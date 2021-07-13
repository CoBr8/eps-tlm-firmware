#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <vector>

#include "selectMuxPin.h"
#include "collectSamples.h"
#include "avgVal.h"

using std::vector;

int timeMod = 2; // divisor, used to decrease the interval times for testing. set to 1 for actual interval times. 

int adcPins[4] {0, 1, 2, 3}; // ADC pin numbers to stop from unnamed numbers popping up

int muxS [3] {5,  6,  7 }; 
/* muxS:
* All muxes could use the same three pins to do selection. Since we loop we're only ever pulling
*  information from one ADS pin at a time.
*/
unsigned long muxTimes [32] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
/* muxTimes:
* keeping track of the time since the sensor was last polled. initially none of them are polled 
*/
unsigned long muxIntrvl [32] { 20000,  90000,  90000,  90000,  20000,  20000, 270000, 270000,\
                              270000, 270000, 270000, 270000, 270000, 270000, 270000, 270000,\
                              270000,  90000,  90000, 270000,  90000,  90000,  90000,  90000,\
                               90000,  90000,  90000,  20000,  20000, 270000,  30000,  30000,\
                             }; // last two 30s sensors are not utilized.
unsigned long outTime=0; // keeping track of the last time we sent data over Serial
const unsigned long printIntrvl=10000; // output sensor data every 10 seconds.
vector<float> muxVals = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // init all mux values to start at zero. 

Adafruit_ADS1115 ads;	// Construct an ads1115 instance to read single ended values

void setup() 
{   
    Serial.begin(9600); // serial output to print out the sensor values
    ads.begin();  // Initialize ads1115 at the default address 0x48
    ads.setGain(GAIN_ONE);
    for (int i=0; i < 3; i++) 
    {
        pinMode(muxS[i], OUTPUT);
    }
}
void loop() {
    for (int pin : adcPins)  // cycling through the adc pins (0-3)
    {
        for (int muxPin=0; muxPin<8; muxPin++) // cycling through the mux pins (0-7)
        {
            if (millis() - muxTimes[muxPin] > muxIntrvl[muxPin] / timeMod)  // check if the last time the pin was polled is greater than the sampling interval
            {
                selectMuxPin(muxPin, muxS);  // switches the mux to the pin as defined by loop
                vector<float> sensVals = collectSamples(pin, ads);  // returns a vector of 20 sensor readings over 1 second. 
                float sensVal = avgVal(sensVals);
                muxVals[muxPin + pin*8] = sensVal;
                muxTimes[muxPin] = millis();  // storing the pin access time to be checked next loop
            }
            if (millis() - (outTime) > printIntrvl / timeMod) // I only want to print the output (ie send to file) every 10/timeMod seconds!
            { 
                String outString = "";
                for (int i : muxVals)
                {
                    float muxVolt = ads.computeVolts(i);
                    outString += (String)muxVolt + ",";
                }
                Serial.println(outString);
                outTime = millis();
            }
        }  
    }
}
