byte dipS[8] = {1,2,3,4,5,6,7} ;
int val=0 ;
int t ;
void setup() {
  for(int i=0;i<8;i++){
    pinMode (dipS[i],INPUT) ;
  }
}

void loop() {
for(int j=0;j<8;j++){
    val = 0 ;
    t = digitalRead(dipS[j]) ;
    for(int k=0;k<j;k++){
      t = t * 2 ;
    }
    val = val + t ;
  }
 analogWrite(3,val*4) ;

}
