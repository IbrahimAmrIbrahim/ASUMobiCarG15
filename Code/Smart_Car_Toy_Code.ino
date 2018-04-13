#include <Servo.h>
#include <SoftwareSerial.h>

//Bluetooth
#define HC_05_TXD_ARDUINO_RXD 10
#define HC_05_RXD_ARDUINO_TXD 11
//Motor Driver
#define MIN1 3
#define MIN2 4
#define MIN3 5
#define MIN4 6
//UltraSonic
#define SERVO 9
#define ping_tri 26
#define ping_ecc 27

Servo myservo;
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
String BD = "";
char IBD = 0;
char IPBD = 0;

void Motion(byte Direction , byte MSpeed = 100 , byte RSpeed = 0);
void Drive_T();
int ping_read();
bool anti_crush();
int steps_counter();
void servo_cheak(char a);
float string_to_float();
void move_with_steps(int x ,char y,float angle);

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
  pinMode(ping_tri, OUTPUT);
  digitalWrite(ping_tri, LOW);
  pinMode(ping_ecc, INPUT);
  myservo.attach(SERVO);
  myservo.write(90);

  Serial.begin(9600);
  BTSerial.begin(9600);  // HC-05 default speed in AT command mode
  BTSerial.println("Car is ready");
}



void loop() {
  if (BTSerial.available()) {
    IBD = char(BTSerial.read());
    if (IBD == ';') {
      if (BD == "EDT" || BD == "edt") {
           Drive_T();
      } else {
        BTSerial.println("Wrong Command");
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


void Drive_T() {
  //F || f ----> forward
  //B || b ----> backward
  //R || r ----> forward Right
  //L || l ----> forward Left
  //V || V ----> backward Right
  //W || w ----> backward Left
  //A || a ----> rotate around axis
  //S || s ----> stop
  BTSerial.println("Easy Driving Mode");
  while ((BD != "E") && (BD != "e")) {
    if (BTSerial.available()) {
      BD = char(BTSerial.read());
    }
    if (BD == "F" || BD == "f" ) {
      if (IPBD == 'F') {
        if (!anti_crush(15)){ 
          Motion(0 , 100, 0);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'F';
        servo_cheak(IPBD);
      }
    } else if (BD == "B" || BD == "b") {
      if (IPBD == 'B') {
        Motion(1 , 100, 0);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'B';
        servo_cheak(IPBD);
      }
    } else if (BD == "R" || BD == "r" ) {
      if (IPBD == 'R') {
        if (!anti_crush(15)){
          Motion(2 , 100, 25);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'R';
        servo_cheak(IPBD);
      }
    } else if (BD == "L" || BD == "l") {
      if (IPBD == 'L') {
        if (!anti_crush(15)){
          Motion(3 , 100, 25);
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'L';
        servo_cheak(IPBD);
      }
    } else if (BD == "V" || BD == "v") {
      if (IPBD == 'V') {
        Motion(4 , 100, 25);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'V';
        servo_cheak(IPBD);
      }
    } else if (BD == "W" || BD == "w") {
      if (IPBD == 'W') {
        Motion(5 , 100, 25);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'W';
        servo_cheak(IPBD);
      }
    } else if (BD == "A" || BD == "a") {
      if (IPBD == 'A') {
        Motion(2 , 100, 100);
      } else {
        Motion(6 , 0, 0);
        IPBD = 'A';
        servo_cheak(IPBD);
      }
    } else {
      Motion(6 , 0, 0);
      IPBD = 'S';
      servo_cheak(IPBD);
    }
  }
  BTSerial.println("Trminate easy Driving Mode");
}

// read the distance infront of the ping
int ping_read(){
  unsigned int  cm ,duration;
  digitalWrite(ping_tri, LOW);
  delayMicroseconds(2);
  digitalWrite(ping_tri, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping_tri, LOW);
  duration = pulseIn(ping_ecc, HIGH);
  cm = duration / 29 / 2 ;
  delay(2);
  return cm;
}


// if the distance less than 15 cm STOP!
bool  anti_crush(int x ){// x distance in cm
  if (ping_read() <= x ){ // if distance less than x ===> stop and return true 
  Motion(6,0,0);
  return true;
  } else {
  return false;
  }
}


//servo
void servo_cheak(char a){
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
//===========================//
float string_to_float(){ // enter string as 123.26; return 123.26
String user_input = "";
char input='0' ;
  float float_number;
  while ((input != ';')){  // read the distance as string tell yoy find ;
 if(BTSerial.available()){ // read string
  input=char(BTSerial.read());
   if (input==';'){ // to don't add the ; to the input distance
  break;
 }
  user_input+=input;
 }

  }    
   if ( input==';'){// when you find the ;
    float_number=user_input.toFloat();// transform user distance from string to float
  
  return float_number;
}
}
  //========================//
  int steps_counter(){ // give it distance for example 12 return 12/1.625 ( the unit step as cm ) and cell or floor the number to get the min error 
  float distance;
  float real_distance; // the distance/1.625 but celled or floored 
  float my_dumy; // equal to distance
  float deff; // deff betwien the distance /1.625 in float - distabce /1.625 in int 

    distance = string_to_float();
    real_distance=distance/1.625;  // make copy of distance / 1.625 ( resolution )
    my_dumy= distance; // make sec copy to operate on it as int 
    distance= distance/1.625 ; // distance /1.625 = no of steps for example 10.3 times high from light sensor
    my_dumy= int(my_dumy/1.625); // distance /1.625 = 10 because it's int 
   deff = distance-my_dumy ; // 10.3 - 10 = 0.3 
   deff = deff-0.5; // 0.3 - 0.5 = negative 0.2
   if ( deff >0){ 
    real_distance =ceil(real_distance);
   }//if  deff float > 0 
   else if ( deff<0){ // deff is negative 
    real_distance= floor(real_distance); // read 10 times high from the sensor is most optmize solution
   } //if  deff <0
   
    
   return real_distance;
 }
//===========================//
void move_with_steps(int x ,char y,float angle){ // give it x = step numbers = the light entrupter count number ,y the direction , angle the angle //
  if (y=='f'&&angle==0){
for (int i =0;i<x&&digitalRead(LS);i++){// as you read high and counter didn't reach the real distance
      
    Motion(0 , 100, 0) ; // move motors forward
    }// for loop
}// if f
if (y=='b'&&angle==0){
  for (int i =0;i<x&&digitalRead(LS);i++){// as you read high and counter didn't reach the real distance
      
           Motion(1 , 100, 0);  // move backward
    
    }// for loop
  
}// if b
 Motion(6 , 0, 0); // STOP!
}// angle funtion will be added by ashraf later
//==================================================//
