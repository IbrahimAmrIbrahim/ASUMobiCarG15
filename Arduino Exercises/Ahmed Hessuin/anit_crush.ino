void anti_crush() {
const byte ping_Out = 22;
const byte ping_In = 23 ;
int duration;
int cm ;
  pinMode(ping_Out, OUTPUT);
  digitalWrite(ping_Out, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_Out, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_Out, LOW);
  pinMode(ping_In, INPUT);
  duration = pulseIn(ping_In, HIGH);
  cm = duration / 29 / 2;
  if (cm <=15 ){
    STOP();// stop all motors
  }
  
}
