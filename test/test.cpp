/******************************************************************************
Mux_Analog_Output
SparkFun Multiplexer Output Example
Jim Lindblom @ SparkFun Electronics
August 15, 2016
https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

This sketch demonstrates how to use the SparkFun Multiplexer
Breakout - 8 Channel (74HC4051) to drive eight outputs using
four digital pins.

Hardware Hookup:
Mux Breakout ----------- Arduino
     S0 ------------------- 2
     S1 ------------------- 3
     S2 ------------------- 4
     Z -------------------- 5
    VCC ------------------- 5V
    GND ------------------- GND
    (VEE should be connected to GND)

Development environment specifics:
Arduino 1.6.9
SparkFun Multiplexer Breakout - 8-Channel(74HC4051) v10
(https://www.sparkfun.com/products/13906)
******************************************************************************/
#include <Arduino.h>
/////////////////////
// Pin Definitions //
/////////////////////
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zOutput = 5; // Connect common (Z) to 5 (PWM-capable)

void setup() 
{
  // Set up the select pins, as outputs
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], LOW);
  }
  pinMode(zOutput, OUTPUT); // Set up Z as an output
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.


void loop() 
{
  // Cycle from pins Y0 to Y7 first
  for (int pin=0; pin<=7; pin++)
  {
    // Set the S0, S1, and S2 pins to select our active
    // output (Y0-Y7):
    selectMuxPin(pin);
    // While the output is selected ramp the LED intensity up
    for (int intensity=0; intensity<=255; intensity++)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
    // Then bring the analog output value down:
    for (int intensity=255; intensity>=0; intensity--)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
  }
  // Now cycle from pins Y6 to Y1
  for (int pin=6; pin>=1; pin--)
  {
    selectMuxPin(pin); // Select the pin
    // Cycle the intensity up:
    for (int intensity=0; intensity<=255; intensity++)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
    // Then ramp the output down:
    for (int intensity=255; intensity>=0; intensity--)
    {
      analogWrite(zOutput, intensity);
      delayMicroseconds(DELAY_TIME);
    }
  }
}

