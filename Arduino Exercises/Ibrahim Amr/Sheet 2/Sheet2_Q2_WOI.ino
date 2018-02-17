void setup() {
  pinMode(2 , INPUT_PULLUP);
  pinMode(3 , INPUT_PULLUP);
  pinMode(0 , OUTPUT);
  digitalWrite(0 , LOW);
}
int   x = 0;
void loop() {
  if ((digitalRead(2) == LOW) && (x < 10000)) {
    x += 1000;
  }
  if ((digitalRead(3) == LOW) && (x > 0)) {
    x -= 1000;
  }
  digitalWrite(0 , HIGH);
  delay((x / 2));
  digitalWrite(0 , LOW);
  delay((x / 2));
}
