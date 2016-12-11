/*
DS3231_Interupt
John E.D. Edwards
July 21st 2014

Test of Interupt Routine for a DS3231 RTC.

Turn on the serial monitor after loading this and press reset
to check if things are working as they should.

*/
// Includes Here.
#include <DS3231.h>
#include <Wire.h>
// Declarations Here.
DS3231 Clock;
bool Century=false;
bool h12Hr;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits, prevSecond;
bool ADy, A12h, Apm;

byte year, month, date, DoW, hour, minute, second;


void setup ()
{
Serial.begin(9600);
Wire.begin();
Serial.println("Test of DS3231 Alarm1 and Alarm2");
attachInterrupt(1, INT1_ISR, FALLING);
prevSecond=0;
// Enable Alarms and Interupt
Clock.turnOnAlarm(1);
Clock.turnOnAlarm(2);
Clock.enableOscillator(true,true,0);
Clock.enableINTCN(true);
}


void loop ()
{
// Program will loop and print out the time every second
// Set the Alarms to something sensible so you do not have to wait days until you get an interupt!!!
// The sketch sketch_Clock_Set_Alarm defaults to Alarm 1 every minute at 30 seconds and Alarm2 every minute at 00 Seconds
    Clock.getTime(year, month, date, DoW, hour, minute, second);
    if (prevSecond != second) {
        Serial.print("Date and Time is ");
        Serial.print(date, DEC);
        Serial.print("/");
        Serial.print(month, DEC);
        Serial.print("/");
        Serial.print(year, DEC);
        Serial.print(" ");
        digitalClockDisplay();
        Serial.print('\n');
        prevSecond=second;
        //Test if Alarm Fired
        if (Clock.checkIfAlarm(1)==true) {
            Serial.println("Alarm 1 Fired!");
        }
        if (Clock.checkIfAlarm(2)==true) {
            Serial.println("Alarm 2 Fired!");
        }
    }
}
void digitalClockDisplay() {
  // digital clock display of the time
  printDigits(hour);
  Serial.print(":");
  printDigits(minute);
  Serial.print(":");
  printDigits(second);
}

void printDigits(int digits) {
  // utility function for digital clock display: prints leading 0
  if(digits > 59)
    Serial.print("--");
  else {
    if(digits < 10)
      Serial.print('0');
    Serial.print(digits);
  }
}

//Interrupt service routine for external interrupt on INT1 pin conntected to
//INT on DS3231
void INT1_ISR()
{
    //Keep this as short as possible. Possibly avoid using function calls
    Serial.println("External Interrupt detected!");
}
