#include <Arduino.h>

void selectMuxPin(byte pin, int sZero, int sOne, int sTwo) {
/******************************************************
* Function name  : void selectMuxPin(byte pin)
* returns        : void
* byte pin       : the desired channel of the mux (0-7)
* int sZero	 : the s0 connector pin for the mux
* int sOne	 : the s1 connector pin for the mux
* int sTwo	 : the s2 connector pin for the mux
* created by     : Colton Broughton, adapted from sparkfun
* Date created   : 2021-06-25
* Description    : switches the mux to the desired I/O. Used
			for the 74HC4051 and similar muxes
* Notes          :	Input       | Channel ON
			E  S2 S1 S0 |
			L  L  L  L  | Y0 to Z
			L  L  L  H  | Y1 to Z
			L  L  H  L  | Y2 to Z
			L  L  H  H  | Y3 to Z
			L  H  L  L  | Y4 to Z
			L  H  L  H  | Y5 to Z
			L  H  H  L  | Y6 to Z
			L  H  H  H  | Y7 to Z
			H  X  X  X  | mux off
				H:= high voltage
				L:= low voltage 
				X:= disregarded
*******************************************************/
  const int selectPins[3] = {sZero, sOne, sTwo};
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}