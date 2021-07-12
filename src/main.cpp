#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <vector>

#include "selectMuxPin.h"
#include "collectSamples.h"
#include "avgVal.h"
#include "appendLineToFile.h"

using std::vector;

int timeMod = 2; // divisor, used to decrease the interval times for testing. set to 1 for actual interval times. 

int adcPins[4] {0, 1, 2, 3}; // ADC pin numbers to stop from unnamed numbers popping up
int mux1S [3] {5, 6, 7};    // Mux channel select pins for the 1st mux

unsigned long mux1Times [8] {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long mux1Intrvl [8] { 20000,  90000,  90000,  90000,  20000,  20000, 270000, 270000};
unsigned long outTime=0;

const unsigned long printIntrvl=10000; // output sensor data every 10 seconds.

adsGain_t mux1Gain [8] {GAIN_TWOTHIRDS, GAIN_SIXTEEN,   GAIN_FOUR, GAIN_TWOTHIRDS,\
                        GAIN_ONE,       GAIN_TWOTHIRDS, GAIN_ONE,  GAIN_TWO}; // gain array for adjusting the ADC to be within a proper range for each sensor value. this is adc pin 0 or mux 1
Adafruit_ADS1115 ads;	// Construct an ads1115 instance to read single ended values
vector<float> mux1Vals = {0,0,0,0,0,0,0,0};

void setup() 
{   
    Serial.begin(9600); // serial output to print out the sensor values
    delay(5000);        // included only to allow vscode + platformio to catch the Serial print initially
    Serial.println("Serial init complete");
    ads.begin();  // Initialize ads1115 at the default address 0x48
    for (int i=0; i < 3; i++) 
    {
        pinMode(mux1S[i], OUTPUT);
    }
}

void loop() {
    for (int muxPin=0; muxPin<8; muxPin++) 
    {
        if (millis() - mux1Times[muxPin] > mux1Intrvl[muxPin] / timeMod)  // check if the last time the pin was polled is greater than the sampling interval
        {
            selectMuxPin(muxPin, mux1S);  // switches the mux to the pin we're interested in
            ads.setGain(mux1Gain[muxPin]);
            vector<float> sensValsMux1 = collectSamples(adcPins[0], ads);  // returns a vector of 20 sensor readings over 1 second. 
            float sensValMux1 = avgVal(sensValsMux1);
            mux1Vals[muxPin] = sensValMux1;
            mux1Times[muxPin] = millis();  // storing the pin access time to be checked next loop
        }
        if (millis() - (outTime) > printIntrvl / timeMod) // I only want to print the output (ie send to file) every 10/timeMod seconds!
        { 
            String outString = "";
            for (int i : mux1Vals)
            {
                float mux1Volt = ads.computeVolts(i);
                outString += (String)mux1Volt + ",";
            }
            Serial.println(outString);
            outTime = millis();
        }
    }   
}