#include <Arduino.h>
#include "Wire.h"

#include <MPU6050_light.h>
#define PWMA 9
#define AI1 8
#define AI2 7
#define BI1 5
#define BI2 4
#define PWMB 3

MPU6050 mpu(Wire);
unsigned long timer = 0;

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

int forward(float left, float right){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  analogWrite(PWMA, (left));  
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
  analogWrite(PWMB, (right));
  return 0;
}

void loop() {
  mpu.update();
  if((millis()-timer)>1){ // print data every 10ms
    timer = millis();  	
    Serial.println(String(mpu.getAngleZ()));
    float angle_off = abs(mpu.getAngleZ());

    float high_power = 220+(10*angle_off);
    float low_power = 220-(10*angle_off);
    if (high_power >= 255)
    {
      high_power = 255;
    }
    if (low_power <= 0)
    {
      low_power = 0;
    }
    if (mpu.getAngleZ() > 0.25)
    {
      forward(low_power, high_power);
      Serial.println("l");
    }
    else if(mpu.getAngleZ() < -0.25)
    {
      forward(high_power,low_power);
      Serial.println("r");
    }
    else
    {
      forward(255, 255);
    }
  }

}