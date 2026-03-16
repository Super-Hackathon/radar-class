#include <Servo.h>

Servo servo_1; // servo controller (multiple can exist)

// Edit to change the scanning state
// 1 = Fixed (No Scan)
// 2 = Medium Scan
// 3 = Fast Scan
// 4 = Slow Scan
// 5 = Customizable Scan
int ScanState = 1;

int StartAngle = 10;
int EndAngle = 170;
int StepAngle = 5;

int trig = 9; // trig pin for HC-SR04
int echo = 10; // echo pin for HC-SR04
int servo_pin = 11; // PWM pin for servo control

int pos = 0;    // servo starting position
float duration,distance;

void setup() {
  Serial.begin(9600);
  Serial.println("Radar Start");
  servo_1.attach(servo_pin); // start servo control
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  
}

void loop() {


 switch (ScanState) {

  case 1:  // Fixed State
    pos=90;
    //servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250); // delay to allow the servo to reach the desired position
    dist_calc(pos);
    break;
  case 2:  // Medium Scan
    for (pos = StartAngle; pos <= EndAngle; pos += StepAngle) { 
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    for (pos = EndAngle; pos >= StartAngle; pos -= StepAngle) {
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    break;
    
    case 3:  // Fast Scan
    
    for (pos = StartAngle; pos <= EndAngle; pos += StepAngle) { 
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(90); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    for (pos = EndAngle; pos >= StartAngle; pos -= StepAngle) {
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(90); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    break;
    
   case 4:  // Slow Scan 
    for (pos = StartAngle; pos <= EndAngle; pos += StepAngle) { 
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    for (pos = EndAngle; pos >= StartAngle; pos -= StepAngle) {
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500); // delay to allow the servo to reach the desired position
    dist_calc(pos);  
    }
    break;
   case 5:  // CUSTOM - Tune me!!!
    for (pos = 10; pos <= 170; pos += 3) { // goes from 10 degrees to 170 degrees
    // in steps of 3 degree
    servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100); // delay to allow the servo to reach the desired position
    dist_calc(pos);  }
    break;
  default:  // Default is fixed scanning at 90 deg
    pos=90;
    //servo_1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250); // delay to allow the servo to reach the desired position
    dist_calc(pos);
 }
}

float dist_calc(int pos){
  // trigger 40kHz pulse for ranging
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(echo,HIGH); // duration for pulse to reach detector (in microseconds)
  distance = 100.0*(343.0*(duration/2.0))/1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
 
  Serial.print(pos); // position of servo motor
  Serial.print(","); // comma separate variables
  Serial.println(distance); // print distance in cm
}
