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
    int size = vals.size();
    float avg = sum / size;
    return avg;
}