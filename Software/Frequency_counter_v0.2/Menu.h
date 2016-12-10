/*
 *  Menu table X_INDEX sets the menu pointer to the menu set selected. Sets are
 *  0 to 9, 10 to 19, 20 to 29 etc. thus allowing up to a maximum of 10 elements
 *  within each menu set.  X_INDEX parameter comprise the set number (0,10, 20..) plus
 *  the number of the last element within the menu set
 *  
 *  MX_TEXT refers to the menu number refering to its parents set i.e. M0, M1, M2, M3 etc
 *  while TEXT refers to the actual text displayed
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


#ifndef MENU_H
#define MENU_H


#define TOP_MENU          9
#define MENU_INDEX        0 + 4  //Number of string items in menu selection + offset
    #define M0_INPUT      0
    #define M0_TIME       1
    #define M0_DATE       2
    #define M0_CALIBRATE  3
    #define M0_EXIT       4

#define SELECT_MENU       19
#define INPUT_INDEX       10 + 2  //Select normal or 
    #define SET_AUTO      10      //prescaler input
    #define SET_HF        11
    #define SET_VHF       12
 

#define TIME_MENU       29
#define TIME_INDEX      20  //includes zero as a state
    #define SET_HOUR    21 //time parameters to set
    #define SET_MIN     22

#define DATE_MENU       39
#define DATE_INDEX      30
    #define SET_DAY     31
    #define SET_MONTH   32
    #define SET_YEAR    33

#define CAL_MENU          49
#define CALIBRATE_INDEX   40  //only a single item
    #define SET_CAL       41



#define EXIT_MENU      209
#define CONFIRM_INDEX  200 + 1  //two string items (confirm and exit)
  #define M1_CONFIRM   200 
  #define M1_CANCEL    201

//Variables defining functionality require following a user Confirm action (should use enum)
#define Time        0  //These variables are used to determin
#define Calibrate   1  //the type of variables to be stored following a Confirm action
#define AutoSelect  2
#define InputLow    3
#define InputHigh   4


#define QUIT -1


#endif
