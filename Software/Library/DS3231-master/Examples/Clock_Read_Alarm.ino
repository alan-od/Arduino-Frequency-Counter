/*
DS3231_Read_Alarm_Settings
 John E.D. Edwards
 July 21st 2014
 
Demo of reading Alarm Settings for a DS3231.
 
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
bool ADy, A12h, Apm;
int Aval,Adow;
byte year, month, date, DoW, hour, minute, second;

void setup() {
// WARNING!! It is possible to have set stupid values eg 43rd day of a month, or 27th Hour or 70th Minute
// into the Alarm Registers,No testing is done to see the values are correct.
// If my sketch_Set_Alarm has been used to set the Alarms there should be no 'funnies'
// Once you are happy with the Setting and Reading of the Alarms there is a sketch to test an external interupt
// Simple test of using an external interupt sketch_Clock_Test_Int. 

  // Start the I2C interface
  Wire.begin();
  // Start the serial interface
  Serial.begin(9600);
  // Get all the Alarm 1 Details
  Clock.getA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);
  ABits	= ABits & 0b00001111; //Mask out only A1 bits
  // Start to Check the Alarms.
  Serial.print('\n');
  Serial.println("--------Alarm 1 Settings---------");
  // Display Alarm 1 information
  isEnabled(1); 
  // Show if 12 or 24 Hour Clock
  clockMode();
  // Now explain when the Alarm will be triggered.
  fireWhen(1);

  Serial.print('\n');
  // End of Alarm 1 Details
  //---------------------------------------------
  // Get all the Alarm 2 Details
  Clock.getA2Time(ADay, AHour, AMinute, ABits, ADy, A12h, Apm);
  ABits	= ABits & 0b01110000; //Mask out only A2 bits
  ASecond=0;
  // Start to Check the Alarms.
  Serial.print('\n');
  Serial.println("--------Alarm 2 Settings---------");
  // Display Alarm 2 information
  isEnabled(2); 
  // Show if 12 or24 Hour Clock
  clockMode();
  // Now explain when the Alarm will be triggered.
  fireWhen(2);
  Serial.print('\n');
  Serial.print("--------Alarms Fired?---------");
  Serial.print('\n');
  // Indicate whether an alarm went off
  if (Clock.checkIfAlarm(1)) {
    Serial.print(" A1 Fired");
  }
  if (Clock.checkIfAlarm(2)) {
    Serial.print(" A2 Fired");
  }
  Serial.print('\n');
  Serial.print("--------EOSC Settings---------");
  Serial.print('\n');
  if (Clock.CheckEOSC()) {
    Serial.print("True");
  } 
  else {
    Serial.print("False");
  }
  Serial.print('\n');
  Serial.print("--------INTCN Settings---------");
  Serial.print('\n');
  if (Clock.CheckINTCN()) {
    Serial.print("True");
  } 
  else {
    Serial.print("False");
  }
}

// Subroutines
void fireWhen(int Alarm){
  Aval=int(ABits);
  Serial.println(ABits,DEC);
  switch(Aval)
  {
  case 0:
    if (ADy) {
      if (Alarm != 2){
        Serial.println("Alarm will fire when Day,hours,minutes and seconds match.");
      }
      else {  
        Serial.println("Alarm will fire when Day,hours and minutes match.");
      }
      Serial.println("Assuming Sunday = Day 1");
      Adow=int(ADay);
      switch(Adow)
      {
      case 1:
        Serial.print("Sun at ");
        break;
      case 2:
        Serial.print("Mon at ");
        break;
      case 3:
        Serial.print("Tue at ");
        break;
      case 4:
        Serial.print("Wed at ");
        break;
      case 5:
        Serial.print("Thu at ");
        break;
      case 6:
        Serial.print("Fri at ");
        break;
      case 7:
        Serial.print("Sat at ");
        break;
      }
      digitalClockDisplay();
      Serial.print('\n');
    } 
    else { //Ady is False
      if (Alarm != 2){
        Serial.println("Alarm will fire when Date,hours,minutes and seconds match.");
      }
      else {  
        Serial.println("Alarm will fire when Date,hours and minutes match.");
        ASecond=0;
      }
      Serial.print(ADay);
      // Get the Date ending 
      Adow=int(ADay);
      switch(Adow)
      {
      case 1: 
      case 21: 
      case 31:
        Serial.print("st of each month at ");
        break;
      case 2: 
      case 22:
        Serial.print("nd of each month at ");
        break;
      case 3: 
      case 23:
        Serial.print("rd of each month at ");
        break;
      default:
        Serial.print("th of each month at ");
      }
      digitalClockDisplay();
      Serial.print('\n');
    }
    break;
  case 8:
    Serial.println("Alarm will fire when hours,minutes and seconds match.");
    Serial.print("Every Day at ");
    digitalClockDisplay();
    Serial.print('\n');
    break;
  case 12:
    Serial.println("Alarm will fire when minutes and seconds match.");
    Serial.print("Every Hour at ");
    AHour=99;
    digitalClockDisplay();
    Serial.print(" minutes and seconds.");
    Serial.print('\n');
    break;
  case 14:
    Serial.println("Alarm will fire when seconds match.");
    Serial.print("Every Minute at ");
    AHour=99;
    AMinute=99;
    digitalClockDisplay();
    Serial.print(" seconds.");
    Serial.print('\n');
    break;
  case 15:
    Serial.println("Alarm will fire once per second.");
    Serial.print('\n');
    break;
  case 64:
    Serial.println("Alarm will fire when hours and minutes match.");
    Serial.print("Every Day at ");
    digitalClockDisplay();
    Serial.print('\n');
    break;
  case 96:
    Serial.println("Alarm will fire when minutes match.");
    Serial.print("Every Hour at ");
    AHour=99;
    digitalClockDisplay();
    Serial.print('\n');
    break;
  case 112:
    Serial.println("Alarm will fire once per minute at 00 Seconds.");
    Serial.print('\n');
    break;
  } 
}
void digitalClockDisplay() {
  // digital clock display of the time
  printDigits(AHour);
  Serial.print(":");
  printDigits(AMinute);
  Serial.print(":");
  printDigits(ASecond);
  // If the mode is 12Hour then add either AM or PM
  if (A12h) {
    if (Apm) {
      Serial.print("PM ");
    } 
    else {
      Serial.print("AM ");
    }
  }

}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  if(digits > 59)
    Serial.print("--");
  else {
    if(digits < 10)
      Serial.print('0');
    Serial.print(digits);
  }
}

void isEnabled(int Alarm){
  Serial.print("Alarm is ");
  if (Clock.checkAlarmEnabled(Alarm)) {
    Serial.print("enabled.");
  } 
  else {
    Serial.print("disabled");
  }
  Serial.print('\n');

}
void clockMode(){
  if (A12h) {
    Serial.println("Clock is in 12Hour Mode");    
  }
  else {
    Serial.println("Clock is in 24Hour Mode");
  }
}
void loop() {

}



















