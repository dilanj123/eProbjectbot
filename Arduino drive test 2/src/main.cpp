#include <Arduino.h>

// Assigned pinouts of Arduino Uno and defines each pin for the code
#define ENA 9
#define IN1 8
#define IN2 7
#define IN3 5
#define IN4 4
#define ENB 3


void setup() 
{
  // Set all the motor controls pins to output pins (pinouts)
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

// Function programs rover to move forward
int forward(int speed)
{
  // Motor A move forwards
  digitalWrite(IN1, LOW );
  digitalWrite(IN2, HIGH  );
  analogWrite (ENA, speed);   // Set speed for Motor A

  // Motor B move forwards
  digitalWrite(IN3, LOW );
  digitalWrite(IN4, HIGH  );
  
  analogWrite (ENB, speed);   // Set speed for Motor B
  
  return 0; // Note: Not necessary by C++ requires a function to return a value.
}

// Function programs rover to move backwards
int backward(int speed)
{
  // Motor A move backwards
  digitalWrite(IN1, LOW  );
  digitalWrite(IN2, HIGH );
  analogWrite (ENA, speed);   // Set speed for Motor A


  // Motor B move backwards
  digitalWrite(IN3, LOW  );
  digitalWrite(IN4, HIGH );
  analogWrite (ENB, speed);   // Set speed for Motor B
  return 0;
}

// Function programs rover to accelerate
int accelerate()
{  
  // Motor A move forwards
  digitalWrite(IN1, HIGH );
  digitalWrite(IN2, LOW  );

  // Motor B move forwards
  digitalWrite(IN3, HIGH );
  digitalWrite(IN4, LOW  );

  int i = 80;
  while (i < 255)     // While Loop increases value of 'i' increasing the velocity every 100ms. 
  {
  analogWrite(ENA, i);  
  analogWrite(ENB, i);
  i = i + 5;
  delay (100);
  }
  return i; 
}

// Function programs rover to deccelerate
int deccelerate()
{  
  // Motor A move forwards
  digitalWrite(IN1, HIGH );
  digitalWrite(IN2, LOW  );

  // Motor B move forwards
  digitalWrite(IN3, HIGH );
  digitalWrite(IN4, LOW  );
  
  int i = 255;
  while (i > 80)    // While Loop decreases value of 'i' decreasing the velocity every 100ms.
  {
  analogWrite(ENA, i);  
  analogWrite(ENB, i);
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