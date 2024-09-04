// C++ code
// 14 May 2023

#include <Servo.h>

// Servo
Servo servo1;
int servoPin = 9;
int position;
int startPosition = 0;
int endPosition = 90;

// Raindrop sensor
int sensorPin = A0;
int sensorValue;

// Bluetooth
char bluetoothValue = '*';
// bluetooth values code
char automaticMode = 'a';
char manualMode = 'm';
char openOrder = 'o';
char closeOrder = 'c';

// State
String canopyState = "opened";
bool sensorState = true; // true = sensor on, false = sensor off


void setup()
{
  servo1.attach(servoPin);
  servo1.write(startPosition);
  pinMode(sensorPin, INPUT);

  // serial communication
  Serial.begin(9600);
}


void loop()
{
  if (Serial.available() > 0)
  {
    bluetoothValue = Serial.read();
    delay(10);
    
    // Serial monitor displays the bluetooth value
    Serial.println(bluetoothValue);
    delay(10);
    
    if (bluetoothValue == automaticMode)
    {
      sensorState = true;
    }
    else if (bluetoothValue == manualMode)
    {
      sensorState = false;
    }
  }

  if (sensorState) // Auto mode
  {
    sensorValue = analogRead(sensorPin);

    // Serial monitor displays the raindrop sensor value
    Serial.println(sensorValue);
    delay(10);

    if (sensorValue < 450 && canopyState == "opened")
    {
      // Close the canopy
      for (position = startPosition; position <= endPosition; position++)
      {
        servo1.write(position);
        delay(20);
      }

      canopyState = "closed";
      delay(1000);
    }
    else if (sensorValue > 600 && canopyState == "closed")
    {
      // Open the canopy
      for (position = endPosition; position >= startPosition; position--)
      {
        servo1.write(position);
        delay(20);
      }

      canopyState = "opened";
      delay(1000);
    }
  }
  else // Manual mode
  {
    if (bluetoothValue == closeOrder && canopyState == "opened")
    {
      // Close the canopy
      for (position = startPosition; position <= endPosition; position++)
      {
        servo1.write(position);
        delay(20);
      }

      canopyState = "closed";
      delay(1000);
    }
    else if (bluetoothValue == openOrder && canopyState == "closed")
    {
      // Open the canopy
      for (position = endPosition; position >= startPosition; position--)
      {
        servo1.write(position);
        delay(20);
      }

      canopyState = "opened";
      delay(1000);
    }
  }
}
