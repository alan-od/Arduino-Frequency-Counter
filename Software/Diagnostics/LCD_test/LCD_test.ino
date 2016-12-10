/*
 * 
 * Diagnostic App for Frequency Counter
 * 
 * Test LCD Display
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
  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines
  //Start up splash screen
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Test Display");
  lcd.setCursor(0, 1);
  lcd.print("Test Display");
  delay(3000);  
  lcd.clear();

}


void loop() {

    int x;
    int dis = 0;
    char A;
    for(x = 0; x < 16; x++){
      if(dis > 9) dis = 0;
      lcd.print(dis);
      lcd.setCursor(x,0);
      dis++;
      delay(500);      
    }
    
    for(x = 0; x < 16; x++){
      if(dis > 9) dis = 0;
      lcd.print(dis);
      lcd.setCursor(x,1);
      dis++;
      delay(500);      
    }
    
    lcd.clear();
    
    for(x = 0; x < 16; x++){
      lcd.print(A);
      lcd.setCursor(x,0);
      A = 'A'+ x;
      delay(500);      
    }
    for(x = 0; x < 16; x++){
      lcd.print(A);
      lcd.setCursor(x,1);
      A = 'Q' + x;
      delay(500);      
    }
 
    lcd.clear();

    for(x = 0; x < 16; x++){
      lcd.print(A);
      lcd.setCursor(x,0);
      A = 'a'+ x;
      delay(500);      
    }
    for(x = 0; x < 16; x++){
      lcd.print(A);
      lcd.setCursor(x,1);
      A = 'q' + x;
      delay(500);      
    }
 
    lcd.clear();


}
