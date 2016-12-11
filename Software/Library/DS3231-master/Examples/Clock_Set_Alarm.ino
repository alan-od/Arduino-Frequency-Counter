/*
 DS3231 Clock Set Alarm
 John E.D. Edwards
 July 21st 2014
 
Demo of setting Alarms on DS3231.
 
Turn on the serial monitor after loading this and press reset
to check if things are working as they should.
This is a one-shot prog so no loop code.
 
 */
// Includes Here.
#include <DS3231.h>
#include <Wire.h>

// Declarations Here.
DS3231 Clock;
bool Century=false;
bool h12Hr;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADoW, A12h, Apm;
int Aval,Adow;
byte year, month, date, DoW, hour, minute, second;

void setup() {
  // Start the I2C interface
  Wire.begin();
  // Start the serial interface
  Serial.begin(9600);
  // Set Alarm to fire at 12:34:56 on the 23rd of each month using 24H clock
  Serial.println("A1 to fire every minute at 30 Seconds");
  			//WARNING!! It is possible to set stupid values eg 43rd day of a month, or 27th Hour or 70th Minute
  			//The values shown for Alarm 1 & 2 are the 'acceptable' ranges or values
  			// There are two other sketches to help with Interupts
  			// 1) Clock_Read_Alarm.ino Displays settings for both alarms
  			// 2) Clock_Test_Int.ino Simple example of using an external interupt
  ADay=23; 		//If ADoW is False ADay Value is 1 to 31 or if ADoW is True ADay Value is 1 to 7
  AHour=12; 		// If A12h=False Hour is 00 to 23 or if A12h=True Hour is 01 to 12 
  AMinute=34; 		// Minutes = 00 to 59
  ASecond=30; 		// Seconds= 00 to 59
  ABits=14; 		//Match Type Values. 0=Day/Date, 8=Hrs/Min/Sec, 12=Min/Sec, 14=Sec, 15=Every Sec
  ADoW=false; 		//False= Match on Date, True= Match on DoW
  A12h=false; 		//False= Use 24Hour Clock format, True= Use 12Hour Clock format
  Apm=false; 		// If False time is 1AM to 12AM, if True time is 1PM to 12PM
  Clock.setA1Time(ADay, AHour, AMinute, ASecond, ABits, ADoW, A12h, Apm);
  Clock.turnOffAlarm(1);
  // Now to turn or attention to Alarm 2.
  /* The main difference with Alarm 2 is in the Alarm Mask Bits.
   it is only possible to fire the alarm down to a minute, i.e. you cannot specify
   it down to the second. All matches occur at 00 seconds
   */
  Serial.println("A2 to fire Every Minute at 00 Seconds");
  ADay=2; 		//If ADoW is False ADay Value is 1 to 31 or if ADoW is True ADay Value is 1 to 7
  AHour=7; 		//If A12h=False Hour is 00 to 23 or if A12h=True Hour is 01 to 12
  AMinute=25; 		// Minutes 00 to 59
  ABits=112; 		//Match Type Values. 0=Day/Date, 64=Hrs/Min, 96=Min, 112=Every Minute
  ADoW=false; 		//False= Match on Date, True= Match on DoW
  A12h=false; 		//False= Use 24Hour Clock format, True= Use 12Hour Clock format
  Apm=false; 		// If False time is 1AM to 12AM, if True time is 1PM to 12PM
  Clock.setA2Time(ADay, AHour, AMinute, ABits, ADoW, A12h, Apm);
  Clock.turnOffAlarm(2);
}

void loop() {

}






