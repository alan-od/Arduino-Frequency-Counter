/*
 * 
 * Diagnostic App for Frequency Counter
 * 
 * Update RTC - user needs to up date setTimeDate function
 * with date time parameters.
 * 
 * Use serial monitor to check the RTC is being accessed
 * by I2C network and up dating the time.
 * 
 * 
 * LCD display shows something is happening (or should)
 * 
 * 
 * AOD - 30th November 2016
 */

#include <Wire.h> //I2C Library
#include <LiquidCrystal.h>
#include <DS3231.h>


//Clock structure 
struct ClockStruct{
  byte hour;
  byte minute;   
  byte sec;
  byte day;
  byte month;
  byte year;
  byte DoW;
} timeStruct;


LiquidCrystal lcd(11,10,9,8,7,6);
DS3231 Clock;

void setup() {
    Serial.begin(9600);      // open the serial port at 9600 bps:
    Wire.begin();  //start I2C bus 
    
   lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines
  //Start up splash screen
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Test Clock - 2");
  lcd.setCursor(0, 1);
  lcd.print("Use Monitor");
  delay(3000);  
  lcd.clear();
       
}


bool h12 = false;
bool PM = false; 
bool Century=false;



void setTimeDate(){
        Clock.setSecond(0);//Set the second 
        Clock.setMinute(45);//Set the minute 
        Clock.setHour(10);  //Set the hour 
        Clock.setDoW(4);    //Set the day of the week (Sunday = 1)
        Clock.setDate(30);  //Set the date of the month
        Clock.setMonth(11);  //Set the month of the year
        Clock.setYear(16);  //Set the year (Last two digits of the year)
}

bool inhibit = true;

void loop() {
  
  
//populate structure with time from RTC
  //Two possible methods
  
  Clock.getTime(timeStruct.year,timeStruct.month,timeStruct.day,timeStruct.DoW,timeStruct.hour,timeStruct.minute,timeStruct.sec);
 
  
  //timeStruct.sec=Clock.getSecond();
 // timeStruct.minute=Clock.getMinute();
 // timeStruct.hour=Clock.getHour(h12, PM);
 // timeStruct.day=Clock.getDate();
 // timeStruct.month=Clock.getMonth(Century);
 // timeStruct.year=Clock.getYear();  


  //set time and date Once!
  if(inhibit){
    setTimeDate();
    inhibit = false;
  }
  
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
