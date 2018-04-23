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
//Line Tracking Sensors
#define S1P 50
#define S2P 42
#define S3P 45
#define S1G 46
#define S2G 51
#define S3G 52
#define S1S 48
#define S2S 53
#define S3S 43

Servo myservo;
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
String BD = "";
char IBD = 0;
char IPBD = 0;

void Motion(byte Direction , byte MSpeed = 100 , byte RSpeed = 0);
void Drive_T();
int ping_read();
bool anti_crush();
void servo_cheak(char a);
void Follow();

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
  
  //Line Tracking Sensors Pins
  pinMode(S1P, OUTPUT);
  digitalWrite(S1P, HIGH);
  pinMode(S2P, OUTPUT);
  digitalWrite(S2P, HIGH);
  pinMode(S3P, OUTPUT);
  digitalWrite(S3P, HIGH);
  pinMode(S1G, OUTPUT);
  digitalWrite(S1G, LOW);
  pinMode(S2G, OUTPUT);
  digitalWrite(S2G, LOW);
  pinMode(S3G, OUTPUT);
  digitalWrite(S3G, LOW);
  pinMode(S1S, INPUT);
  pinMode(S2S, INPUT);
  pinMode(S3S, INPUT);

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
      } else if (BD == "LT" || BD == "lt") {
        Follow();
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


void Follow() {
  bool L1 ; bool Mid ; bool R1;
  bool White = 0;
  bool Black = 1;
  BTSerial.println("Line Tracking Mode");
  while ((BD != "E") && (BD != "e")) {
    if (BTSerial.available()) {
      BD = char(BTSerial.read());
    }
    if  (BD == "I" || BD == "i") {
      L1 = digitalRead(S1S);
      Mid = digitalRead(S2S);
      R1 = digitalRead(S3S);
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
