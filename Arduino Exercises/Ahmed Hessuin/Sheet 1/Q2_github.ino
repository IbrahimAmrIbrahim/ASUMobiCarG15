int led_1 = 4;
int led_2 = 5; 
int led_3 = 6; 
int led_4 = 7;
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
  // put your main code here, to run repeatedly:
digitalWrite(led_1,HIGH);
delay(1000) ;// work for 1 sec as delay work with mS
digitalWrite(led_1,LOW); 
//=====================================//
digitalWrite(led_2,HIGH);
delay(1000) ;// work for 1 sec as delay work with mS
digitalWrite(led_2,LOW); 
//====================================//
digitalWrite(led_3,HIGH);
delay(1000) ;// work for 1 sec as delay work with mS
digitalWrite(led_3,LOW); 
//==================================//
digitalWrite(led_4,HIGH);
delay(1000);
digitalWrite(led_4,LOW); 
//=====================================//
digitalWrite(led_3,HIGH);
delay(1000) ;// work for 1 sec as delay work with mS
digitalWrite(led_3,LOW); 
//====================================//
digitalWrite(led_2,HIGH);
delay(1000) ;// work for 1 sec as delay work with mS
digitalWrite(led_2,LOW); 
//==================================//
digitalWrite(led_1,HIGH);
delay(1000);
digitalWrite(led_1,LOW); 


// the void loop work as while loop 


}
