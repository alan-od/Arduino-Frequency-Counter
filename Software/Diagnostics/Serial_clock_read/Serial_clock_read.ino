/*
 * 
 * Diagnostic App for Frequency Counter
 * 
 * Read clock, display in Serial Monitor
 * 
 * 
 * Switch in or out as required - LCD display shows something is happening (or should)
 * 
 * 
 * 
 */

#include <Wire.h> //I2C Library
#include <LiquidCrystal.h>
#include <DS3231.h>


//Clock structure 
struct ClockStruct{
  int hour;
  int minute;   
  int sec;
  int day;
  int month;
  int year;
} timeStruct;


LiquidCrystal lcd(11,10,9,8,7,6);
DS3231 Clock;

void setup() {
    Serial.begin(9600);      // open the serial port at 9600 bps:
    Wire.begin();  //start I2C bus 
    
   lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines
  //Start up splash screen
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Test Clock - 1");
  lcd.setCursor(0, 1);
  lcd.print("Use Monitor");
  delay(3000);  
  lcd.clear();
       
}


bool h12 = false;
bool PM = false; 
bool Century=false;


void loop() {
  
  //populate structure with time from RTC
  timeStruct.sec=Clock.getSecond();
  timeStruct.minute=Clock.getMinute();
  timeStruct.hour=Clock.getHour(h12, PM);
  timeStruct.day=Clock.getDate();
  timeStruct.month=Clock.getMonth(Century);
  timeStruct.year=Clock.getYear();  
  
 
  //Uncomment if display appears to work okay
  lcd.print("Serial Monitor");
  delay(800);
  lcd.setCursor(0,0);
  lcd.print("               ");
  lcd.setCursor(0,1);
  lcd.print("Serial Monitor");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("              ");
  lcd.setCursor(0,0);
 
  Serial.print("Time is ");
  Serial.print(timeStruct.hour );
  Serial.print(":");
  Serial.print(timeStruct.minute );
  Serial.print(":");
  Serial.println(timeStruct.sec );
  Serial.print("Date -  ");
  Serial.print(timeStruct.day );
  Serial.print(" ");
  Serial.print(timeStruct.month);
  Serial.print(" ");
  Serial.println(timeStruct.year);

}
