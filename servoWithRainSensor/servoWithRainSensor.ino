// C++ code

#include <Servo.h>

// servo
Servo servo1;
int servoPin = 9;
int position;
int startPosition = 0;
int endPosition = 90;

// raindrop sensor
int sensorPin = A0;
int sensorValue;

// state
String state = "opened";


void setup()
{
  servo1.attach(servoPin);
  servo1.write(startPosition);
  pinMode(sensorPin, INPUT);
  
  // serial monitor
  Serial.begin(9600);
}


void loop()
{
  sensorValue = analogRead(sensorPin);

  // serial monitor displays the signal value
  Serial.println(sensorValue);
  delay(10);

  if (sensorValue < 450 && state == "opened")
  {
    for (position = startPosition; position <= endPosition; position++)
    {
      servo1.write(position);
      delay(20);
    }
    
    state = "closed";
    delay(5000);
  }
  else if (sensorValue > 600 && state == "closed")
  {
    for (position = endPosition; position >= startPosition; position--)
    {
      servo1.write(position);
      delay(20);
    }
    
    state = "opened";
    delay(5000);
  }
}
