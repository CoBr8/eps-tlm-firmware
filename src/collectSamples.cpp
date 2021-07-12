/******************************************************
* Function name  : vector<float> collectSamples(int Pin, 
*                   Adafruit_ADS1115 ads)
* returns        : samples; a 20 item vector that was 
*                   collected
*                   from sampling the sensor 20 times over
*                   1 second. 
* arg1           : Pin; the ADS1115 input pin number (0-3)
* arg2           : ads; The ADS1115 ads instance to collect 
*                   the data from.
* created by     : Colton Broughton
* Date created   : 2021-07-07
* Description    : Collects 20 single-ended samples from 
*                   the ADS1X15 instance passed over 1 
*                   second. returns a 20 item vector.
* Notes          : 
*******************************************************/
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
