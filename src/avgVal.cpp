/******************************************************
* Function name  : float avgVal(vector<float> vals)
* returns        : avg; the average value of the 18/20 
*                   samples
* arg1           : vals; a 20 item vector containing raw 
*                   sensor values.
* created by     : Colton Broughton
* Date created   : 2021-07-01
* Description    : Function takes in a 20 item vector,
*                   removes the first and last values 
*                   from  the vector and then averages
*                   the remaining 18 values which is
*                   then returned.
* Notes          : should be robust enough to handle 
*                   larger or smaller vector objects.
*******************************************************/

#include <Arduino.h>
#include <vector>
#include <numeric>

using std::vector;
using std::accumulate;

float avgVal(vector<float> vals)
{   
    vals.pop_back(); // removing the last value of the vector
    vals.erase(vals.begin());  // removing the first value of the vector
    int sum = accumulate(vals.begin(), vals.end(), 0.0); // calculating the sum of the vector after removing first and last element.
    int size = vals.size();  // getting the size of the vector to be used to compute the avg. (in case the sample size is changed later)
    float avg = sum / size;  // computing the avergae value of the remaining 18 samples.
    return avg; 
}