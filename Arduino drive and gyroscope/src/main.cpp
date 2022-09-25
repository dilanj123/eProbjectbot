#include <Arduino.h>
#include "Wire.h"

#include <MPU6050_light.h>
#define ENA 9
#define IN1 8
#define IN2 7
#define IN3 5
#define IN4 4
#define ENB 3

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
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
}

int forward(float left, float right){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, (left));  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, (right));
  return 0;
}

int total_x = 0;
int average_x = 0;
float prev_angle = 0;
float difference = 0;
float offset = 0;

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