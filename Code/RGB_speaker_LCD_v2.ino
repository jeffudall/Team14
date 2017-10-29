/*  
Group 14
ECE 411
10/29/2017

Color Detecting Program
Version 3.0

Short description:

  Detects color using an RBG sensor. The user is able to see the name of the detected color using the LCD or hear it 
  spoken using the speaker (requires SD card module and microSD card).
  
Long description:
  
  This program uses an SD card module to store audio files, which are recordings of different colors (e.g. "red", 
  "yellow", "blue", "green") being spoken. A speaker is used to output the sound. A Liquid Crystal Display (LCD) 
  is used as an alternative to the speaker, in order to display the name of the detected color.
  
  A state bit keeps track of which "mode" the user wants to be in: 
  
  0 for visual mode (using the LCD)
  1 for audio mode (using the speaker) 
  
  The user can specify the file names directly as shown in the void loop, for when the state bit is 1. For instance, 
  if the file name is "SQUUP8~1.WAV", then the setFile("filename") function is called in order 
  to set the specified file name:
   
  SdPlay.setFile("SQUUP8~1.WAV");
  
  Finally, the play() function can be called in order to play on the speaker the last file name that was set using
  setFile():
  
  SdPlay.play();
  
  All serial prints have been ommitted from this version in order to reduce any unnecessary complexity. If the user
  wants to use the Serial Monitor tool in order to see the printed values of the colors (for example to determine the
  C, R, G, and B values from the RGB sensor to program new color detection), then they should use the other simpler
  program, which only uses the RBG (and / or the LCD).

  Bugs: in audio mode, the speaker plays beeps when blue is detected on the RGB sensor (when the basic audio program
        is played, the speaker functions correctly -- so the problem is likely using the free() function;
        missing audio files to play for red, and for green;
        missing yellow color detection in the control structure (import this solution from the other v3 program)
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

//Convert our RGB -> eye-recognized gamma color
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Create static buffer 
//#define BIGBUFSIZE (1024)      // bigger than 2*512 is often only possible on Arduino megas!
uint8_t bigbuf[1024];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Color View Test!");
  lcd.noAutoscroll();  
  tcs.begin();
  
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER);  

lcd.clear();
}


void loop() {
  //Variables for the RGB library
  uint16_t clear, red, green, blue;
  //State for visual or audio mode; 0 means audio, 1 means visual  
  bool state = 1;

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

//If !state is true, then we are running in visual mode (using the LCD)
if(!state){
  free(bigbuf); //Get space to run in visual mode
  if(clear < 200){ //If here then there is low-light levels
    lcd.print("ambient");
    delay(2000); //2 sec delay 
    lcd.clear(); //Clear the screen
  }
  else if(r > g & r > b){ //If here then the dominant color is red
    lcd.print("red");
    delay(2000);
    lcd.clear();
  }
  else if(g > r & g > b){ //If here then the dominant color is green
    lcd.print("green");
    delay(2000);
    lcd.clear();  
  }
  else if(b > r || b > g){ //If here then the dominant color is blue
    lcd.print("blue");
    delay(2000);
    lcd.clear();    
    }
  else{ //If here then there is some error on the sensor readings
    lcd.print("error");
    delay(2000);
    lcd.clear(); 
 }
}

//If state is true, then we are running in audio mode (using the speaker and SD card)
if(state){
    uint8_t bigbuf[1024];
    SdPlay.setWorkBuffer(bigbuf, 1024);
    if(clear < 200) //If here we are at low-light levels
    delay(1);
  else if(r > g & r > b) //If here then the dominant color is red
    delay(1);
  else if(g > r & g > b) //If here then the dominant color is green
    delay(1);
  else if(b > r || b > g){ //If here then the dominant color is blue
    SdPlay.setFile("SQUUP8~1.WAV");
    SdPlay.play();
    delay(4000); //The audio files typically last at least 3 - 4 sec, so a 4 sec delay is used here
                 //Could also poll the isPlaying function until it returns false (not playing)
    }
  else //If here then there is some error on the sensor readings
    delay(1);
}

  delay(3000);
  lcd.clear();
}
