/*
 color_LCD version 4
 Integrates the RGB sensor, the LCD and speaker actuators, and the SD card module
 10/28/2017
 
 Simple SD Audio example, shows the usage of most functions 
 via terminal at serial communication port.
 
 This example shows how to use the SimpleSDAudio library for audio playback.
 You need: 
 - An Arduino with ATmega368 or better
 - An SD-Card connected to Arduinos SPI port (many shields will do)
   -> copy some converted audio files on freshly formated SD card into root folder
 - A passive loudspeaker and resistor or better: active speakers (then stereo output will be possible)
 
 Audio signal output is at the following pin:
 - Arduino with ATmega328       (many non-mega Arduinos): Pin 9
 - Arduino with ATmega1280/2560 (many mega Arduinos)    : Pin 44
 
 Using passive speaker:  
    Audio-Pin --- -[100 Ohm resistor]- ---- Speaker ---- GND
    
 Using amplifier / active speaker / line-in etc.:
    Audio-Pin --||--------------[10k resistor]----+----[1k resistor]---- GNDm
              100nF capacitor                   to amp
 
 See SimpleSDAudio.h or our website for more information:
 http://www.hackerspace-ffm.de/wiki/index.php?title=SimpleSDAudio
 
 created  29 Jun 2012 by Lutz Lisseck
 */

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <LiquidCrystal.h>
#include <SimpleSDAudio.h>

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, FILE_SIZE = 20;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Create static buffer 
#define BIGBUFSIZE (2*512)      // bigger than 2*512 is often only possible on Arduino megas!
uint8_t bigbuf[BIGBUFSIZE];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  // Setting the buffer manually for more flexibility (speaker initialization code)
  
  //LCD initialization code
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.noAutoscroll();
  tcs.begin();
  
  SdPlay.setWorkBuffer(bigbuf, BIGBUFSIZE);
 
  SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER) ; 
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  //RGB initialization code
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
  }
}

void loop() {
  //Variables for the RGB library
  uint16_t clear, red, green, blue;
  //Variables for the audio library
  uint8_t count=0, c, flag;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  // Print a message to the LCD.
  if(clear < 800)
    {
    lcd.print("Power OFF");
    }
  else if(r > b & g > b)
    lcd.print("yellow");
  else if(r > g & r > b)
    lcd.print("red");
  else if(g > r & g > b)
    lcd.print("green");
  else if(b > r || b > g){
    lcd.print("blue");
    delay(1000);
    SdPlay.setFile("SQZUP2.WAV");
    SdPlay.play();
    lcd.clear();
    delay(4000);
    }
  else
    lcd.print("error");
  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

  analogWrite(redpin, gammatable[(int)r]);
  analogWrite(greenpin, gammatable[(int)g]);
  analogWrite(bluepin, gammatable[(int)b]);
  delay(1000);
  lcd.clear();
}
