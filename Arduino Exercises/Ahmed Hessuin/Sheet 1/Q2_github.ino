int led_1 = 0;
int led_2 = 1; 
int led_3 = 2; 
int led_4 = 3;
void setup() {
  
  // put your setup code here, to run once:
pinMode(led_1,OUTPUT);
pinMode(led_2,OUTPUT);
pinMode(led_3,OUTPUT);
pinMode(led_4,OUTPUT);
digitalWrite(led_1,LOW); 
digitalWrite(led_2,LOW);
digitalWrite(led_3,LOW);
digitalWrite(led_4,LOW);
}

void loop() {
  digitalWrite(led_1,HIGH);
  delay(1000);
  digitalWrite(led_1,LOW);
  //=========================//
  digitalWrite(led_2,HIGH);
  delay(1000);
  digitalWrite(led_2,LOW);
  //======================//
  digitalWrite(led_3,HIGH);
  delay(1000);
  digitalWrite(led_3,LOW);
  //=============//
  digitalWrite(led_4,HIGH);
  delay(1000);
  digitalWrite(led_4,LOW);
  //======================//
  digitalWrite(led_3,HIGH);
  delay(1000);
  digitalWrite(led_3,LOW);
  //=======================//
  digitalWrite(led_2,HIGH);
  delay(1000);
  digitalWrite(led_2,LOW);

}
