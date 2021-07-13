# eps-tlm-firmware
Embedded Power Subsystem TeLemetry Module Firmware

## Function
The pinouts are setup to be outputs to control the mux pins. The loop does 2 things.
1. The first loop iterates through the ADS pins (0-3). The second loop iterates through the mux pins (0-7).
2. Every 10 seconds the line is printed out over Serial where it can be logged to a csv file and read. 

## TODO:
* Convert sensor values to the correct output for each sensor and send over Serial.
* more Efficient way of storing and accessing data? 2d vector? 
* 