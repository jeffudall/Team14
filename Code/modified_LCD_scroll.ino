/*
   10 - 12 - 2017
   ECE 411 Team 14
   Portland, OR
  (Modified) LiquidCrystal Library - Autoscroll
                                   - Uses the Arduino RedBoard

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch demonstrates the use of the autoscroll()
 and noAutoscroll() functions to make new text scroll or not.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalAutoscroll

 Idea to try: us an array for a senetence; iterate over the sentence
              in a for loop and use lcd.write(char) to write a char
              at a time
*/

//Create a unique char
byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Create the smiley char that was specified above
  lcd.createChar(0, smiley);
  // set up the LCD's number of columns and rows:   
  lcd.begin(16, 2);
}

void loop() {

  // set the cursor to (16,1): -- NOTE: 16 here is the column, 1 is the row
  lcd.setCursor(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  //Print the first smiley
  lcd.write(byte(0));
  //Print a space between the first smiley and the next char
  lcd.print(" "); 
  //Print one word each time through the for-loop
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    if(thisChar == 0)
       lcd.print("ECE ");
    else if(thisChar == 1)
       lcd.print("Team ");
    else if(thisChar == 2)
       lcd.print("14 ");
    else if(thisChar == 3)
       lcd.print("Rulezz ");
    else
       thisChar = 10; //exit the for-loop if thisChar isn't in the interval [0, 4]
    delay(500);
  }
    //Write out another smiley char, don't need a space before
    //because the last word has a space
    lcd.write(byte(0));
  // turn off automatic scrolling
  lcd.noAutoscroll();

  //Don't need to clear the screen because we want to 
  //display the text as it scrolls
  //lcd.clear();
}

