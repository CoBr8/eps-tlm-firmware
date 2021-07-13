# eps-tlm-firmware
Embedded Power Subsystem TeLemetry Module Firmware

## Function
The pinouts are setup to be outputs to control the mux pins. The loop does 2 things.
1. The first loop iterates through the ADS pins (0-3). The second loop iterates through the mux pins (0-7).
2. Every 10 seconds the line is printed out over Serial where it can be logged to a csv file and read. 

* Version 1.1.0:
    - Prints out Voltage readings in the range of +- 4.096V 
    - Uses functions to collect and average sensor readings
    - no error or min/max reading prinouts (upcoming version 1.2.0)
* Version 1.0.0
    - Initial version, reads and sends sensor data over Serial

## TODO:
* Convert sensor values to the correct output for each sensor and send over Serial. (iterate over functions? possible?)
* Implement error readings for those values that require it. 