#include <Servo.h>
#include <SoftwareSerial.h>

#define HC_05_TXD_ARDUINO_RXD 10
#define HC_05_RXD_ARDUINO_TXD 11
#define MENA 22
#define MENB 23
#define MENA_B 24
#define MENB_B 25
#define MIN1 3
#define MIN2 4
#define MIN3 5
#define MIN4 6
#define SERVO 9

Servo myservo;
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
String BD = "";
char IBD= 0;
char IPBD = 0;

void Motion(byte Direction , byte MSpeed = 100 , byte RSpeed = 0);
void Drive_T();
int ping_read();
void anti_crush();

void setup() {
  pinMode(MENA, OUTPUT);
  digitalWrite(MENA, HIGH);
  pinMode(MENB, OUTPUT);
  digitalWrite(MENB, HIGH);
  pinMode(MENA_B, OUTPUT);
  digitalWrite(MENA_B, HIGH);
  pinMode(MENB_B, OUTPUT);
  digitalWrite(MENB_B, HIGH);
  pinMode(MIN1, OUTPUT);
  digitalWrite(MIN1, LOW);
  pinMode(MIN2, OUTPUT);
  digitalWrite(MIN2, LOW);
  pinMode(MIN3, OUTPUT);
  digitalWrite(MIN3, LOW);
  pinMode(MIN4, OUTPUT);
  digitalWrite(MIN4, LOW);
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
  BTSerial.println("Easy Driving Mode");
  while ((BD != "E") && (BD != "e")) {
    if (BTSerial.available()) {
      BD = char(BTSerial.read());
      if (BD == "F" || BD == "f" ) {
        if (IPBD == 'F') {
          Motion(0 , 100, 0);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'F';
        }
      } else if (BD == "B" || BD == "b") {
       if (IPBD == 'B') {
          Motion(1 , 100, 0);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'B';
        }
      } else if (BD == "R" || BD == "r" ) {
         if (IPBD == 'R') {
          Motion(2 , 100, 25);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'R';
        }
      } else if (BD == "L" || BD == "l") {
        if (IPBD == 'L') {
          Motion(3 , 100, 25);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'L';
        }
      } else if (BD == "V" || BD == "v") {
        if (IPBD == 'V') {
          Motion(4 , 100, 25);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'V';
        }
      } else if (BD == "W" || BD == "w") {
        if (IPBD == 'W') {
          Motion(5 , 100, 25);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'W';
        }
      } else if (BD == "A" || BD == "a") {
        if (IPBD == 'A') {
          Motion(2 , 100, 100);
        } else {
          Motion(6 , 0, 0);
          IPBD = 'A';
        }
      } else {
        Motion(6 , 0, 0);
        IPBD = 'S';
      }
    }
  }
  BTSerial.println("Trminate easy Driving Mode");
}

// read the distance infront of the ping
int ping_read(){
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

// if the distance less than 15 cm STOP!
void  anti_crush(){
  if (ping_read() <= 15 ){
  Motion(6);
  }
}
