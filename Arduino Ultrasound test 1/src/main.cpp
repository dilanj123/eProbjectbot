#include <Arduino.h>
#include "NewPing.h"
#define TRIGGER_PIN 10
#define ECHO_PIN 10
#define MAX_DISTANCE 400

NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

float distance, duration;

int iterations = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
}

void loop() {

  duration = sonar.ping_median(iterations);

  distance = (duration/2)*0.03432;

  Serial.print("Distance = ");
  if(distance >= 400 || distance <= 2)
  {
    Serial.println("Out of range");
  } 
  else{
    Serial.print(distance); Serial.println("cm");
    delay(10);
  }
  delay(10);
}