unsigned long previousMillisGetHR = 0;
unsigned long previousMillisResultHR = 0;
const long intervalGetHR = 20;
const long intervalResultHR = 10000;
int pulseSensorSignal;
const int pulseSensor = 15;
int highThreshold = 560;
int lowThreshold = 550;
int cntHB = 0;
boolean threshold = true;
int valBPM = 0;
int iLED = 2;

void setup()
{
  Serial.begin(115200);
  pinMode(iLED, OUTPUT);
  Serial.println();
  Serial.println("Please wait for 10 seconds to get the BPM value.");
}

void loop()
{
  getHeartRate();
}

void getHeartRate()
{
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR)
  {
    previousMillisGetHR = currentMillisGetHR;
  }

  pulseSensorSignal = analogRead(pulseSensor);
  Serial.println(pulseSensorSignal);

  if (pulseSensorSignal > highThreshold && threshold == true)
  {
    cntHB++;
    threshold = false;
    digitalWrite(iLED, HIGH);
  }

  if (pulseSensorSignal < lowThreshold)
  {
    threshold = true;
    digitalWrite(iLED, LOW);
  }

  unsigned long currentMillisResultHR = millis();

  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR)
  {
    previousMillisResultHR = currentMillisResultHR;

    valBPM = cntHB * 6;
    Serial.print("BPM: ");
    Serial.println(valBPM);
    cntHB = 0;
  }

}
