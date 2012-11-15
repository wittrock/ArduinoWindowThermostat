#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// For backlight colors.
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int set_Temp = 22; // Is this a sane default?

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
  sensors.begin();

}

void loop() {
  sensors.requestTemperatures();
  lcd.setCursor(0,0);
  
  

  lcd.print("Temp 1 is: ");
  lcd.print(sensors.getTempCByIndex(0)); 
  lcd.setCursor(0,1);
  lcd.print("Temp 2 is: ");
  lcd.print(sensors.getTempCByIndex(1));
}
