#include <algorithm>
#include <vector>
#include <numeric>
#include <math.h>

using std::vector;
float stdCalc(vector<float> vec)
{
    std::sort(vec.begin(), vec.end());  // sorting the vector based on size, we need not preserve original sort
    vector<float> noMinMaxVec = vector<float>(vec.size() - 2);  // New vector that is 2 items smaller, since we remove min and max
    std::copy(&vec[1], &vec[vec.size()-1], &noMinMaxVec[0]); // copying our old vector, minux the min and max, into the new vector.
    float sum = accumulate(noMinMaxVec.begin(), noMinMaxVec.end(), 0.0); // calculating the sum of the vector after removing min and max element.
    float size = noMinMaxVec.size();  // getting the size of the vector to be used to compute the avg. (in case the sample size is changed later)
    float mean = sum / size;  // computing the avergae value of the remaining N (for ORCASat: 18) samples.
    float num = 0;
    for (float val : noMinMaxVec)
    {
       num += pow((double)(val - mean), 2);
    }
    double stdMean = pow((double)(num / (noMinMaxVec.size()-1)), 0.5) /  pow(noMinMaxVec.size(), 0.5);
    return stdMean;
}