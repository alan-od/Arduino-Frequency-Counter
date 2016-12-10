/*
 * 
 * This module includes the details for
 * setting up the clock module and
 * also the confirm() function which
 * is called from the menu system
 * 
 * 
 *  Author: Alan O'Donovan
 *  Copyright (c) 2016 Alan O'Donnovan.  All rights reserved.
 *   
 *  This file is part of Frequency_counter
 *
 *  Frequency_counter is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Frequency_counter is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Frequency-counter.  If not, see <http://www.gnu.org/licenses/>. 
 *   
 * 
 * 
 */


#include "EEPROM.h"
#include "Menu.h"
#include "Frequency_counter.h"

extern byte indexIndex;

// Bits and pieces for clock
bool Century=false;
bool h12 = false;
bool PM = false;
//The following arrays are used to display date on the LCD
char month_alpha[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}; 
char day[7][4] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};


extern struct clockStruct mainClock;   //holds real time clock data
extern struct clockStruct tempClock; //temp needed for menu system

extern byte  exitIndex; //type of action to be performed follwing a confirm action
extern bool  prescaler; //normal or prescaler input

void ReadDS3231()
{
 // int minute,hour,date,month,year; 

  mainClock.minute=Clock.getMinute();
  mainClock.hour=Clock.getHour(h12, PM);
  mainClock.day=Clock.getDate();
  mainClock.month=Clock.getMonth(Century);
  mainClock.year=Clock.getYear();  
  lcd.clear();
  //Print Hours and Minutes
  lcd.setCursor(5,0);
  if(mainClock.hour <= 9)
    lcd.print("0"); //need to zero pad hours and mins
  lcd.print(mainClock.hour);
  lcd.print(":");
  if(mainClock.minute <=9)
    lcd.print("0");
  lcd.print(mainClock.minute);
  //Print full date on line 2
  lcd.setCursor(0,1);
  //Select day from Day of the week marker (needs to be set on startup)
  lcd.print(day[(Clock.getDoW())-1]);
  lcd.print(" ");
  lcd.print(mainClock.day);
  lcd.print(" ");
  //Print month
  lcd.print(month_alpha[mainClock.month-1]); //array 0 to 11, month index 1 to 12
  lcd.print(" 20");
  lcd.print(mainClock.year);

  tempClock = mainClock;
  
}

//Determine day of week from date.
//Thanks to Tomohiko Sakamoto - amazing

int computeDoW(int d, int m, int y){
 
       int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
       y -= m < 3;
       return 1+((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7); //returns 1 to 7, 1 = Sunday
 }



void confirm(void){
  //Update real time clock
  if(exitIndex == Time){
      mainClock = tempClock;
      Clock.setMinute(mainClock.minute);
      Clock.setHour(mainClock.hour);
      Clock.setDate(mainClock.day);
      Clock.setMonth(mainClock.month);
      Clock.setYear(mainClock.year);
      Clock.setDoW(computeDoW(mainClock.day,mainClock.month,mainClock.year)); //dsClock has a 1 to 7 day counter, Sunday = 1
  }
  //Update EEPROM
  if(exitIndex == Calibrate){
        eeStore = eeTemp;
        EEPROM_writeStruct(0,eeStore);     
  }
  //Select type of input  
  if(exitIndex == InputLow){
        SEL_LF;
        prescaler = false;
  }
  if(exitIndex == InputHigh){
        SEL_HF;
        prescaler = true;
  }


}

