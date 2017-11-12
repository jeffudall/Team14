/*
Group 14
ECE 411
11/11/2017


Short description: 
_____________________________________________________________________________________________________________________________
                  Uses the TCS34725 RGB sensor to detect a color and the 326 OLED actuator to display the color detected.
_____________________________________________________________________________________________________________________________


Long description: 
_____________________________________________________________________________________________________________________________
                  The TCS34725 RGB sensor allows for detection of clear, red, green, and blue light as distinct components
		  of incident light (to the sensor). Each sensor value (for clear, red, green, and blue) is a base-ten number, 
		  which can be used to distinguish different colors from each other. There are limitations to the capability 
		  of this device. For instance, detecting “light green” versus “dark green” could be difficult if not impossible 
		  because the RGB sensor readings are close to other colors. 
		  
		  Potential RGB sensor values: [0, 20,0000+]
		  Potential OLED actuator text: "Ambient", "Black", "Gray", "Blue", "Red", "Yellow", "Green", "Purple",
		  				"Pink", "Orange", "Brown"
		  
		  This program detects ambient, black, gray, blue, red, yellow, green, purple, brown, pink, and orange, 
		  using the RGB sensor. The program displays the color detected on the OLED, which can (among other things) 
		  display white font on a black background, or black font on a white background. 
		  
		  Helper functions from the RGB_OLED_Helper_Functions.h file were created by our team to facilitate the 
		  heavy-lifting for the program. 
_____________________________________________________________________________________________________________________________


Version 5.0 
_____________________________________________________________________________________________________________________________
                 Detects white (ambient), black, red, orange, yellow, green, blue, brown, purple, and pink.
                 Stores the last detected color if the LED pin is grounded.
	         Uses functions to increase: abstraction, modularity, and maintainability.
_____________________________________________________________________________________________________________________________
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

//Execute void loop() function forever, as long as the circuit has power
void loop() {
  //Check RGB sensor and get the data, then print it to the Serial Monitor
  get_and_print_RGB();
  //Get the color label (clabel) and print it to the OLED
  get_and_print_clabel();
  //Clear the last color detected
  display.clearDisplay(); 
}
