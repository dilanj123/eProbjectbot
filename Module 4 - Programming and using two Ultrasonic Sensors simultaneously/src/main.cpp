#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_PIN_1 10
#define ECHO_PIN_1 10
#define TRIGGER_PIN_2 11
#define ECHO_PIN_2 11
#define MAX_DISTANCE 400

NewPing sonar1 (TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); 
NewPing sonar2 (TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);


float distance1, duration1, distance2, duration2;

int iteration1 = 5;
int iteration2 = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
}

void loop() {

  duration1 = sonar1.ping_median(iteration1);
  duration2 = sonar2.ping_median(iteration2);

  distance1 = (duration1/2)*0.03432;
  distance2 = (duration2/2)*0.03432;

  Serial.print("Distance = ");
  if(distance1 >= 400 || distance1 <= 2)
  {
    Serial.println("Sensor 1 Out of range");
  } 
  if(distance2 >= 400 || distance2 <= 2)
  {
    Serial.println("Sensor 2 Out of range");
  } 
  else{
    Serial.print("Sensor 1: ");Serial.print(distance1); Serial.print("cm          ");
    Serial.print("Sensor 2: ");Serial.print(distance2);Serial.println("cm"); 
    delay(10);
  }
  delay(10);
}