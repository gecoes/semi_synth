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
        float baseSize = 30 * maxAmp;
        String wavetype = maxSignal.getString("wavetype");
        float freq = maxSignal.getFloat("frequency");

        // Dibuixa la figura principal farcida
        fill(getColor(wavetype, maxAmp));
        noStroke();
        drawShape(wavetype, x, y, baseSize);

        // Dibuixa anells al voltant
        int numRings = (int)map(freq, 50, 1000, 3, 10); // ajustar rang freq segons dades reals
        numRings = constrain(numRings, 3, 10);
        float maxRadius = baseSize * 1.8; // ràdi màxim depèn d'amplitud i mida base

        noFill();
        for (int k = 1; k <= numRings; k++) {
          float radius = map(k, 1, numRings, baseSize / 2, maxRadius);
          float alpha = map(k, 1, numRings, 150, 20);
          stroke(red(getColor(wavetype, maxAmp)), green(getColor(wavetype, maxAmp)), blue(getColor(wavetype, maxAmp)), alpha);
          strokeWeight(2);
          drawShapeOutline(wavetype, x, y, radius * 2);  // *2 perquè size és diàmetre
        }
      }

      // Dibuixa formes més petites per altres senyals
      for (int j = 0; j < senyals.size(); j++) {
        JSONObject s = senyals.getJSONObject(j);
        if (s == maxSignal) continue;
        float amp = s.getFloat("amplitude");
        float size = 25 * amp;
        fill(getColor(s.getString("wavetype"), amp), 120);
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

      // Afegim una ona nova per cada canal rebut amb la seva freq i amp màxima
      for (int i = 0; i < canals.size(); i++) {
        JSONObject canal = canals.getJSONObject(i);
        JSONArray senyals = canal.getJSONArray("signals");

        float maxAmp = 0;
        float maxFreq = 0;
        String maxWave = "sin";
        for (int j = 0; j < senyals.size(); j++) {
          JSONObject s = senyals.getJSONObject(j);
          float amp = s.getFloat("amplitude");
          float freq = s.getFloat("frequency");
          if (amp > maxAmp) {
            maxAmp = amp;
            maxFreq = freq;
            maxWave = s.getString("wavetype");
          }
        }
        color c = getColor(maxWave, maxAmp);
      }
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
  } else if (forma.equals("triangle")) {
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
  } else if (forma.equals("triangle")) {
    triangle(x - size/2, y + size/2, x, y - size/2, x + size/2, y + size/2);
  } else {
    ellipse(x, y, size/2, size/2);
  }
}

void drawShapeOutline(String forma, float x, float y, float size) {
  if (forma.equals("sin")) {
    ellipse(x, y, size, size);
  } else if (forma.equals("square")) {
    rect(x, y, size, size);
  } else if (forma.equals("triangle")) {
    // triangle: recalculant vèrtexs per contorn segons size (amplada)
    float half = size / 2;
    triangle(x - half, y + half, x, y - half, x + half, y + half);
  } else {
    ellipse(x, y, size/2, size/2);
  }
}
