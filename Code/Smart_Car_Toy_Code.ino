#include <Servo.h>
#include <SoftwareSerial.h>
#include<Wire.h>

//Bluetooth
#define Hc_05_TXD_ARDUINO_RXD 10
#define Hc_05_RXD_ARDUINO_TXD 11
//Motor Driver
#define MIN1 3
#define MIN2 4
#define MIN3 5
#define MIN4 6
//UltraSonic
#define SERVO 9
#define ping_trig 26
#define ping_echo 27
//Line Tracking Sensors
#define LT1P 50
#define LT2P 42
#define LT3P 45
#define LT1G 46
#define LT2G 51
#define LT3G 52
#define LT1S 48
#define LT2S 53
#define LT3S 43
//Light interrupt
#define LIP 2
#define LIG 2
#define LIS 2
//Gyroscope
#define GyroP 2
#define GyroG 2
#define GyroAD0 2

Servo myservo;
SoftwareSerial BTSerial(Hc_05_TXD_ARDUINO_RXD, Hc_05_RXD_ARDUINO_TXD); // RX | TX
String BD = "";
char IBD = 0;
char IPBD = 0;
const int MPU_addr = 0x68;
int16_t Gz ;
volatile int LI_Count = 0 ;
bool sent = false;

void Motion(byte Direction , byte MSpeed = 100 , byte RSpeed = 0);
void Drive();
int ping_read();
bool anti_crush();
void servo_check(char a);
void Follow();
int steps_counter();
float string_to_float();
void move_with_steps(int x , char y);
void count() ;
void accurate_motion() ;

void setup() {
  //Motor Driver Pins
  pinMode(MIN1, OUTPUT);
  digitalWrite(MIN1, LOW);
  pinMode(MIN2, OUTPUT);
  digitalWrite(MIN2, LOW);
  pinMode(MIN3, OUTPUT);
  digitalWrite(MIN3, LOW);
  pinMode(MIN4, OUTPUT);
  digitalWrite(MIN4, LOW);

  //UltraSonic Pins
  pinMode(ping_trig, OUTPUT);
  digitalWrite(ping_trig, LOW);
  pinMode(ping_echo, INPUT);
  myservo.attach(SERVO);
  myservo.write(90);

  //Line Tracking Sensors Pins
  pinMode(LT1P, OUTPUT);
  digitalWrite(LT1P, HIGH);
  pinMode(LT2P, OUTPUT);
  digitalWrite(LT2P, HIGH);
  pinMode(LT3P, OUTPUT);
  digitalWrite(LT3P, HIGH);
  pinMode(LT1G, OUTPUT);
  digitalWrite(LT1G, LOW);
  pinMode(LT2G, OUTPUT);
  digitalWrite(LT2G, LOW);
  pinMode(LT3G, OUTPUT);
  digitalWrite(LT3G, LOW);
  pinMode(LT1S, INPUT);
  pinMode(LT2S, INPUT);
  pinMode(LT3S, INPUT);

  //Light interrupt Pins
  pinMode(LIP, OUTPUT) ;
  digitalWrite(LIP, HIGH);
  pinMode(LIG, OUTPUT) ;
  digitalWrite(LIG, LOW);
  pinMode(LIS, INPUT);
  attachInterrupt(digitalPinToInterrupt(LIS), count, RISING) ;

  //Gyroscope
  pinMode(GyroP, OUTPUT) ;
  digitalWrite(GyroP, HIGH);
  pinMode(GyroG, OUTPUT) ;
  digitalWrite(GyroG, LOW);
  pinMode(GyroAD0, OUTPUT) ;
  digitalWrite(GyroAD0, LOW);

  Serial.begin(9600);
  BTSerial.begin(9600);  // Hc-05 default speed in AT command mode
  BTSerial.println("car is ready");
}



void loop() {
   if (sent == false) {
    BTSerial.println("Easy driving mode      -----> ED");
    BTSerial.println("Line tracking mode     -----> LT");
    BTSerial.println("Accurate Movement mode -----> AM");
    sent = true;
  }
  if (BTSerial.available()) {
    IBD = char(BTSerial.read());
    if (IBD == ';') {
      if (BD == "ED" || BD == "ed") {
        sent = false;
        Drive();
      } else if (BD == "LT" || BD == "lt") {
        sent = false;
        Follow();
      } else if (BD == "AM" || BD == "am") {
        sent = false;
        accurate_motion() ;
      } else {
        BTSerial.println("Wrong command");
      }
      BD = "";
    } else {
      BD += IBD;
    }
  }
}

void Motion(byte Direction , byte MSpeed = 100 , byte RSpeed = 0) {
  // Direction = 0 ----> Linear Motion Forward
  // Direction = 1 ----> Linear Motion Backward
  // Direction = 2 ----> Forward  Right Rotating
  // Direction = 3 ----> Forward  Left  Rotating
  // Direction = 4 ----> Backward Right Rotating
  // Direction = 5 ----> Backward Left  Rotating
  // Direction = 6 ----> Stop

  // MSpeed : Motion Speed    ----> 1 : 100
  // RSpeed : Rotation Speed  ----> 1 : 100

  // RSpeed = 50   ----> Side Stop
  // RSpeed = 100  ----> Side reverse

  byte PMWLV ;
  byte PMWRV ;
  if (MSpeed >= 0 && MSpeed <= 100) {
    PMWLV = ((MSpeed * 255 ) / 100);
  } else {
    PMWLV = 0;
  }

  switch (Direction) {
    case 0: {
        analogWrite(MIN2, 0);
        analogWrite(MIN3, 0);
        analogWrite(MIN1, PMWLV);
        analogWrite(MIN4, PMWLV);
        break;
      }
    case 1: {
        analogWrite(MIN1, 0);
        analogWrite(MIN4, 0);
        analogWrite(MIN2, PMWLV);
        analogWrite(MIN3, PMWLV);
        break;
      }
    case 2: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN2, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN1, PMWLV);
          analogWrite(MIN4, PMWRV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN2, 0);
          analogWrite(MIN4, 0);
          analogWrite(MIN1, PMWLV);
          analogWrite(MIN3, PMWRV);
        } else {
          analogWrite(MIN2, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN1, PMWLV);
          analogWrite(MIN4, PMWLV);
        }
        break;
      }
    case 3: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN2, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN1, PMWRV);
          analogWrite(MIN4, PMWLV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN4, 0);
          analogWrite(MIN2, 0);
          analogWrite(MIN1, PMWRV);
          analogWrite(MIN3, PMWLV);
        } else {
          analogWrite(MIN2, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN1, PMWLV);
          analogWrite(MIN4, PMWLV);
        }
        break;
      }
    case 4: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN1, 0);
          analogWrite(MIN4, 0);
          analogWrite(MIN2, PMWLV);
          analogWrite(MIN3, PMWRV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN1, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN2, PMWLV);
          analogWrite(MIN4, PMWRV);
        } else {
          analogWrite(MIN1, 0);
          analogWrite(MIN4, 0);
          analogWrite(MIN2, PMWLV);
          analogWrite(MIN3, PMWLV);
        }
        break;
      }
    case 5: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN1, 0);
          analogWrite(MIN4, 0);
          analogWrite(MIN2, PMWRV);
          analogWrite(MIN3, PMWLV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          analogWrite(MIN1, 0);
          analogWrite(MIN3, 0);
          analogWrite(MIN2, PMWRV);
          analogWrite(MIN4, PMWLV);
        } else {
          analogWrite(MIN1, 0);
          analogWrite(MIN4, 0);
          analogWrite(MIN2, PMWLV);
          analogWrite(MIN3, PMWLV);
        }
        break;
      }
    case 6: {
        analogWrite(MIN1, 0);
        analogWrite(MIN2, 0);
        analogWrite(MIN3, 0);
        analogWrite(MIN4, 0);
        break;
      }
    default: {
        analogWrite(MIN1, 0);
        analogWrite(MIN2, 0);
        analogWrite(MIN3, 0);
        analogWrite(MIN4, 0);
        break;
      }
  }
}


void Drive() {
  //F || f ----> forward
  //B || b ----> backward
  //R || r ----> forward Right
  //L || l ----> forward Left
  //V || V ----> backward Right
  //W || w ----> backward Left
  //A || a ----> rotate around axis
  //S || s ----> stop
  BTSerial.println("Easy Driving Mode");
  BTSerial.println("forward            ----> F");
  BTSerial.println("Backward           ----> B");
  BTSerial.println("Forward Right      ----> R");
  BTSerial.println("Forward Left       ----> L");
  BTSerial.println("Backward Right     ----> V");
  BTSerial.println("Backward Left      ----> W");
  BTSerial.println("Rotate around axis ----> A");
  BTSerial.println("stop               ----> S");
  BTSerial.println("Exit               ----> E");
  while ((BD != "E") && (BD != "e")) {
    if (BTSerial.available()) {
      BD = char(BTSerial.read());
    }
    if (BD == "F" || BD == "f" ) {
      if (IPBD == 'F') {
        if (!anti_crush(15)) {
          Motion(0 , 100, 0);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'F';
        servo_check(IPBD);
      }
    } else if (BD == "B" || BD == "b") {
      if (IPBD == 'B') {
        Motion(1 , 100, 0);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'B';
        servo_check(IPBD);
      }
    } else if (BD == "R" || BD == "r" ) {
      if (IPBD == 'R') {
        if (!anti_crush(15)) {
          Motion(2 , 100, 25);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'R';
        servo_check(IPBD);
      }
    } else if (BD == "L" || BD == "l") {
      if (IPBD == 'L') {
        if (!anti_crush(15)) {
          Motion(3 , 100, 25);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'L';
        servo_check(IPBD);
      }
    } else if (BD == "V" || BD == "v") {
      if (IPBD == 'V') {
        Motion(4 , 100, 25);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'V';
        servo_check(IPBD);
      }
    } else if (BD == "W" || BD == "w") {
      if (IPBD == 'W') {
        Motion(5 , 100, 25);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'W';
        servo_check(IPBD);
      }
    } else if (BD == "A" || BD == "a") {
      if (IPBD == 'A') {
        Motion(2 , 100, 100);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'A';
        servo_check(IPBD);
      }
    } else {
      Motion(6 , 0, 0);
      IPBD = 'S';
      servo_check(IPBD);
    }
  }
  BTSerial.println("Trminate easy Driving Mode");
}

// read the distance infront of the ping
int ping_read() {
  unsigned int  cm , duration;
  digitalWrite(ping_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_trig, LOW);
  duration = pulseIn(ping_echo, HIGH);
  cm = duration / 29 / 2 ;
  delay(2);
  return cm;
}


// if the distance less than 15 cm STOP!
bool  anti_crush(int x ) { // x distance in cm
  if (ping_read() <= x ) { // if distance less than x ===> stop and return true
    Motion(6, 0, 0);
    return true;
  } else {
    return false;
  }
}


//servo
void servo_check(char a) {
  if (a == 'f' || a == 'F') {
    myservo.write(90);
    delay(250);
  }  else if (a == 'r' || a == 'R') {
    myservo.write(45);
    delay(250);
  }  else if (a == 'l' || a == 'L') {
    myservo.write(135);
    delay(250);
  } else {
    myservo.write(90);
  }
}


void Follow() {
  bool L1 ; bool Mid ; bool R1;
  bool White = 0;
  bool Black = 1;
  BTSerial.println("Line Tracking Mode");
  BTSerial.println("Start -----> I");
  BTSerial.println("Stop  -----> S");
  BTSerial.println("Exit  -----> E");  
  while ((BD != "E") && (BD != "e")) {
    if (BTSerial.available()) {
      BD = char(BTSerial.read());
    }
    if  (BD == "I" || BD == "i") {
      L1 = digitalRead(LT1S);
      Mid = digitalRead(LT2S);
      R1 = digitalRead(LT3S);
      if (L1 == Black && Mid == White  && R1 == White) {
        Motion(3 , 80 , 50);
      } else if (L1 == White  && Mid == White && R1 == Black) {
        Motion(2 , 80 , 50);
      } else if (Mid == Black) {
        Motion (0 , 50 , 0);
      }
    } else if (BD == "S" || BD == "s") {
      Motion (6 , 0 , 0);
      BD = "";
    }
  }
  BTSerial.println("Trminate Line Tracking Mode");
}


float string_to_float() {
  String user_input = "";
  char input = '0' ;
  float float_number;
  while (true) {
    if (BTSerial.available()) {
      input = char(BTSerial.read());
      if (input == ';') {
        break;
      }
      user_input += input;
    }
  }
  if ( input == ';') {
    float_number = user_input.toFloat();
    return float_number;
  }
}

int steps_counter() {
  // give it distance for example 12 return 12/1.625 ( the unit step as cm ) and cell or floor the number to get the min error
  float distance;
  float real_distance; // the distance/1.625 but celled or floored
  float my_dumy; // equal to distance
  float deff; // deff betwien the distance /1.625 in float - distabce /1.625 in int

  distance = string_to_float();
  real_distance = distance / 0.9739; // make copy of distance / 1.625 ( resolution )
  my_dumy = distance; // make sec copy to operate on it as int
  distance = distance / 0.9739 ; // distance /1.625 = no of steps for example 10.3 times high from light sensor
  my_dumy = int(my_dumy / 0.9739); // distance /1.625 = 10 because it's int
  deff = distance - my_dumy ; // 10.3 - 10 = 0.3
  deff = deff - 0.5; // 0.3 - 0.5 = negative 0.2
  if ( deff > 0) {
    real_distance = ceil(real_distance);
  }//if  deff float > 0
  else if ( deff < 0) { // deff is negative
    real_distance = floor(real_distance); // read 10 times high from the sensor is most optmize solution
  } //if  deff <0

  return real_distance;
}


void move_with_steps(int x ,char y,float angle){
     if (x >=10 && y != 't'){
       x=x-6;
      }
      //Serial.println(x);
    // give it x = step numbers = the light entrupter count number ,y the direction , angle the angle //
      if ((y=='f'||y=='F')&&angle==0){
      
      c = 0 ;
     while(1){
    //Motion(3,50,0) ; // move motors forward
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(3,127.962);//216
      analogWrite(10,125);//211
      
      if(c >=x ){// was x    only
        Motion(1,25,0);
        delay(50);
        Motion(6,0,0) ;
        break ;
      }  
   } // while loop
  } // if f
   if((y=='b'||y=='B')&&angle==0){
    c = 0 ;
    while(1){
     // Motion(1,50,0) ; // move motors backward
       analogWrite(3,0);
      analogWrite(10,0);
      analogWrite(5,125);
      analogWrite(6,127.9620853);
     //Serial.println(c);
      if(c >= x){// was x 
        Motion(0,25,0);
        delay(50);
        Motion(6,0,0) ;
        break ;
      }  
    } // while loop
   } // if b
//===========================//
   if((y=='t'||y=='T')&&angle==0){
     c = 0 ;
     while(1){
    //Motion(3,50,0) ; // move motors forward
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(3,225);
      analogWrite(10,210);
      
      if(c >= x){
        Motion(6,0,0) ;
        break ;
      }  
   } // while loop
  } // if t

   Motion(6,0,0) ; // Stop 
 }

void angle (float ra) {
  // ra is required angle
  float t , tp , gs , a = 0;
  Wire.begin(); // disabling sleep mode of the gyro
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  while ((ra > 180) || (ra < -180)) { // making ra between -180 , 180
    if (ra < -180) {
      ra = ra + 360 ;
    }
    if (ra > 180) {
      ra = ra - 360 ;
    }
  }
  if (ra > 0) {
    Motion(3, 35, 100) ; //turn left around car axis
  } else if (ra < 0) {
    Motion(4, 35, 100) ; //turn right around car axis
  } else {
    Motion(6, 0, 0) ; // stop
  }
  t = millis() ; // taking initial value of time
  while (1) {
    tp = t ;
    t = millis() ;
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 2, true);
    Gz = Wire.read() << 8 | Wire.read(); // Gz is the angular velocity
    gs = Gz / 131.0 ; // 131 is the gyro scale
    a = a + gs * ((t - tp) / 1000) ;

    if (a >= 360) {
      a = a - 360 ;
    } else if (a <= -360) {
      a = a + 360 ;
    }
    if (ra > 0) {
      if (a >= ra) {
        Motion(6, 0, 0) ;
        break ;
      }
    } else if (ra < 0) {
      if (a <= ra) {
        Motion(6, 0, 0) ;
        break ;
      }
    } else {
      break ;
    }
  }
}


void count() {
  LI_Count++ ;
}


void accurate_motion(){
  char End='0';
  float my_angle=0;
  int steps=0;

 while( End !='e' && End!='E'){ // while he didn't get e
  if (Serial.available()){
    End=char(Serial.read());
    if(End=='e' ||End =='E'){
      End='0';
      break;
    }
  }
  if (End=='f'||End=='b'||End=='F'||End=='B'){ // if he recived f or b only
    Serial.println("Enter distance ") ;
    if (End =='f'||'F'==End){
      Serial.println("Forward");
     
    }
    if (End =='b'||'B'==End){
      Serial.println("Backward");
     
    }
    steps= steps_counter();
 // after taking the distance from user
 // move with step = real_distance , in direction of End
 delay(5000);
    move_with_steps (steps,End,0); // take the order for example End = f and the steps 1.625 * real_distance

  }

 if (End=='a'||End=='A'){// move with angle
  Serial.println("Enter angle") ;
  my_angle= string_to_float();
  Serial.println("Enter distance") ;
  steps= steps_counter();
  delay(5000);
  angle(my_angle) ;
  move_with_steps(steps,'f',0);
  // ashraf funtion 
  // my function
 }
 if (End=='h'||End=='H'){
  Serial.println("infinity");
   // infinity
   angle (30) ;  
   move_with_steps(45,'t',0) ;
   
   for (int i=0 ; i<45 ; i++){
    c = 0 ;
    move_with_steps(2,'t',0) ;
    Motion(6,0,0) ;
    angle(-3) ;
    }
    
    move_with_steps(110,'t',0) ;
    
    for (int i=0 ; i<40; i++){
    c = 0 ;
    move_with_steps(2,'t',0) ;
    Motion(6,0,0) ;
    angle(3) ;
    }
    
    move_with_steps(45,'t',0) ;
    angle(-30) ;
    delay(10000) ;
   // square
Serial.println("rectangle");
  for(int i=0 ; i<4 ; i++){
    c = 0 ;  
      move_with_steps(193,'f',0) ;
   
   Motion(6,0,0) ;
    delay(1000);
  // Serial.println("flag1");
    angle(87  ) ; //90 degree 90 -7.1 
    delay(1000);
   
  }
  delay(10000) ;
 // circle 
 Serial.println("circle");
  c = 0 ; 
  for (int i=0 ; i<55 ; i++){
    c = 0 ;
    move_with_steps(8,'t',0) ;
    Motion(6,0,0) ;
    angle(3) ;
  //  Serial.println("flag 1");
//    if(c == 645){ // 645 is the number of steps
//      Motion(6,0,0) ;
//      break ;
//    }
  }
//Serial.println("flag 2");
  Motion(6,0,0) ;
 }
   End='0';
   }//while   
}
