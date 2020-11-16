// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"

const int sensorPin = A3;

float temperatura;
int co2, tvoc;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

Adafruit_SGP30 sgp;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for serial console to open!
  }

  Serial.println("SGP30 test");

  if (! sgp.begin()) {
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

}
  void loop() {

    stemperatura();
    sgp30();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.setCursor(2, 0);
    lcd.print(temperatura);
    lcd.setCursor(7, 0);
    lcd.print("VOC:");
    lcd.setCursor(11, 0);
    lcd.print(tvoc);


    lcd.setCursor(0, 1);
    lcd.print("CO2:");
    lcd.setCursor(5, 1);
    lcd.print(co2);
    lcd.setCursor(13, 1);
    lcd.print("ppm");

    delay(1000);
  }


  void sgp30() {
    if (! sgp.IAQmeasure()) {
      Serial.println("Measurement failed");
      return;
    }
    tvoc = sgp.TVOC;
    co2 = sgp.eCO2;
    Serial.println(co2);
    Serial.println(tvoc);
  }
  void stemperatura()
  {
    int value = analogRead(sensorPin);
    Serial.println("VALUEE");
    Serial.println(value);
    float millivolts = (value / 1024.0) * 4400;
    temperatura = millivolts / 10;
    Serial.println(temperatura);
    delay(100);
  }
