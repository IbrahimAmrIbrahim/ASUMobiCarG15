void setup() {
  for (byte i = 4 ; i < 8 ; i ++ ) {
    pinMode(i , OUTPUT);
    digitalWrite(i , LOW);
  }
}

void loop() {
  for (byte i = 4 ; i < 8 ; i ++ ) {
    digitalWrite(i , HIGH);
    delay(1000);
    digitalWrite(i , LOW);
  }
  for (byte i = 6 ; i > 4 ; i --) {
    digitalWrite(i , HIGH);
    delay(1000);
    digitalWrite(i , LOW);
  }
}
