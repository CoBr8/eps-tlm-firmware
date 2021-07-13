/* *****************************************************
Function name  : float avgVal(vector<float> vals)
returns        : avg; the average value of the 18/20 
                  samples
arg1           : vals; a 20 item vector containing raw 
                  sensor values.
created by     : Colton Broughton
Date created   : 2021-07-01
Description    : Function takes in a 20 item vector,
                  removes the first and last values 
                  from  the vector and then averages
                  the remaining 18 values which is
                  then returned.
Notes          : should be robust enough to handle 
                  larger or smaller vector objects.
****************************************************** */

#include <Arduino.h>
#include <vector>s
#include <numeric>
#include <algorithm>
using std::vector;
using std::accumulate;

float avgVal(vector<float> vals)
{   std::sort(vals.begin(), vals.end());  // sorting the vector based on size, we need not preserve original sort
    vector<float> noMinMaxVec = vector<float>(vals.size() - 2);  // New vector that is 2 items smaller, since we remove min and max
    std::copy(&vals[1], &vals[vals.size()-1], &noMinMaxVec[0]); // copying our old vector, minux the min and max, into the new vector.
    int sum = accumulate(noMinMaxVec.begin(), noMinMaxVec.end(), 0.0); // calculating the sum of the vector after removing min and max element.
    int size = noMinMaxVec.size();  // getting the size of the vector to be used to compute the avg. (in case the sample size is changed later)
    float avg = sum / size;  // computing the avergae value of the remaining N (for ORCASat: 18) samples.
    return avg; 
}