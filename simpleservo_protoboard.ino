#include <Arduino.h>

const int servopin = A3; // set servo pin
const int potone = A2;  // analog pin used to connect the potentiometer
const int pottwo = A1;  // analog pin used to connect the potentiometer
const int modepin = 1; // digital pin for reading mode switch input
const int ledpin = 0; // digital pin for controlling LED

int valone;    // variable to read the value from the analog pin
int valtwo;    // variable to read the value from the analog pin
int valcheck;  // variable to check for value differences to see if pot is being used

int mode; // variable for reading mode switch

void setup() {
  pinMode(servopin, OUTPUT); // initalize pin 0 for servo
  
  pinMode(potone, INPUT); // intialize A3 pin for potentiomter 1 input
  pinMode(pottwo, INPUT); // intialize A3 pin for potentiomter 2 input
  
  pinMode(modepin, INPUT); // initialize digital pin for reading mode switch input

  pinMode(ledpin, OUTPUT); // initialize digital pin for lighting up LED
}

void loop() {
  mode = digitalRead(modepin);
  
  valone = analogRead(potone); // read potentiomter one, values ranging from 0-1023
//  delay(1); // short delay
  valcheck = analogRead(potone); // check if potentiometer value has changed
  if (valcheck - valone >= 1) { // if the potentiometer is being moved
    digitalWrite(ledpin, HIGH); // turn on LED
  }
  else {
    digitalWrite(ledpin, LOW); // else, turn off LED
  }
  valone = map(valone, 0, 1023, 600, 2300); // only let valone go up to 2300, because valtwo will always be at least 100 greater, and max value is 2400
  
  valtwo = analogRead(pottwo); // read potentiomter one, values ranging from 0-1023
  valtwo = map(valtwo, 0, 1023, 600, 2400); 

  if (mode == 1) { // check if switch is high, manual servo control
//    for(int i=0; i<50; i++) { // go to valtwo
//    digitalWrite(servopin, HIGH);
//    delayMicroseconds(valtwo); // use second potentiometer value to control servo manually
//    digitalWrite(servopin, LOW);
//    //delayMicroseconds(valtwo);
//    delay(20);
//    }
//    delay(1000);
    digitalWrite(servopin, HIGH);
    delayMicroseconds(valtwo); // use second potentiometer value to control servo manually
    digitalWrite(servopin, LOW);
    delay(20);
  }
  else if (mode == 0) { // else if switch is low, auto servo control

    if (valtwo <= valone) { // make sure that valtwo is always greater than valone
      valtwo = valone + 100;
    }
    
    for(int i=0; i<50; i++) { // go to valone
    digitalWrite(servopin, HIGH);
    delayMicroseconds(valone);
    digitalWrite(servopin, LOW);
    delay(10);
    }
    delay(100);
    
    for(int j=0; j<50; j++) { // go to valtwo
      digitalWrite(servopin, HIGH);
      delayMicroseconds(valtwo);
      digitalWrite(servopin, LOW);
      delay(10);
    }
    delay(100);     
  } 
}
