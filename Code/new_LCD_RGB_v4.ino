/*
Uses the 326 LCD and the TCS34725 to display the color (on the LCD).
Version 4.0 - detects white (ambient), black, red, orange, yellow, green, blue, brown, purple, and pink
            - stores the last detected color if the LED pin is grounded
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_TCS34725.h"

// set to false if using a common cathode LED
#define commonAnode true
// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  
  Serial.begin(9600);
  //326 LCD init start
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  //RGB sensor init start
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  //init done
  }
  //Clear what was last on the screen
  display.clearDisplay();
}

void loop() {
  //Setup local variables
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 60ms to read 
  //Get the red, green, blue, and clear values
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println();
  //Print a message to the LCD.
  if(clear < 2000 & clear > 1000) //ambient 
    {
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Ambient");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    }
  else if(clear > 1500 & clear < 3500){ //black
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Black");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }
  else if(red > 800 & red < 2200 & green > 2800 & green < 4000 & blue > 2500 & blue < 3400){ //gray
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Gray");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }
  else if(red > 7000 & red < 11000 & green > 2200 & green < 4800 & blue > 1300 & blue < 3500){ //orange
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Orange");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }
  else if(red > 12500 & red < 16000 & green > 10000 & green < 15500 & blue > 4000 & blue < 7300){ //yellow
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Yellow");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }
  else if(red > 5500 & red < 7000 & green > 900 & green < 2000 & blue > 1200 & blue < 2700){ //red
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Red");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }
  else if(red > 1500 & red < 3000 & green > 5000 & green < 6700 & blue > 1600 & blue < 4500){ //green
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Green");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  } 
  else if(red > 800 & red < 1500 & green > 2900 & green < 4200 & blue > 6000 & blue < 9000){ //blue
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Blue");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    }
  else if(red > 1500 & red < 2000 & green > 1500 & green < 2500 & blue > 1000 & blue < 1800){ //brown
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Brown");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    }
  else if(red > 700 & red < 1200 & green > 1900 & green < 2300 & blue > 2300 & blue < 3200){ //purple
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Purple");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    }
  else if(red > 6000 & red < 7100 & green > 3400 & green < 4200 & blue > 6000 & blue < 7500){ //pink
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Pink");
    display.display();
    delay(4000);
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    }
  else{ //If here, we're not detecting values correctly so display error
    // text display tests
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Retry");
    display.display();
    delay(1000); //1 sec delay
    tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
    while(clear < 1400 & red < 550 & green < 500 & blue < 400)
         tcs.getRawData(&red, &green, &blue, &clear); //check if the values changed
  }      
  display.clearDisplay(); //yes, still scanning, so clear the last color detected for better accuracy 
}
