/*
	Portland State University
	ECE 411
	Team 14 - Color Detector
	11/11/2017
	Portland, OR
	
	This file is the header file for the helper functions, which aid the RGB and OLED circuit software.
	
	Functions do the initialization necessary 
*/

//How much time should the detected color label get displayed on the screen?
#define COLOR_DELAY 3000 //3000 = 4 seconds

#include <RGB_OLED_Helper_Functions.h>

//Initialization code for the baud rate, RGB sensor, and the OLED screen
boolean init_RGB_OLED(void);

//Useful function for debugging; checks what the RGB sensor is reading and prints it to Serial Monitor
boolean get_and_print_RGB(void);

//Determines the label (e.g. "yellow", "red", "blue", etc.) of the color detected, then prints to the OLED
boolean get_and_print_clabel(void);

//These functions check whether the RGB sensor data is a certain color
boolean is_ambient(void);
boolean is_black(void);
boolean is_gray(void);
boolean is_orange(void);
boolean is_yellow(void);
boolean is_red(void);
boolean is_green(void);
boolean is_blue(void);
boolean is_brown(void);
boolean is_purple(void);
boolean is_pink(void);

//These functions print the detected color's label (e.g. "yellow", "red", "blue", etc.)
boolean print_ambient(void);
boolean print_black(void);
boolean print_gray(void);
boolean print_orange(void);
boolean print_yellow(void);
boolean print_red(void);
boolean print_green(void);
boolean print_blue(void);
boolean print_brown(void);
boolean print_purple(void);
boolean print_pink(void);
boolean print_retry(void);