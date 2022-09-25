#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include "NewPing.h"

#define TRIGGER_PIN 10
#define ECHO_PIN 10
#define MAX_DISTANCE 400
// Assigned pinouts of Arduino Uno and defines each pin for the code
#define PWMA 9
#define AI1 8
#define AI2 7
#define BI1 5
#define BI2 4
#define PWMB 3

MPU6050 mpu(Wire);
unsigned long timer = 0;
NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

float distance, duration;

int iterations = 5;
void setup() {
  Serial.begin(9600);
  Wire.begin();
 
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  // Set all the motor controls pins to output pins (pinouts)
  pinMode(PWMA, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}
// Function programs rover to move forward
int forward(int speed)
{
  // Motor A move forwards
  digitalWrite(AI1, LOW );
  digitalWrite(AI2, HIGH  );
  analogWrite(PWMA, speed); // Set speed for Motor A

  // Motor B move forwards
  digitalWrite(BI1, LOW );
  digitalWrite(BI2, HIGH  );

  analogWrite(PWMB, speed);// Set speed for Motor B

  return 0; // Note: Not necessary by C++ requires a function to return a value.
}

int clockwise(int speed){
  // Motor A move forwards (left)
  digitalWrite(AI1, HIGH );
  digitalWrite(AI2, LOW  );

  analogWrite(PWMA, speed); // Set speed for Motor A

  // Motor B move backwards (right)
  digitalWrite(BI1, LOW  );
  digitalWrite(BI2, HIGH );

  analogWrite(PWMB, speed);// Set speed for Motor B
  return 0;
}
int anticlockwise(int speed){
  // Motor A move backwards (left)
  digitalWrite(AI1, LOW );
  digitalWrite(AI2, HIGH  );

  analogWrite(PWMA, speed); // Set speed for Motor A

  // Motor B move forwards (right)
  digitalWrite(BI1, HIGH  );
  digitalWrite(BI2, LOW );

  analogWrite(PWMB, speed);// Set speed for Motor B
  return 0;
}

int MPU6050update()
{
  mpu.update();
  Serial.println(String(round(mpu.getAngleZ())));
  int m_angle = round(mpu.getAngleZ());
  return m_angle;
}

int rotate(int r_angle)
{ 
  int m_angle = 0;
  int initial_angle = MPU6050update();  
  while(m_angle != (-1*r_angle)){ 
    m_angle = MPU6050update()-initial_angle;
    if((millis()-timer)>1){ // print data every 10ms   
      timer = millis(); 
      if(r_angle > 0)  
      {
        clockwise(200);
      }
      else{
        anticlockwise(200);
      }
    }
  }
clockwise(0);
return 0;
}

void loop() {
  
  duration = sonar.ping_median(iterations);
  distance = (duration/2)*0.03432;

  Serial.print("Distance = ");
  if(distance >= 400 || distance <= 2)
  {
    Serial.println("Sensor 1 Out of range");
  } 
  else{
    forward(255);
    Serial.print("Sensor 1: ");Serial.print(distance); Serial.println("cm");
    
    if(distance <= 20){
      Serial.println("done");
      forward(0);
      delay(500);
      rotate(90);
      delay(500);
      duration = sonar.ping_median(iterations);
      distance = (duration/2)*0.03432;

      if(distance <= 20){
        delay(500);
        rotate(-90);
        duration = sonar.ping_median(iterations);
        distance = (duration/2)*0.03432;
        
        if(distance <= 20){
          rotate(-90);
          delay(500);
        }
      }
      delay(10);
    }
  }
}
