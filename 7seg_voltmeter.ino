//Programme to measure and display voltage (0 to 22) on a 4 digit 7 segment display
//and then shut down to low power. Press reset to wake up and test voltage.

//http://www.learningaboutelectronics.com/Articles/Max7219-4-digit-7-segment-LED-display-driver-circuit.php
//Article that this programme is based on, gives non-library access to 7219, great article.

#include <SPI.h>
#include <LowPower.h>
const int slaveSelect= 10; //pin used for !chip select
const int numberofDigits= 4;
int Vin = A0;
int number=0;

void setup()
{
//Serial.begin(9600); //for testing
SPI.begin(); //initialize SPI
pinMode(slaveSelect, OUTPUT);
digitalWrite(slaveSelect, LOW); //select Slave (7219)

//prepare the 7219 to display 7-segment data
sendCommand (12,1); //normal mode (default is shutdown mode)
sendCommand (15,0); //Display test off
sendCommand (10,8); //set medium intensity (range is 0-15)
sendCommand (11, numberofDigits); //digit scan limit (number of digits)
sendCommand (9, 255); //sets display to accept regular characters as input
digitalWrite(slaveSelect, HIGH); //deselect slave
}

void loop()
{
for (int repeats = 0; repeats <= 10; repeats++) //gives approx 11 seconds of readings before shutting down
{ 
int V = analogRead(Vin); //read voltage from A0;
// voltage divider R1 = 20k R2 = 68k reading 0 to 22v 
float voltage = float(V)/1024 * 22; //V is int (0 to 1024 from A0) cast to float
//divided by max to give proportion of max output multiplied by maximum voltage
//Serial.println(voltage);
number = int(voltage * 10 + 0.5); //gives voltage rounded to 1 DP (but without DP)
//Serial.println(number); (for testing) 
displayNumber(number); //format voltage for display
delay(1000);// gives voltage sampling delay
}
sendCommand (12, 0);//shut down display
LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

//function to display up to 4 digits on a 7-segment display
void displayNumber (int number)
{
for (int i=0; i <= numberofDigits; i++)//loop to display digits one at a time
{
byte character = number % 10; //get the value of the rightmost digit
if (number == 0 && i > 0)
{
character = 0xf; //sets character off if not required
}
//Serial.println(character);
if(i == 1)
sendCommand(numberofDigits-i, character | 128);// sets DP to give 1 Decimal place
else
sendCommand(numberofDigits-i, character);
number= number/10;
}
}

void sendCommand(int command, int value)
{
digitalWrite(slaveSelect, LOW); //chip select is active low
SPI.transfer(command);
SPI.transfer(value);
digitalWrite(slaveSelect,HIGH);
}
