#define MENA 3
#define MENB 4
#define MIN1 22
#define MIN2 23
#define MIN3 24
#define MIN4 25

void Motion(byte Direction , byte MSpeed = 0 , byte RSpeed = 0);

void setup() {
  pinMode(MENA, OUTPUT);
  digitalWrite(MENA, LOW);
  pinMode(MENB, OUTPUT);
  digitalWrite(MENB, LOW);
  pinMode(MIN1, OUTPUT);
  digitalWrite(MIN1, LOW);
  pinMode(MIN2, OUTPUT);
  digitalWrite(MIN2, LOW);
  pinMode(MIN3, OUTPUT);
  digitalWrite(MIN3, LOW);
  pinMode(MIN4, OUTPUT);
  digitalWrite(MIN4, LOW);


}



void loop() {

  float LinearSpeed = analogRead(A0);
  LinearSpeed = (LinearSpeed * 100) / 1023;
  float RotationSpeed = analogRead(A1);
  RotationSpeed = (RotationSpeed * 100) / 1023;
  float D = analogRead(A2);
  D = (D * 100) / 1023;
  if ( D <= 10) {
    Motion(0 , LinearSpeed, RotationSpeed);

  } else if ( D <= 20) {
    Motion(1 , LinearSpeed, RotationSpeed);

  } else if ( D <= 30) {
    Motion(2 , LinearSpeed, RotationSpeed);

  } else if ( D <= 40) {
    Motion(3 , LinearSpeed, RotationSpeed);

  } else if ( D <= 50) {
    Motion(4 , LinearSpeed, RotationSpeed);

  } else if ( D <= 60) {
    Motion(5 , LinearSpeed, RotationSpeed);

  } else if ( D <= 70) {
    Motion(6);
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
        digitalWrite(MIN1, HIGH);
        digitalWrite(MIN2, LOW);
        digitalWrite(MIN3, HIGH);
        digitalWrite(MIN4, LOW);
        analogWrite(MENA , PMWLV);
        analogWrite(MENB , PMWLV);
        break;
      }
    case 1: {
        digitalWrite(MIN1, LOW);
        digitalWrite(MIN2, HIGH);
        digitalWrite(MIN3, LOW);
        digitalWrite(MIN4, HIGH);
        analogWrite(MENA , PMWLV);
        analogWrite(MENB , PMWLV);
        break;
      }
    case 2: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWRV);
          analogWrite(MENB , PMWLV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWRV);
          analogWrite(MENB , PMWLV);
        } else {
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWLV);
        }
        break;
      }
    case 3: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWRV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWRV);
        } else {
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWLV);
        }
        break;
      }
    case 4: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWRV);
          analogWrite(MENB , PMWLV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, HIGH);
          digitalWrite(MIN2, LOW);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWRV);
          analogWrite(MENB , PMWLV);
        } else {
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWLV);
        }

        break;
      }
    case 5: {
        if ( RSpeed >= 0 && RSpeed <= 50) {
          PMWRV = 100 - (RSpeed * 2);
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWRV);
        } else if (RSpeed > 50 && RSpeed <= 100) {
          PMWRV = (RSpeed * 2) - 100;
          PMWRV = (PMWRV * PMWLV ) / 100;
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, HIGH);
          digitalWrite(MIN4, LOW);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWRV);
        } else {
          digitalWrite(MIN1, LOW);
          digitalWrite(MIN2, HIGH);
          digitalWrite(MIN3, LOW);
          digitalWrite(MIN4, HIGH);
          analogWrite(MENA , PMWLV);
          analogWrite(MENB , PMWLV);
        }

        break;
      }
    case 6: {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(MIN1, LOW);
        digitalWrite(MIN2, LOW);
        digitalWrite(MIN3, LOW);
        digitalWrite(MIN4, LOW);
        break;
      }
    default: {
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(MIN1, LOW);
        digitalWrite(MIN2, LOW);
        digitalWrite(MIN3, LOW);
        digitalWrite(MIN4, LOW);
        break;
      }
  }
}

