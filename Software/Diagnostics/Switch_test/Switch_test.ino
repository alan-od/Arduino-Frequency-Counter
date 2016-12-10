/*
 * 
 * Diagnostic App for Frequency Counter
 * 
 * Test the three switches
 * 
 * 
 * 
 * 
 * 
 * 
 */




#include <LiquidCrystal.h> //LCD library

LiquidCrystal lcd(11,10,9,8,7,6);

void setup() {

  //Set SW1,2 & 3 to inputs
  DDRD &= ~(1<<PD2);    
  DDRD &= ~(1<<PD3);
  DDRD &= ~(1<<PD4);

  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines
  //Start up splash screen
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Test Switches");
  lcd.setCursor(0, 1);
  lcd.print("Test Switches");
  delay(3000);  
  lcd.clear();

  lcd.print("Press a Switch");
  lcd.setCursor(0,1);

}

void loop() {

       
        
       if (bit_is_clear(PIND,PIND2)){   //switch SW1 (select)
          delay(300);
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("Switch 1 Pressed");
       }
       if (bit_is_clear(PIND,PIND3)){    //switch SW2 (down)
          delay(300);
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("Switch 2 Pressed");
       }
       if (bit_is_clear(PIND,PIND4)){    //switch SW3 (up)
          delay(300);
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("Switch 3 Pressed");       
       }

 
}
