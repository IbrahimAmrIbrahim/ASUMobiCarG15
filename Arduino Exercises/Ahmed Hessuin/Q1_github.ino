
void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
digitalWrite(5,LOW); // intially put pin 5 as low 
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(5,HIGH);
delay(500) // work for 0.5 sec as delay work with mS
digitalWrite(5,LOW); // set pin 5 low again
delay(1500); // set off for 1.5 sec 
// the void loop work as while loop 


}
