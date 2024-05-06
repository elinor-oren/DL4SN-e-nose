#include <Wire.h>
#include "Waveshare_LCD1602_RGB.h"
#include <math.h> // Include the math library for the sin function

Waveshare_LCD1602_RGB lcd(16,2);  // 16 characters and 2 lines of display

void setup() {
  lcd.init();  // Initialize the LCD
  lcd.setCursor(0,0);
  lcd.send_string("Setup done!");
}

void loop() {
  static int startPos = 0;
  const char* text = "This is a long text that scrolls"; 
  int textLen = strlen(text);

  lcd.clear();
  lcd.setCursor(0,0);
  
  if (startPos < textLen) {
    if (textLen - startPos < 16) {
      lcd.send_string(text + startPos);  // Send substring starting from startPos
      // Fill the rest of the display with spaces if needed
      for (int i = 0; i < 16 - (textLen - startPos); i++) {
        lcd.send_string(" ");
      }
    } else {
      lcd.send_string(text + startPos);
    }
  } else {
    startPos = 0;  // Reset start position if it exceeds text length
  }
  
  startPos++;  // Move start position to the right
  delay(300);  // Adjust delay for text scrolling speed
}
