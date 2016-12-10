/*
 *  Frequency Counter
 *  
 *  See Readme file
 *  
 *  
 *  
 *  Version 6 v0.2
 *  1st December '16
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



#include <Wire.h> //I2C Library
#include <LiquidCrystal.h> //LCD library
#include <DS3231.h>  //Clock library

#include "Menu.h"
#include "EEPROM.h"
#include "Frequency_counter.h"


//---------Globals--------------------

//------- external functions ---------------//
//Menu function prototypes
void menu(char);
void menu_dis(void);
void menu_func(void);
void throb(void);
bool timerT(void);

//Clock Functions
void ReadDS3231(void);
void SetTimeDate(void);

//----------Globals variables--------------
extern int menu_ptr;
extern int8_t cal;

long       freq = 0;  //32 bit store, main frequency variable
long       overflowCount = 0;
char       char_array[15]; //required here to pass array to lcd_display()
bool       displayFlag = false;
byte       countFlag = 0;
bool       menuInt = false;
bool       direc = false;
bool       prescaler = false;  //false = LF input, true = prescaler

//--------End Globals-----------------

//------------- System structs  ----------//
//Main and temproary Clock structure (tempParam are updated from the menu system)
struct clockStruct{
  byte hour;
  byte minute;   
  byte day;
  byte month;
  byte year;
};

struct clockStruct mainClock;
struct clockStruct tempClock;

struct storeParametersStruct{
  int8_t calVar;
};

struct storeParametersStruct eeStore;
struct storeParametersStruct eeTemp;

//instantiate Objects
LiquidCrystal lcd(11,10,9,8,7,6);
DS3231 Clock; 

//--- Here we go -----------
void setup() {

//-----Set up pins for I/O-----
  //Set pins to output
  DDRC = (1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC6); //Pins A0, A1, A2, A6
  DDRB = (1<<DDB4)|(1<<DDB5); //Pins D12 and D13
  //Set pints to input
  DDRD &= ~(1<<PD5);  //TI counter
  DDRC &= ~(1<<PC3);  //Set C3 to input
  DDRD &= ~(1<<PD2);  //Set SW1,2 & 3 to inputs  - Interrupt on pin D2
  DDRD &= ~(1<<PD3);
  DDRD &= ~(1<<PD4);
  NOP;
  ENABLE_1HZ;
  NOP;
  INT_TB_HI;
  NOP;
  SEL_LF; //Select input
  NOP;
  CLEAR; //Clears U7
  NOP;

  attachInterrupt(digitalPinToInterrupt(2), gotoMenu, LOW);
//---------------------------

//---------- Timer T1 is used as part of the overall counter------------------ 

  //Set up T1 interrupt registers
  //Set control registers to 0
  TCCR1A = 0;
  TCCR1B = 0;
  //Set up registers
  //Enable interrupts
  TIMSK1 = bit(TOIE1);
  // Set normal mode, external clock source and fallling edge.
  TCCR1B =  bit(ICNC1) | bit (CS11) | bit (CS12);  //if bit (CS10) is set, clocks on rising edge
                                                   //bit(ICNC1) is the noise filter 
  
  Wire.begin();  //start I2C bus
  
  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines
  //Start up splash screen
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("CPREC F Counter");
  lcd.setCursor(0, 1);
  lcd.print("V6 v0.2");
  delay(3000);  
  lcd.clear();
  ReadDS3231();
  tempClock = mainClock;  //initialise struct
  EEPROM_readStruct(0,eeStore); //read in EEPROM values into StoreParameter structure
  eeTemp = eeStore; 
  
  //Set up external 1Hz SQW in RTC
  //Check prior to enabling - don't need to keep updating 
  //every time the device is switched on
  if(!Clock.CheckINTCN()){
    Clock.enableOscillator(1,0,0);
  }

}

//------------Interrupt Functions---------------
//Interrupt fuction for Timer1
//fired each time T1 overflows

ISR (TIMER1_OVF_vect){
    overflowCount++;
}

//Interrupt function for menu select button (SW1)
void gotoMenu(){
    menuInt = true;
}

//-------------End of Interrupt functions------------

//---------------- Timers--------------------
//Non blocking timer
unsigned long num1;
int timer(){
  if(num1 < 1000){
    num1++;
    return false;
  }
  else{
    num1 = 0;
    return true;
  }
}

//Timer 2 used to drop out of menu system
//when no user interaction has been detected
unsigned long int num2;
bool  timer2(bool reset){
      if(reset) num2 = 0;
      if(num2 < 900000){
        num2++;
        return false;
      }
      else{
        num2 = 0;
        return true;
      }
}

//------------End of timers------------------------

//------------- Loop to discover switch presses ---------------
void checkSwitches(){

    while(menu_ptr != QUIT){
      timer2(false); //fire timer once menu system is entered
      if(timer2(false) && menu_ptr > -1){ //drops out of menu system
        menu_ptr = QUIT;
        return;
      }
    
    
        if (bit_is_clear(PIND,PIND2)){   //switch SW1 (select)
          timer2(true); //resets drop out timer
          delay(300);
          menu_func();
       }
       if (bit_is_clear(PIND,PIND3)){    //switch SW2 (down)
          timer2(true);
          delay(300);
          menu(false);
       }
       if (bit_is_clear(PIND,PIND4)){    //switch SW3 (up)
          timer2(true);
          delay(300);
          menu(true);
       }
    throb();      //in menu module
    }
}

void correctF(){
  long temp;
  temp = freq;
  temp = temp/1000000;  //corrects from 1MHz upwards
  temp *= (long)eeStore.calVar;
  temp /= 10;  //cal granualtiy is +/- 0.1 Hz (per MHz)
  freq += temp;
}

void displayFreq() {
  byte n, x;
  if(freq < 100){  //Display time if no frequency
    ReadDS3231();
    return;
  }

  
  ltoa(freq, char_array, 10); //long to string - handy extension!
  for (n = 0; n <= 9; n++) { //position n to end of string
    if (char_array[n] == 0) break;
  }
  n -= 1; //n = last string character
  //format string to include comma and dot for appropriate frequency display.

  if (n >= 6) {
    for (x = n; x > (n - 3); x--) {
      char_array[x + 2] =  char_array[x];
    }
    char_array[n - 1] = ',';
    for (x = (n - 3); x > (n - 6) ; x--) {
      char_array[x + 1] =  char_array[x];
    }
    char_array[n - 5] = '.';
    //re position n to end of string
    n += 3;
    char_array[n] = ' ';
    char_array[n + 1] = 'M';
    char_array[n + 2] = 'H';
    char_array[n + 3] = 'z';
    char_array[n + 4] = 0; //null terminator
  }
  else if (n >= 3 && n <= 5) {
    for (x = n; x > (n - 3)  ; x--) {
      char_array[x + 1] =  char_array[x];
    }
    char_array[n - 2] = '.';
    n += 2;
    char_array[n] = ' ';
    char_array[n + 1] = 'K';
    char_array[n + 2] = 'H';
    char_array[n + 3] = 'z';
    char_array[n + 4] = 0; //null terminator
  }
  else {
    n += 1;
    char_array[n] = ' ';
    char_array[n + 1] = 'H';
    char_array[n + 2] = 'z';
    char_array[n + 3] = 0; //null terminator
  }
  lcd.clear();
  lcd.print(char_array);
  //Display which input is being used on 2nd line of LCD
  lcd.setCursor(0,1);
  (prescaler == true) ?  lcd.print(F("Hi Input")) : lcd.print(F("Lo Input"));
}

void readTimer1(){
   unsigned int timer1Value;
   timer1Value = TCNT1;
   overflowCount <<= 16;
   freq = overflowCount + (unsigned long)timer1Value;
}

//Clock out 74HC393

void flush393(){
  uint8_t x = 0;
  
  freq <<= 8; // x256
  if(!(PIND&(1<<PIND5))){
    for(x = 0; x<128 && !(PIND&(1<<PIND5)); x++){
      FLUSH_74323;
    }
    freq = freq+(128 - x);
  }
  else{    
    for(x = 0; x<128 && PIND&(1<<PIND5); x++){
      FLUSH_74323;
    }
    freq = freq+(256 - x);  //if D6 is high, count is already at 128
  }
}

//-------Main-----------------

void loop() {

  while(bit_is_set(PINC,PINC3)){   
    displayFlag = true;

    if(menuInt){
      lcd.clear();
      menu_ptr = 0;
      tempClock = mainClock; //ensure temp struct is upto date
      eeTemp = eeStore;
      menu_dis();
      checkSwitches(); //loops around switches - blocks while loop!
      menuInt = false;
    }
    
  }

  if(bit_is_clear(PINC,PINC3)&& displayFlag){  
      readTimer1();
      flush393();
      correctF();   //use calibrate variable
      if(prescaler) freq = freq * 10; //prescaler divides by 10
      displayFreq();
      freq = 0;
      CLEAR;
      overflowCount = 0;
      TCNT1 = 0;
      displayFlag = false;
  }
}
