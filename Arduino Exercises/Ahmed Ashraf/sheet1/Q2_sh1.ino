int leds[4] = {4,5,6,7} ;
void setup() {
 for (int i=0;i<4;i++){
   pinMode(leds[i],OUTPUT) ;
 }

}

void loop() {
  for(int j=0 ; j<4 ; j++){
    digitalWrite(leds[j],HIGH) ;
    delay(1000) ; 
    digitalWrite(leds[j],LOW) ;
  }
  for(int k=2 ; k>=1 ; k--){
    digitalWrite(leds[k],HIGH) ;
    delay(1000) ; 
    digitalWrite(leds[k],LOW) ;

}
}
