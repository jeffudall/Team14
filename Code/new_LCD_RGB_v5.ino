/*
Uses the 326 LCD and the TCS34725 to display the color (on the LCD).
Version 5.0 - detects white (ambient), black, red, orange, yellow, green, blue, brown, purple, and pink
            - stores the last detected color if the LED pin is grounded
			- uses functions to increase: abstraction, modularity, and maintainability
*/

//Get libraries of code for functions needed in this program
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_TCS34725.h"
#include "RGB_OLED_Helper_Functions.h"

//Objects for the OLED
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

//Global variables for storing the RGB sensor data
uint16_t clear, red, green, blue;

//Execute void setup() function only once
void setup() {
	
  if(init_RGB_OLED())
	      Serial.println("Initialization successful\n");
  else
	      Serial.println("Initialization failed\n");
	  
}

//Execute void loop() forever, as long as the circuit has power
void loop() {
	
  //Check RGB sensor and get the data, then print it to the Serial Monitor
  get_and_print_RGB();
  //Get the color label (clabel) and print it to the OLED
  get_and_print_clabel();
  //Clear the last color detected
  display.clearDisplay(); 
  
}
