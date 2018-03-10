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

void Motion(byte Direction , byte MSpeed = 0 , byte RSpeed = 0);


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
       
      }
      BD = "";
    } else {
      BD += IBD;
    }
  }
}

void Motion(byte Direction , byte MSpeed = 0 , byte RSpeed = 0) {
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


