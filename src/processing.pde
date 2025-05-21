import hypermedia.net.*;  // Llibreria UDP
UDP udp;

JSONArray canals;

void setup() {
  size(800, 600);
  background(0);

  udp = new UDP(this, 12345);  // Port ha de coincidir amb el de C++
  udp.listen(true);

  canals = new JSONArray();  // Inicialitzar
}

void draw() {
  background(20);
  
  if (canals != null) {
    for (int i = 0; i < canals.size(); i++) {
  JSONObject canal = canals.getJSONObject(i);
  float x = map(canal.getFloat("x"), 0, 1000, 0, width);
  float y = map(canal.getFloat("y"), 0, 1000, 0, height);

  JSONArray senyals = canal.getJSONArray("signals");
  int numSenyals = senyals.size();

  // Dibuixa el cercle principal
  float baseSize = 15;
  fill(100 + numSenyals * 30, 200, 150);
  ellipse(x, y, baseSize, baseSize);

  // Per cada senyal, dibuixa una petita forma al voltant
  for (int j = 0; j < numSenyals; j++) {
    JSONObject senyal = senyals.getJSONObject(j);
    String forma = senyal.getString("wavetype");
    float angle = TWO_PI * j / numSenyals;
    float r = 25;
    float sx = x + cos(angle) * r;
    float sy = y + sin(angle) * r;

    drawWaveShape(forma, sx, sy);
  }

  // Text opcional
  fill(255);
  textSize(10);
  text("Canal " + i, x + 8, y - 8);
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

void drawWaveShape(String forma, float x, float y) {
  float s = 10;  // mida
  stroke(255);
  fill(255, 180);

  if (forma.equals("sin")) {
    // Sinusoide esquemàtica
    noFill();
    beginShape();
    for (int i = 0; i <= 10; i++) {
      float dx = map(i, 0, 10, -s, s);
      float dy = sin(TWO_PI * i / 10.0) * 4;
      vertex(x + dx, y + dy);
    }
    endShape();
  } else if (forma.equals("square")) {
    noStroke();
    rectMode(CENTER);
    rect(x, y, s, s);
  } else if (forma.equals("triangle")) {
    triangle(x - s/2, y + s/2, x, y - s/2, x + s/2, y + s/2);
  } else if (forma.equals("saw")) {
    noFill();
    beginShape();
    vertex(x - s/2, y + s/2);
    vertex(x + s/2, y - s/2);
    vertex(x + s/2, y + s/2);
    endShape();
  } else {
    // Si no es coneix el tipus, punt petit
    ellipse(x, y, 3, 3);
  }
}