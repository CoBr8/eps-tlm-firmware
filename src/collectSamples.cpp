#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <vector>
using std::vector;
vector<float> collectSamples(int Pin, Adafruit_ADS1115 ads)
{
    unsigned long timeVal=0;
    unsigned long interval=50; // 1000 milliseconds split between 20 samples thus: 1000 / 20 = 50
    vector<float> samples {};
    int count=0;
    do 
    {   
        float sensVal;
        if (millis() - timeVal > interval) 
        {   
            timeVal = millis();
            sensVal = ads.readADC_SingleEnded(Pin);
            samples.push_back(sensVal);
            count++;
        }
    } while (count < 20);
    return samples;
}
