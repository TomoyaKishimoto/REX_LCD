#include <LiquidCrystal.h>

LiquidCrystal lcd( 5, 6, 9, 10, 11, 12 );

void setup() {
    lcd.begin( 16, 2 );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("\xb0");
}

void loop() {
    
}