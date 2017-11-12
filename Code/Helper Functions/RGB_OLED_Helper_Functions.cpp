/*
	Portland State University
	ECE 411
	Team 14 - Color Detector
	11/11/2017
	Portland, OR
	
	This file is the implementation for the helper functions, which aid the RGB and OLED circuit software.
*/

#include <RGB_OLED_Helper_Functions.h>

//Initialization code for the baud rate, RGB sensor, and OLED actuator
boolean init_RGB_OLED(void) {
  Serial.begin(9600); //Set the data rate (baud - bits per sec) for transmission
  //326 LCD init start
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done

  //RGB sensor init start
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    return 0; //Return failure to the calling routine
  //init done
  }
  //Clear what was last on the screen
  display.clearDisplay();
  return 1; //Return success to the calling routine
}

//Useful function for debugging; checks what the RGB sensor is reading and prints it to Serial Monitor
boolean get_and_print_RGB(void) {
  //Get the RGB sensor data
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 60ms to read 
  //Get the red, green, blue, and clear values
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  
  //Print RGB sensor data to Serial Monitor
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println();

  return 1; //Return success to the calling routine
}

boolean get_and_print_clabel(void) {
  //Check which color the RGB sensor detected, then print the name to the OLED
  if(is_ambient())
	  print_ambient();
  else if(is_black())
	  print_black();
  else if(is_gray())
	  print_gray();
  else if(is_orange())
	  print_orange();
  else if(is_yellow())
	  print_yellow();
  else if(is_red())
	  print_red();
  else if(is_green())
	  print_green();
  else if(is_blue())
	  print_blue();
  else if(is_brown())
	  print_brown();
  else if(is_purple())
	  print_purple();
  else if(is_pink())
	  print_pink();
  else
	  print_retry(); //If here, RGB sensor data doesn't match any known color labels - try to detect again
  
  return 1; //Return success to the calling routine
}

boolean is_ambient(void) {
  //Are we receiving ambient sensor readings?
  if(clear < 2000 & clear > 1000) //Yes, so return true
	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_black(void) {
  //Are we receiving black sensor readings?
  if(clear > 1500 & clear < 3500) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_gray(void) {
  //Are we receiving gray sensor readings?
  if(red > 800 & red < 2200 & green > 2800 & green < 4000 & blue > 2500 & blue < 3400) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_orange(void) {
  //Are we receiving orange sensor readings?
  if(red > 7000 & red < 11000 & green > 2200 & green < 4800 & blue > 1300 & blue < 3500) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_yellow(void) {
  //Are we receiving yellow sensor readings?
  if(red > 12500 & red < 16000 & green > 10000 & green < 15500 & blue > 4000 & blue < 7300) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_red(void) {
  //Are we receiving red sensor readings?
  if(red > 5500 & red < 7000 & green > 900 & green < 2000 & blue > 1200 & blue < 2700) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_green(void) {
  //Are we receiving green sensor readings?
  if(red > 1500 & red < 3000 & green > 5000 & green < 6700 & blue > 1600 & blue < 4500) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_blue(void) {
  //Are we receiving blue sensor readings?
  if(red > 800 & red < 1500 & green > 2900 & green < 4200 & blue > 6000 & blue < 9000) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_brown(void) {
  //Are we receiving brown sensor readings?
  if(red > 1500 & red < 2000 & green > 1500 & green < 2500 & blue > 1000 & blue < 1800) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_purple(void) {
  //Are we receiving purple sensor readings?
  if(red > 700 & red < 1200 & green > 1900 & green < 2300 & blue > 2300 & blue < 3200) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}

boolean is_pink(void) {
  //Are we receiving pink sensor readings?
  if(red > 6000 & red < 7100 & green > 3400 & green < 4200 & blue > 6000 & blue < 7500) //Yes, so return true
    	  return 1;
  else //No, so return false
	  return 0;
}


boolean print_ambient(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ambient");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_black(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Black");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_gray(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Gray");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_orange(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Orange");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_yellow(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Yellow");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_red(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Red");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_green(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Green");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_blue(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Blue");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_brown(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Brown");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_purple(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Purple");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_pink(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pink");
  display.display();
  delay(COLOR_DELAY);
  tcs.getRawData(&red, &green, &blue, &clear); //check if OLED's LED pin is grounded
  while(clear < 1400 & red < 550 & green < 500 & blue < 400)
       tcs.getRawData(&red, &green, &blue, &clear); //Stay in loop until OLED'S LED pin becomes ungrounded
	 
  return 1; //Return success to the calling routine
}

boolean print_retry(void){
  //Print the label
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Retry");
  display.display();
  delay(500); //Wait 0.5 sec because we don't want to be waiting long for the "Retry" label
	 
  return 1; //Return success to the calling routine
}
