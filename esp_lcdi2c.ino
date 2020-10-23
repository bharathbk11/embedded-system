#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup(){
  Wire.begin(2,0);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.setCursor(0,0); 
  lcd.print("Hello"); // Start Printing
  lcd.setCursor(0,1);
  lcd.print("Makers"); // Start Printing
}
void loop(){
  // Nothing Absolutely Nothing!
}
