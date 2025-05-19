const int pinPotenciometre = A0;
const int pinBotoElement = 2;
const int pinBotoEdit = 3;
const int pinBotoCanal = 4;
const int pinBotoSenyal = 5;

const int numCanals = 32;
const int numSenyals = 4;
const int numElements = 5; // freq, ampl, forma, x, y

int canalActual = 0;
int senyalActual = 0;
int elementActual = 0; // 0=freq, 1=ampl, 2=forma, 3=x, 4=y
bool editMode = false;

unsigned long tLastBtn[4] = {0, 0, 0, 0};
const int debounceDelay = 200;

struct Senyal
{
    float freq = 0;
    float ampl = 0;
    int forma = 0;
};

struct Canal
{
    float x = 0;
    float y = 0;
    Senyal senyals[4];
};

Canal canals[numCanals];

void setup()
{
    Serial.begin(9600);
    pinMode(pinBotoElement, INPUT_PULLUP);
    pinMode(pinBotoEdit, INPUT_PULLUP);
    pinMode(pinBotoCanal, INPUT_PULLUP);
    pinMode(pinBotoSenyal, INPUT_PULLUP);
}

void loop()
{
    if (digitalRead(pinBotoElement) == LOW && millis() - tLastBtn[0] > debounceDelay)
    {
        elementActual = (elementActual + 1) % numElements;
        tLastBtn[0] = millis();
    }

    if (digitalRead(pinBotoEdit) == LOW && millis() - tLastBtn[1] > debounceDelay)
    {
        editMode = !editMode;
        Serial.print("Edit mode: ");
        Serial.println(editMode ? "ON" : "OFF");
        tLastBtn[1] = millis();
    }

    if (digitalRead(pinBotoCanal) == LOW && millis() - tLastBtn[2] > debounceDelay)
    {
        canalActual = (canalActual + 1) % numCanals;
        tLastBtn[2] = millis();
    }

    if (digitalRead(pinBotoSenyal) == LOW && millis() - tLastBtn[3] > debounceDelay)
    {
        senyalActual = (senyalActual + 1) % numSenyals;
        tLastBtn[3] = millis();
    }

    int valorPot = analogRead(pinPotenciometre);

    if (editMode)
    {
        Canal &canal = canals[canalActual];
        Senyal &senyal = canal.senyals[senyalActual];

        switch (elementActual)
        {
        case 0: // freq
            senyal.freq = map(valorPot, 0, 1023, 0, 18000);
            Serial.print("CANAL ");
            Serial.print(canalActual);
            Serial.print(" SENYAL ");
            Serial.print(senyalActual);
            Serial.print(" freq: ");
            Serial.println(senyal.freq);
            break;
        case 1: // ampl
            senyal.ampl = valorPot / 1023.0;
            Serial.print("CANAL ");
            Serial.print(canalActual);
            Serial.print(" SENYAL ");
            Serial.print(senyalActual);
            Serial.print(" ampl: ");
            Serial.println(senyal.ampl, 3);
            break;
        case 2:                                          // forma
            senyal.forma = map(valorPot, 0, 1023, 0, 3); // 0-3 per exemple
            Serial.print("CANAL ");
            Serial.print(canalActual);
            Serial.print(" SENYAL ");
            Serial.print(senyalActual);
            Serial.print(" forma: ");
            Serial.println(senyal.forma);
            break;
        case 3: // x
            canal.x = valorPot / 1023.0;
            Serial.print("CANAL ");
            Serial.print(canalActual);
            Serial.print(" x: ");
            Serial.println(canal.x, 3);
            break;
        case 4: // y
            canal.y = valorPot / 1023.0;
            Serial.print("CANAL ");
            Serial.print(canalActual);
            Serial.print(" y: ");
            Serial.println(canal.y, 3);
            break;
        }
    }

    delay(100);
}
