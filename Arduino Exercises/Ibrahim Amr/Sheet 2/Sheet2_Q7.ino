void setup() {
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  pinMode (2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), state, CHANGE);

}
int FTime = 0;
int STime = 0;
byte LEDState = 2;
boolean timeState = false;
void state() {
  if (timeState == false) {
    FTime = millis();
    timeState = true;
  }
  else if (timeState == true) {
    STime =  millis();
    timeState = false;
    if (((STime - FTime) >= 5000) && (LEDState != 1)) {
      LEDState = 1;
    } else if (((STime - FTime) >= 5000) && (LEDState == 1)) {
      LEDState = 2;
    } else if (((STime - FTime) < 5000) && (LEDState == 3)) {
      LEDState = 2;
    } else if (((STime - FTime) < 5000) && (LEDState == 2 )) {
      LEDState = 3;
    }
  }
}
void loop() {
  switch (LEDState) {
    case 1:
      {
        digitalWrite(0, HIGH);
        delay(500);
        digitalWrite(0, LOW);
        delay(500);
        break;
      }
    case 2:
      {
        digitalWrite(0, LOW);
        break;
      }
    case 3:
      {
        digitalWrite(0, HIGH);
        break;
      }
  }
}
