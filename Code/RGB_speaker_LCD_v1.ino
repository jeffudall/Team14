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
//byte gammatable[256];
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
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

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
    delay(4000);
    }
  else //If here then there is some error on the sensor readings
    delay(1);
}

  delay(3000);
  lcd.clear();
}
