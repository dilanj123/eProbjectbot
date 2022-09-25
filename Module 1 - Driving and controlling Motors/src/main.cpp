#include <Arduino.h>

// Assigned pinouts of Arduino Uno and defines each pin for the code
#define PWMA 9
#define AI1 8
#define AI2 7
#define BI1 5
#define BI2 4
#define PWMB 3


void setup() 
{
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
  analogWrite (PWMA, speed);   // Set speed for Motor A

  // Motor B move forwards
  digitalWrite(BI1, LOW );
  digitalWrite(BI2, HIGH  );
  
  analogWrite (PWMB, speed);   // Set speed for Motor B
  
  return 0; // Note: Not necessary by C++ requires a function to return a value.
}

// Function programs rover to move backwards
int backward(int speed)
{
  // Motor A move backwards
  digitalWrite(AI1, LOW  );
  digitalWrite(AI2, HIGH );
  analogWrite (PWMA, speed);   // Set speed for Motor A


  // Motor B move backwards
  digitalWrite(BI1, LOW  );
  digitalWrite(BI2, HIGH );
  analogWrite (PWMB, speed);   // Set speed for Motor B
  return 0;
}

// Function programs rover to accelerate
int accelerate()
{  
  // Motor A move forwards
  digitalWrite(AI1, HIGH );
  digitalWrite(AI2, LOW  );

  // Motor B move forwards
  digitalWrite(BI1, HIGH );
  digitalWrite(BI2, LOW  );

  int i = 80;
  while (i < 255)     // While Loop increases value of 'i' increasing the velocity every 100ms. 
  {
  analogWrite(PWMA, i);  
  analogWrite(PWMB, i);
  i = i + 5;
  delay (100);
  }
  return i; 
}

// Function programs rover to deccelerate
int deccelerate()
{  
  // Motor A move forwards
  digitalWrite(AI1, HIGH );
  digitalWrite(AI2, LOW  );

  // Motor B move forwards
  digitalWrite(BI1, HIGH );
  digitalWrite(BI2, LOW  );
  
  int i = 255;
  while (i > 80)    // While Loop decreases value of 'i' decreasing the velocity every 100ms.
  {
  analogWrite(PWMA, i);  
  analogWrite(PWMB, i);
  i = i - 5;
  delay (100);
  }
  return 0; 
}

// Main Loop
void loop() 
{
  // Move Forwards (Motor A forwards, Motor B forwards)
  forward(255);
}