/* extract of mkr stuff 

public:
flash(int count, speed [VERY_FAST, FAST, SLOW])
battery_level()
 */

//=====includes=====================
#include <pins_arduino.h>
#include "RTCZero.h"
#include <ArduinoLowPower.h>
#include <Wire.h>

//=====definitions=====================
// Flash
#define VERY_FAST 50  //error
#define FAST 200      //waiting/working
#define SLOW 500      //ok
#define FOREVER -1
// Battery
//int batterylevel[1];  // Batterylevel 0-255

//=====functions=====================
void mkr_setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void flash(int times, unsigned int speed) {
  while (times == -1 || times--) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(speed);
    digitalWrite(LED_BUILTIN, LOW);
    delay(speed);
  }
}

int battery_level() {
    int vin = A0; // the Sensor pin
    int r1 = 554; // Resistor 560kOhm
    int r2 = 1550; // Resistor 1.5MOhm
    float batteryMaxVoltage = 4.2; // maximum Battery Voltage 
    float minimumVoltage = 2.6; // minimum Battery Voltage 

    int sensorValue = analogRead(vin); // read the sensor Pin
    debugSerial.print("Input A0 = ");
    debugSerial.println(sensorValue);
    float sensorVoltage = 3.3 / 1023 * sensorValue; // interprete sensor Value compared to 3V3
    debugSerial.print("Input Voltage = ");
    debugSerial.println(sensorVoltage);
    float batteryVoltage = sensorVoltage / r2 * (r1 + r2); // calculate battery Voltage
    debugSerial.print("Battery Voltage = ");
    debugSerial.println(batteryVoltage);
    int batteryLevel = 255 / ( batteryMaxVoltage - minimumVoltage) * (batteryVoltage -minimumVoltage); // scale to 1 byte the range from 4.2 to 2.6V
    debugSerial.print("Battery level = ");
    debugSerial.println(batteryLevel);
    return batteryLevel;
}