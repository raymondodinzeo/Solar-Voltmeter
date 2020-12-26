# Solar-Voltmeter
Arduino based voltmeter 
This project was started to develop a meter to measure the voltage of my solar panel charged batteries. The voltage divider in the circuit reduces the battery voltage (up to 22V) down to a maximum of 5V for the analog input of the arduino. The arduino operates a 7 segment display via a MAX7219. The programme initialises by pressing reset and samples the voltage for a short period of time before going into low power mode. 
