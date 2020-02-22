#include <SoftwareSerial.h>
//control mode definition
#define controlMode1 1
#define controlMode2 2
#define controlMode3 3
#define controlMode4 4 //OFF mode
//ATtiny 85 pin application definition
#define detectPin 1
#define controlPin 0
#define Rx 3
#define Tx 4

SoftwareSerial bluetooth(Rx, Tx);

char command;
uint8_t controlMode = 0;
boolean lastState = HIGH;

void setup() {
  bluetooth.begin(9600);
  pinMode(controlPin, OUTPUT);
  pinMode(detectPin, INPUT);
  lastState = digitalRead(detectPin);
}

void loop() {

  if (controlMode >= 4) {
    controlMode = 0;
  }

  boolean state = digitalRead(detectPin);
  if (state != lastState) {
    if (state == LOW) {
      controlMode++;
    }
    delay(50);
  }

  lastState = state;

  if (bluetooth.available() > 0) {
    if (controlMode >= 4) {
      controlMode = 0;
    }

    boolean state = digitalRead(detectPin);
    if (state != lastState) {
      if (state == LOW) {
        controlMode++;
      }
      delay(50);
    }

    lastState = state;

    command = bluetooth.read();

    switch (command) {
      case 's':

        while (controlMode != controlMode1) {
          digitalWrite(controlPin, HIGH);
          delay(200);
          digitalWrite(controlPin, LOW);
          delay(200);
          controlMode++;

          if (controlMode >= 4) {
            controlMode = 0;
          }
        }
        controlMode = controlMode1;
        break;

      case 'o':

        while (controlMode != controlMode2) {
          digitalWrite(controlPin, HIGH);
          delay(200);
          digitalWrite(controlPin, LOW);
          delay(200);
          controlMode++;
          if (controlMode >= 4) {
            controlMode = 0;
          }
        }
        controlMode = controlMode2;
        break;

      case 'g':

        while (controlMode != controlMode3) {
          digitalWrite(controlPin, HIGH);
          delay(200);
          digitalWrite(controlPin, LOW);
          delay(200);
          controlMode++;

          if (controlMode >= 4) {
            controlMode = 0;
          }
        }
        controlMode = controlMode3;
        break;

      case 'l':

        while (controlMode != controlMode4 && controlMode != 0) {
          digitalWrite(controlPin, HIGH);
          delay(200);
          digitalWrite(controlPin, LOW);
          delay(200);
          controlMode++;
        }
        if (controlMode >= 4) {
          controlMode = 0;
        }
        controlMode = controlMode4;
        break;
    }
  }
}
