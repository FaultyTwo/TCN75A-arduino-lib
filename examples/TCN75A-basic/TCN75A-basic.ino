/* TCN75A-basic
 * Author: Chawin 'FaultyTwo' Treesugol
 * Date: 11/16/2021
 * FROM: https://github.com/FaultyTwo/TCN75A-arduino-lib
 * 
 * MODIFIED: 10/09/2024
 * 
 * Desc:
 * This is the basic usage of this library.
 * Straight forward. Read temperature with 10-bit resolution.
 * *0.25C
 * 
 * Enjoy!
 */

#include "TCN75A.h"

TCN75A dvc(0X4F);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dvc.begin();
  delay(50);
  Serial.println("Hello TCN75A!");
  dvc.setResolution(0x01); //setting resolution to 10-bit
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dvc.readTemperature(); //read the sensor
  Serial.print("Current Celsius is: ");
  Serial.println(temp);
  Serial.print("Current Kelvin is: ");
  Serial.println(temp + 273.15);
  Serial.println();
  delay(2000);
}
