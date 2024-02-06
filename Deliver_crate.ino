#include <Servo.h>

int IN1 = 12;
int IN2 = 11;
int IN3 = 10;
int IN4 = 9;
int ENA = 13;
int ENB = 8;

int leftMotor;
int rightMotor;

int leftIR = 2;
int midIR = 3;
int rightIR = 4;
int lIRVal;
int mIRVal;
int rIRVal;

Servo crateServo;
int servoPin = 6;
int pos = 0;


void setup() {
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);
pinMode (IN3, OUTPUT);
pinMode (IN4, OUTPUT);
pinMode (ENB, OUTPUT);
pinMode (ENA, OUTPUT);
digitalWrite (ENB, HIGH);
digitalWrite (ENA, HIGH);

pinMode (midIR, INPUT);
pinMode (leftIR, INPUT);
pinMode  (rightIR, INPUT);

crateServo.attach(servoPin); 

Serial.begin (9600);
}


void loop() {
  
lIRVal = digitalRead (leftIR);
mIRVal = digitalRead (midIR);
rIRVal = digitalRead (rightIR);

if (lIRVal == 1 && mIRVal == 0 && rIRVal == 1) {
  Serial.println ("On Track!");
  forwardM();
}
else if (lIRVal == 1 && mIRVal == 1  && rIRVal == 0) {
  Serial.println ("Off Left!");
  leftM ();  
}
else if (lIRVal == 0 && mIRVal == 1 && rIRVal == 1) {
  Serial.println ("Off Right!");
  rightM();  
}

else if (lIRVal == 0 && rIRVal == 0 && mIRVal == 0) {
  Serial.println ("Arrived at destination");
  stopCar();
  delay (1000);
  dropCargo();         
}

else if (lIRVal == 1 && rIRVal == 1 && mIRVal == 1) {
  Serial.println ("No Track");
  rightM();
}

}


void setSpeed (int leftVal, int rightVal) {
analogWrite (ENA, leftVal); //analog write enablers to control speed
analogWrite (ENB, rightVal);
}

void forwardM() {
leftMotor = 140;
rightMotor = 130;
setSpeed (leftMotor,rightMotor);

digitalWrite (IN1, LOW);
digitalWrite (IN2, HIGH);
digitalWrite (IN3, HIGH);
digitalWrite (IN4, LOW);
}

void backwardM() {
digitalWrite (IN1, HIGH);
digitalWrite (IN2, LOW);
digitalWrite (IN3, HIGH);
digitalWrite (IN4, LOW);
}

void rightM() {
leftMotor = 130;
rightMotor = 130;
setSpeed (leftMotor,rightMotor);

digitalWrite (IN1, LOW);
digitalWrite (IN2, LOW);
digitalWrite (IN3, HIGH);
digitalWrite (IN4, LOW);
}

void leftM() {
leftMotor = 130;
rightMotor = 130;
setSpeed (leftMotor,rightMotor);

digitalWrite (IN1, LOW);
digitalWrite (IN2, HIGH);
digitalWrite (IN3, LOW);
digitalWrite (IN4, LOW);
}

void stopCar() {
digitalWrite (IN1, LOW);
digitalWrite (IN2, LOW);
digitalWrite (IN3, LOW);
digitalWrite (IN4, LOW);
}

void dropCargo() {
  static bool cargoDelivered = true;
  
  if(cargoDelivered) {
    
    for (pos = 0; pos<= 100; pos += 1){
    crateServo.write(pos);
    delay(50);
    }
    
   for (pos = 100; pos<= 0; pos += 1){
    crateServo.write(pos);
    delay(50);
    } 
     
  }
  cargoDelivered = false;
  return cargo
