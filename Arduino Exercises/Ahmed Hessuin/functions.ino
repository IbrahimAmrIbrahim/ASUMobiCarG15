int ping_read(){// read the distance infront of the ping
  unsigned int  cm ,duration;
  pinMode(ping_tri, OUTPUT);
  digitalWrite(ping_tri, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_tri, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_tri, LOW);
  pinMode(ping_ecc, INPUT);
  duration = pulseIn(ping_ecc, HIGH);
  cm = duration / 29 / 2 ;
  delay(2);
 return cm;
}
//====================================//
void  anti_crush(){// if the distance less than 15 cm STOP!
  if (ping_read() <= 15 ){
  Motion(6);
  }// if
}// void anti_crush
