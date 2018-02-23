int t = 1 ;
byte dig = 1 ;
byte button1 = 2 ;
byte button2 = 3 ;
void setup() {
 pinMode(button1,INPUT_PULLUP) ;
 pinMode(button2,INPUT_PULLUP) ;
 pinMode(dig,OUTPUT) ;

}

void loop() {
  attachInterrupt(button1,inc,LOW) ;
  attachInterrupt(button2,dec,LOW) ; 
  digitalWrite(dig,HIGH) ;
  delay(t*1000) ;
  digitalWrite(dig,LOW) ;
  delay(t*1000) ;
 }
 void inc(){
  t = t / 2 ;
}
void dec(){
  t = t * 2 ;
}
