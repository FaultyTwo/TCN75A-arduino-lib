/* TCN75A-interrupt
 * Author: Chawin 'FaultyTwo' Treesugol
 * Date: 11/19/2021
 * FROM: https://github.com/FaultyTwo/TCN75A-arduino-lib
 * 
 * MODIFIED: 10/09/2024
 * 
 * Desc:
 * This is the basic usage of ALERT pin in Interrupt Mode.
 * In this example. If the temperature has exceeded 50.0 celsius,
 * Arduino will halt TCN75A conversion operation.
 * 
 * Enjoy!
 */

#include "TCN75A.h"

#define INTERRUPT_PIN 2

TCN75A dvc(0X4F);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dvc.begin();
  delay(50);
  dvc.setRangeTemp(45,50);
  dvc.setAlertMode(INT_MODE);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), halt, FALLING); //attaching an interrupt pin
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(dvc.readTemperature());
  delay(1000);
}

void halt(){
  dvc.setShutdown(true); //halt TCN75A conversion
  /* Add more devices to turn off here
   * Or save the results into a EEPROM
   */
}
