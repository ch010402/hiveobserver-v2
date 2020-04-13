/* extract of mkr stuff 

public:
flash(int count, speed [VERY_FAST, FAST, SLOW])
battery_level()
 */

//=====includes=====================
#include <pins_arduino.h>
#include "RTCZero.h"
#include <ArduinoLowPower.h>

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
    float battery_voltage = 4.2; // use voltmeter
    int batterylevel;

    analogReadResolution(10);
    analogReference(AR_INTERNAL1V0); 
    //AR_DEFAULT: the default analog reference of 3.3V 
    //AR_INTERNAL1V0: a built-in 1.0V reference
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023)
    float voltage = sensorValue * (battery_voltage / 1023.0);
    // print out the value you read:
    debugSerial.print("Voltage: ");
    debugSerial.print(voltage);
    debugSerial.println("V");

    analogReference(AR_DEFAULT);

    batterylevel = sensorValue / 2;
    return batterylevel;
    
    flash(2, SLOW);
}
