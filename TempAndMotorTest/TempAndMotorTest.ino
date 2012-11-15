/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Stepper.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define ONE_WIRE_BUS 3

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int dir=5;
int steps=6;
int stepsVal = LOW; 
int color=0;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  lcd.setBacklight(WHITE);
  
  sensors.begin();
  
  pinMode(dir, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(13, OUTPUT);
  //5 and 6 are for the stepper motor
  //0 and 1 are for the display
  //2 is for the temps

}


void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures

  lcd.setCursor(0,0);
  lcd.print("Temp 1 is: ");
  lcd.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  lcd.setCursor(0,1);
  lcd.print("Temp 2 is: ");
  lcd.print(sensors.getTempCByIndex(1));
  
  uint8_t buttons = lcd.readButtons();

  if (buttons & BUTTON_SELECT){
    color = color + 1;
  }
  if (color == 1){
    lcd.setBacklight(RED);
  }
  else if (color == 2){
    lcd.setBacklight(GREEN);
  }
  else if (color == 3){
    lcd.setBacklight(BLUE);
  }
  else if (color == 4){
    lcd.setBacklight(WHITE);
    color = 0;
  }
  
  while(buttons & (BUTTON_UP | BUTTON_DOWN)) {
    digitalWrite(13, HIGH);
    int dirVal = 0;

    if (buttons & BUTTON_UP) {
      digitalWrite(dir, HIGH);
    } else{
      digitalWrite(dir, LOW);
    }
    
    digitalWrite(steps, HIGH);
    digitalWrite(steps, LOW);
    
    
    delayMicroseconds(100);
    buttons = lcd.readButtons();
  }
  digitalWrite(13, LOW);
}
