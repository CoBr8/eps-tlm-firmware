#include <Arduino.h>
#include <fstream>
void appendLineToFile(std::string filepath, String line)
{   
    using namespace std;
    ofstream file;
    file.open(filepath, ios::out | ios::app);
    file << line << std::endl;
}