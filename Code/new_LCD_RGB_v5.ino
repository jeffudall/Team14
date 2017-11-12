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
		  because the RGB sensor readings are close to other colors. Also, unless the object is within 1 cm or less of 
		  the RGB sensor's photodiode array, the sensor's accuracy becomes worse. (Each photodiode in the array is 
		  responsible for one of the detected values of clear, red, green, and blue, which are controlled internally
		  by a Finite State Machine.) The OLED uses Serial Peripheral Interface (SPI) to communicate with the Arduino.
		  
		  Expected input range (RGB sensor values): [0, 20,0000+] (dimensionless positive integers)
		  Expected output (OLED actuator text): "Ambient", "Black", "Gray", "Blue", "Red", "Yellow", "Green", "Purple",
		  				"Pink", "Orange", "Brown", "Retry" (string of characters)
						
		  If the RGB's LED pin is grounded, then the program will display the last detected label. Once the LED pin 
		  is ungrounded, the OLED will start to detect new colors again. The program displays the color detected on 
		  the OLED, which can (among other things) display white font on a black background, or black font on a white 
		  background. 
		  
		  This program detects ambient, black, gray, blue, red, yellow, green, purple, brown, pink, and orange, 
		  using the RGB sensor. If the RGB sensor data does not map to one of these labels, then it displays "Retry"
		  until it detects a known label mapping. 
		  
		  The control logic for this program operates under the following assumption: a solid object is presented 
		  to the RGB sensor, within (or less than) 1 cm. The OLED's LED pin becomes ungrounded (after previously
		  being grounded), and gets the RGBC values of the object. Then, an if-else structure determines which color
		  was detected. Multiple solid objects of distinct colors were tested such that the unique colors tested
		  were mapped to the following ranges for R, G, and B:
		  
		  r_l < R < r_h ; 		g_l < G < g_h ; 		b_l < B < b_h;
		  
		  where the _l and _h subscripts indicate the lower and higher bounds of the detected value, respectively.
		  This means that after presenting a red object to the sensor, the values for R, G, and B can be approximated
		  using the Serial Monitor. Once approximated, the lower and higher bounds that red could assume were 
		  implemented in the control structure (shown in the .cpp file for the helper functions).
		  
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
