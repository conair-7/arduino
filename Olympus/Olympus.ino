/*******************************************
 *
 * Olympus Shutter Menu 
 * by KTN
 * using: cameraIrControl Library
 * //E5.shutterNow();
 *
 ********************************************/

#include "multiCameraIrControl.h"
#include <LiquidCrystal.h>
#include "LCDKeypad.h"

//Aparat
Olympus E420(11); 

#define HOURS 0
#define MINUTES 1
#define SECONDS 2

// The LCD screen
LCDKeypad lcd;

// The time model
int hours = 0;
int minutes = 0;
int seconds = 0;
int savedhours;
int savedminutes;
int savedseconds;
unsigned int setting = 2;

//running
boolean active = false;
String statustext = "inact  ";

//backlit
unsigned long startlight;

void setup() {  // =================================== setup

  //turn on backlit
  //only for execute backlight 
  //function to start counting millis
  backlight(true);

  // Set up the LCD's number of columns and rows: 
  lcd.begin(16,2);

  // Set the cursor at the begining of the first row
  lcd.setCursor(0,0);

  // Print a text in the first row
  lcd.print("Setting: Seconds");

}  // ================================================= end setup

void loop() {  // ================================================= main loop
  // start counting if select button is pressed 
  if (active == true) decTime();
  
  // Print the time on the LCD
  printTime();

  // Listen for buttons for 1 second
  buttonListen();
  
  //turn off backlit after 10 second
  if (millis() - startlight > 10000) {
    backlight(false);
    startlight = 0;
  }
  
}  // ============================================================= end main loop

void buttonListen() {  // ============================ buttonListen
  // Read the buttons five times in a second
  for (int i = 0; i < 5; i++) {

    // Read the buttons value
    int button = lcd.button();

    switch (button) {

    // Right button was pushed
    case KEYPAD_RIGHT:
      backlight(true);
      setting++;
      break;

    // Left button was pushed
    case KEYPAD_LEFT:
      backlight(true);
      setting--;
      break;

      // Up button was pushed
    case KEYPAD_UP:
      backlight(true);
      switch (setting) {
      case HOURS:
        if (active == false) hours++;
        break;
      case MINUTES:
        if (active == false) minutes++;
        break;
      case SECONDS:
        if (active == false) seconds++;
      }     
      break;

    // Down button was pushed
    case KEYPAD_DOWN:
      backlight(true);
      switch (setting) {
      case HOURS:
        if (active == false) hours--;
        if (hours == -1) hours = 23;
        break;
      case MINUTES:
        if (active == false) minutes--;
        if (minutes == -1) minutes = 59;
        break;
      case SECONDS:
        if (active == false) seconds--;
        if (seconds == -1) seconds = 59;
        break;
      }
      break;

    // Menu button was pushed
    case KEYPAD_SELECT:
      backlight(true);
      changeStatus();
      break;
      
    }

    setting %= 3;
    printSetting();

    hours %= 24;
    minutes %= 60;
    seconds %= 60;
    printTime();

    // Wait one fifth of a second to complete
    while(millis() % 200 != 0);
  }
}  // ============================================= end buttonListen

// Print the current setting
void printSetting() {  // ========================= printSetting
  lcd.setCursor(9,0);

  switch (setting) {
  case HOURS:
    lcd.print("Hours  ");
    break;
  case MINUTES:
    lcd.print("Minutes");
    break;
  case SECONDS:
    lcd.print("Seconds");
  }
}  // ============================================= end printSetting

// Increase the time model by one second
void decTime() {  // ============================== decTime
  // Increase seconds
  seconds--;

  if (seconds < 0) {
    // Reset seconds
    seconds = 59;
    // Decrease minutes
    minutes--;

    if (minutes < 0) {
      // Reset minutes
      minutes = 59;
      // Increase hours
      hours--;
    
      //stop the counter
      if (hours < 0) {
        hours = savedhours;
        minutes = savedminutes;
        seconds = savedseconds;
        E420.shutterNow(); 
      }
    }
  }
}  // ============================================= end decTime

// Print the time on the LCD
void printTime() {  // ============================ printTime
  // Set the cursor at the begining of the second row
  lcd.setCursor(0,1);
  char time[17];
  if(active == true)  sprintf(time, "ON      %02i:%02i:%02i", hours, minutes, seconds);
  else sprintf(time, "OFF     %02i:%02i:%02i", hours, minutes, seconds);
  lcd.print(time);
}  // ============================================= end printTime

//status of a counter
void changeStatus() {  // ========================= changeStatus
  if (active == false) {
    active = true;
    savedhours = hours;
    savedminutes = minutes;
    savedseconds = seconds;
  }
  else {
    active = false;
    hours = savedhours;
    minutes = savedminutes;
    seconds = savedseconds;
  }
}  // ============================================= end changeStatus

void backlight(boolean on) { //==================== backlight
  
  if (on == true) {
    //Set LED Backlight to ON
    pinMode(10, INPUT);
    startlight = millis();
  }
  else {
    //Set LED Backlight to OFF
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
  }
  
}  // ============================================= end backlight


//=============================================================================================END
