import hypermedia.net.*;  // Llibreria UDP
UDP udp;

JSONArray canals;

void setup() {
  size(800, 600);
  background(0);

  udp = new UDP(this, 12345);
  udp.listen(true);

  canals = new JSONArray();
  ellipseMode(CENTER);
  rectMode(CENTER);
  noStroke();
}

void draw() {
  background(20);

  if (canals != null) {
    for (int i = 0; i < canals.size(); i++) {
      JSONObject canal = canals.getJSONObject(i);
      float x = map(canal.getFloat("x"), 0, 100, 0, width);
      float y = map(canal.getFloat("y"), 0, 100, 0, height);

      JSONArray senyals = canal.getJSONArray("signals");

      // Senyal amb més amplitud
      float maxAmp = 0;
      JSONObject maxSignal = null;
      for (int j = 0; j < senyals.size(); j++) {
        JSONObject s = senyals.getJSONObject(j);
        float amp = s.getFloat("amplitude");
        if (amp > maxAmp) {
          maxAmp = amp;
          maxSignal = s;
        }
      }

      if (maxSignal != null) {
        float baseSize = 10 * maxAmp;
        String wavetype = maxSignal.getString("wavetype");
        float freq = maxSignal.getFloat("frequency");

        // Dibuixa la figura principal farcida
        fill(getColor(wavetype, maxAmp));
        noStroke();
        drawInterpolatedShape(senyals, x, y, baseSize);

        // Dibuixa anells al voltant
        int numRings = (int)map(freq, 50, 1000, 3, 10);
        numRings = constrain(numRings, 3, 10);
        float maxRadius = baseSize * 3;

        noFill();
        for (int k = 1; k <= numRings; k++) {
          float radius = map(k, 1, numRings, baseSize / 2, maxRadius);
          float alpha = map(k, 1, numRings, 150, 20);
          color col = getColor(wavetype, maxAmp);
          stroke(red(col), green(col), blue(col), alpha);
          strokeWeight(2);
          drawInterpolatedShape(senyals, x, y, radius * 2);
        }
      }

      // Dibuixa formes més petites per altres senyals
      for (int j = 0; j < senyals.size(); j++) {
        JSONObject s = senyals.getJSONObject(j);
        if (s == maxSignal) continue;
        float amp = s.getFloat("amplitude");
        float size = 25 * amp;
        fill(getColor(s.getString("wavetype"), amp), 80);
        noStroke();
        drawShape(s.getString("wavetype"), x, y, size);
      }
    }
  }
}

void receive(byte[] data) {
  String msg = new String(data);
  try {
    JSONArray root = parseJSONArray(msg);
    if (root != null) {
      canals = root;
      println("Rebuts " + canals.size() + " canals.");
    }
  } catch (Exception e) {
    println("Error parsejant: " + e.getMessage());
  }
}

color getColor(String forma, float amp) {
  amp = constrain(amp, 0, 1);
  if (forma.equals("sin")) {
    return color(0, 150 + amp * 105, 255);
  } else if (forma.equals("square")) {
    return color(255, 50 + amp * 205, 50);
  } else if (forma.equals("saw")) {
    return color(150 + amp * 105, 255, 50);
  } else {
    return color(200);
  }
}

void drawShape(String forma, float x, float y, float size) {
  if (forma.equals("sin")) {
    ellipse(x, y, size, size);
  } else if (forma.equals("square")) {
    rect(x, y, size, size);
  } else if (forma.equals("saw")) {
    triangle(x - size/2, y + size/2, x, y - size/2, x + size/2, y + size/2);
  } else {
    ellipse(x, y, size/2, size/2);
  }
}

void drawInterpolatedShape(JSONArray senyals, float x, float y, float size) {
  PVector[] sumPts = new PVector[40];
  for (int i = 0; i < 40; i++) sumPts[i] = new PVector();

  for (int j = 0; j < senyals.size(); j++) {
    JSONObject s = senyals.getJSONObject(j);
    float amp = s.getFloat("amplitude");
    if (amp <= 0) continue;
    String forma = s.getString("wavetype");
    PVector[] pts = getShapePoints(forma, size);
    for (int i = 0; i < 40; i++) {
      sumPts[i].x += pts[i].x * amp;
      sumPts[i].y += pts[i].y * amp;
    }
  }

  beginShape();
  for (int i = 0; i < 40; i++) {
    vertex(x + sumPts[i].x, y + sumPts[i].y);
  }
  endShape(CLOSE);
}

PVector[] getShapePoints(String forma, float size) {
  ArrayList<PVector> pts = new ArrayList<PVector>();
  int resolution = 40;

  if (forma.equals("sin")) {
    for (int i = 0; i < resolution; i++) {
      float angle = map(i, 0, resolution, 0, TWO_PI);
      pts.add(new PVector(cos(angle) * size/2, sin(angle) * size/2));
    }
  } else if (forma.equals("square")) {
    pts.add(new PVector(-size/2, -size/2));
    pts.add(new PVector(size/2, -size/2));
    pts.add(new PVector(size/2, size/2));
    pts.add(new PVector(-size/2, size/2));
    while (pts.size() < resolution) pts.add(pts.get(pts.size() % 4));
  } else if (forma.equals("saw")) {
    pts.add(new PVector(-size/2, size/2));
    pts.add(new PVector(0, -size/2));
    pts.add(new PVector(size/2, size/2));
    pts.add(new PVector(0, size/4));
    while (pts.size() < resolution) pts.add(pts.get(pts.size() % 4));
  } else {
    for (int i = 0; i < resolution; i++) {
      float angle = map(i, 0, resolution, 0, TWO_PI);
      pts.add(new PVector(cos(angle) * size/2, sin(angle) * size/2));
    }
  }

  return pts.toArray(new PVector[0]);
}
