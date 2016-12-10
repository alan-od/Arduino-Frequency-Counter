/*
 * All the code for the menuing system
 * is included here.  Note that much of the 
 * textual data is held in non-volatile
 * memory using PGM_P. Also in lcd.print statments
 * the use of F puts text into non-volatile
 * memory ( lcd.print(F("some text")) ).
 * 
 * The menu system relies upon manipulating
 * the pointer menu_ptr (not a C pointer). The value of
 * menu_ptr dictates the position the user is in within 
 * the menu tree.
 * 
 * I pushed the boat out with the Throb timer - this
 * uses timerT as a 2:1 mark space ratio timer. It gives
 * a better "user experience" to certain variables displayed
 * on the display as opposed to either no occulting of variables
 * or just straight flashing
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
 */


#include "Menu.h"

//Structures defined in "clock_xxx file
extern struct clockStruct tempClock;
extern struct storeParametersStruct eeTemp;


extern bool direc; //encoder direction
int   menu_ptr = QUIT; //ptr to display menu
byte  exitIndex;

//Have to set prototypes
void clear_tl();
void display_time();



//Menu Items (stored in flash memory)
PGM_P const menu_string[] PROGMEM = 
  {
    "Select Input",
    "Set Time",
    "Set Date",
    "Calibrate",
    "Exit"
  }; 

PGM_P const select_string[] PROGMEM = 
  {
    "Auto",
    "Input - HF",
    "Input - VHF/UHF"
  }; 
  
PGM_P const time_string[] PROGMEM =   //used twice time and lamp time off
  {
    "Time:   "
  }; 

PGM_P const date_string[] PROGMEM = 
  {
    "Date: "
  }; 

PGM_P const cal_string[] PROGMEM = 
  {
    "Freq Offset: "
  }; 


PGM_P const confirm_string[] PROGMEM = 
  {
    "Confirm",
    "Cancel"
  }; //set MENU_INDEX to 1 - update if this array is changed  
      
  
void menu(char direc)
{
   
  if(direc){ //menu change for up switch
    
    if(menu_ptr < TOP_MENU){    //main menu
      if(menu_ptr < MENU_INDEX) 
        menu_ptr++;
      else
        menu_ptr = M0_INPUT; //set back to 1st menu item
      menu_dis();
      return; 
    }

    if(menu_ptr < SELECT_MENU){    //main menu
      if(menu_ptr < INPUT_INDEX) 
        menu_ptr++;
      else
        menu_ptr = SET_AUTO; //set back to 1st menu item
      menu_dis();
      return; 
    }
  
 
//--------Set Clock Parameters------------
    //Hours and minutes
    if(menu_ptr == SET_HOUR){
      if(tempClock.hour < 23)
        tempClock.hour++;
      else
        tempClock.hour = 0;
      display_hour(true);
    return;
    }
    if(menu_ptr == SET_MIN){
      if(tempClock.minute < 59)
        tempClock.minute++;
      else
        tempClock.minute = 0;
      display_min(true);
    return;
    }
    //Day, date and year
    if(menu_ptr == SET_DAY){
      if(tempClock.day < 31)
        tempClock.day++;
      else
        tempClock.day = 1;
      display_day(true);
    return;
    }
    if(menu_ptr == SET_MONTH){
      if(tempClock.month < 12)
        tempClock.month++;
      else
        tempClock.month = 1;
      display_month(true);
    return; 
    }
    if(menu_ptr == SET_YEAR){
      if(tempClock.year < 99)
        tempClock.year++;
      else
        tempClock.year = 15;
      display_year(true);
    return; 
    }
    //Set calibrate parameters

     if(menu_ptr == SET_CAL){
      if(eeTemp.calVar < 99) eeTemp.calVar++;
      display_cal(true);
      return;
     }

    //--------- Exit/Confirm menu-------------
   if(menu_ptr < EXIT_MENU){   //CONFIRM
      if(menu_ptr < CONFIRM_INDEX)  
        menu_ptr++;
      else
        menu_ptr = M1_CONFIRM; //set back to 1st menu item
      menu_dis();
      return; 
    }
  }
       
//***********Repeat above for down switch************
  else{ //direction is down
      
    if(menu_ptr < TOP_MENU){    //main menu
      if(menu_ptr == M0_INPUT) //check against 1st menu entry
        menu_ptr = MENU_INDEX;
      else
        menu_ptr--;
      menu_dis();
      return; 
    }

    if(menu_ptr < SELECT_MENU){    //main menu
      if(menu_ptr == SET_AUTO) 
        menu_ptr = INPUT_INDEX;
      else
        menu_ptr--;
      menu_dis();
      return; 
    }

      
    //---------Set Clock Parameters----------
    //Set time, hours and minutes
    
    if(menu_ptr == SET_HOUR){
        if(tempClock.hour == 0)
          tempClock.hour = 23;
        else
          tempClock.hour--;
        display_hour(true);
        return;
      }
    if(menu_ptr == SET_MIN){
        if(tempClock.minute == 0)
          tempClock.minute = 59;
        else
          tempClock.minute--;
        display_min(true);
        return;
      }
    //Day, date and year
    if(menu_ptr == SET_DAY){
      if(tempClock.day == 1)
        tempClock.day = 31;
      else
        tempClock.day--;
      display_day(true);
      return;
    }
    if(menu_ptr == SET_MONTH){
      if(tempClock.month == 1)
        tempClock.month = 12;
      else
        tempClock.month--;
      display_month(true);
      return;
    }
    if(menu_ptr == SET_YEAR){
      if(tempClock.year == 15)
        tempClock.year = 99;
      else
        tempClock.year--;
      display_year(true);
      return;
    }
  
  //Set calibrate parameters  

    if(menu_ptr == SET_CAL){
      if(eeTemp.calVar > -99) eeTemp.calVar--;
      display_cal(true);
      return;
    }
  
  //--------- Exit/Confirm menu-------------
    if(menu_ptr < EXIT_MENU){   //main menu
      if(menu_ptr == M1_CONFIRM) 
        menu_ptr = CONFIRM_INDEX;
      else
        menu_ptr--;
      menu_dis();
      return; 
    }
 }
 
}

void menu_dis(void){

  if(menu_ptr < 0){ //out of menu system 
    lcd.clear();
    return;
  }
  //-------------
  setBL();  //sets up button select switches
  //------------
  
  if(menu_ptr < TOP_MENU){  
    clear_tl();
    lcd.print((PGM_P)pgm_read_word(&(menu_string[menu_ptr])));
    return; 
  }
  if(menu_ptr < SELECT_MENU){  
    clear_tl();
    lcd.print((PGM_P)pgm_read_word(&(select_string[menu_ptr - SET_AUTO])));
    return; 
  }
  if(menu_ptr < TIME_MENU){  
     lcd.print((PGM_P)pgm_read_word(&(time_string[0])));
    display_hour(true);
    display_min(true);
    return; 
  }
 if(menu_ptr < DATE_MENU){  
     lcd.print((PGM_P)pgm_read_word(&(date_string[0])));
     display_day(true);
     display_month(true);
     display_year(true);
    return; 
  }
  if(menu_ptr < CAL_MENU){
     lcd.print((PGM_P)pgm_read_word(&(cal_string[0])));
     display_cal(true);
    return;

    
  }
  if(menu_ptr < EXIT_MENU){
    clear_tl();
    lcd.print((PGM_P)pgm_read_word(&(confirm_string[menu_ptr-200])));
  }
}



void menu_func(void){
      switch(menu_ptr){
      //----------Top menu
        case M0_INPUT:
          menu_ptr = SET_HF;
        break;
        case M0_TIME:
          menu_ptr = SET_HOUR; //Set time
        break;
        case M0_DATE:
          menu_ptr = SET_DAY; //Set date
        break;
        case M0_CALIBRATE:
          menu_ptr = SET_CAL;
        break;
        case M0_EXIT:
          menu_ptr = QUIT; //exit
        break;
        //-------- Input Select
        case SET_AUTO:
          exitIndex = AutoSelect;
          menu_ptr = CONFIRM_INDEX;
        break;
        case SET_HF:
          exitIndex = InputLow;
          menu_ptr = CONFIRM_INDEX;
          break;
        case SET_VHF:
          exitIndex = InputHigh;
          menu_ptr = CONFIRM_INDEX;
        break;
        //------Time settings
        case SET_HOUR:
          menu_ptr = SET_MIN;
        break;
        case SET_MIN:
          exitIndex = Time;
          menu_ptr = CONFIRM_INDEX;
        break;
        //------------Date settings
        case SET_DAY:
          menu_ptr = SET_MONTH;
        break;
        case SET_MONTH:
          menu_ptr = SET_YEAR;
        break;
        case SET_YEAR:
          menu_ptr = CONFIRM_INDEX;
          exitIndex = Time;
        break;
        //------------Calibrate settings
        case SET_CAL:
          menu_ptr = CONFIRM_INDEX;
          exitIndex = Calibrate;
        break;
        //-----------Exit options  
        case M1_CONFIRM:
          confirm();
          menu_ptr = QUIT; //exit
        break;
        case M1_CANCEL:
          menu_ptr = QUIT; //exit
        break;
        default:
        break;
      }
     
  menu_dis();
}


void display_hour(bool x){  //bool x - switch on/off
  lcd.setCursor(10,0);
  if(x){
    if(tempClock.hour < 10) lcd.print("0");
    lcd.print(tempClock.hour,DEC);  
    lcd.print(":");
  }
  else lcd.print("  :");
}

void display_min(bool x){
  lcd.setCursor(13,0);
  if(x){
    if(tempClock.minute < 10) lcd.print("0");
      lcd.print(tempClock.minute,DEC);
  }
  else lcd.print("  ");
  
}

void display_day(bool x){
  lcd.setCursor(6,0);
  if(x){
    if(tempClock.day < 10) lcd.print("0");
    lcd.print(tempClock.day,DEC);
    lcd.print(":");
  }
  else lcd.print("  :");
}

void display_month(bool x){
  lcd.setCursor(9,0);
  if(x){
    if(tempClock.month < 10) lcd.print("0");
    lcd.print(tempClock.month,DEC);
    lcd.print(":");
  }
  else lcd.print("  :");
}

void display_year(bool x){
  lcd.setCursor(12,0);
  (x==true) ? lcd.print(tempClock.year+2000,DEC) : lcd.print("    ");  
}


void display_cal(bool x){   
  lcd.setCursor(13,0);      
  if(x){
    if(eeTemp.calVar < 0){
      lcd.print("   ");
      lcd.setCursor(13,0);
      lcd.print(eeTemp.calVar,DEC);
    }
    if(eeTemp.calVar >= 0){
      lcd.print("   ");
      lcd.setCursor(13,0);
      lcd.print(eeTemp.calVar,DEC);
    }
  }
  if(!x)
    lcd.print("   ");
}




//Clear top and bottom lines of LCD
void clear_tl(void){  
  lcd.setCursor(0,0);
  lcd.print(F("                ")); //F() places chars into flash
  lcd.setCursor(0,0);
}
void clear_bl(void){  
  lcd.setCursor(0,1);
  lcd.print(F("                "));
  lcd.setCursor(0,0);
}
//-----------------------------
//LCD bottom line "Sel  <  >"
void setBL(void){
  lcd.setCursor(0,1); //row 2 left
  lcd.print(F("Sel     <      >")); //F() places chars into flash
  lcd.setCursor(0,0);
}

//Throbing timer (a variable mark/space timer)
unsigned long int numa = 0;
bool throbFlag = true;


bool timerT(){
  if(numa < 40000 && throbFlag){    //on timer
    numa++;
    return throbFlag;
  }
  if(numa >= 40000 && throbFlag){
    throbFlag = false;
    numa = 0;
  }
  if(numa < 20000 && !throbFlag){   //off timer
    numa++;
    return throbFlag;
    
  }
  if(numa >= 20000 && !throbFlag){
    throbFlag = true;
    numa = 0;
  }
  return throbFlag;
}



//Switches on and off displayed variable
void throb(){
      if(timerT() && (numa == 1)){ //use numa so the display is only updated once
      switch(menu_ptr){             //else the LCD gets continuously updated
        case SET_HOUR:
              display_hour(true);
        break;
        case SET_MIN:
              display_min(true);
        break;
        case SET_DAY:
              display_day(true);
        break;
        case SET_MONTH:
             display_month(true);
       break;
       case SET_YEAR:
             display_year(true);
       break;
       case SET_CAL:
             display_cal(true);
       break;
     
       default: 
       break;
     }
    }
    if(!timerT() && (numa == 1)){
     switch(menu_ptr){
       case SET_HOUR:
             display_hour(false);
        break;
        case SET_MIN:
              display_min(false);
        break;
        case SET_DAY:
              display_day(false);
        break;
        case SET_MONTH:
              display_month(false);
        break;
        case SET_YEAR:
              display_year(false);
        break;
        case SET_CAL:
              display_cal(false);
        break;
        default:
        break;
     }
    }
  
}


