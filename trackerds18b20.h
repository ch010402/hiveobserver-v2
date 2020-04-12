/* extract of DS18B20 stuff
credits to miles burton 

public:
ds18b20_setup()
ds18b20_temperature()

 */

//=====includes=====================
#include <OneWire.h>
#include <DallasTemperature.h>

//=====definitions=====================
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
float temperature = 0.0;

//=====functions=====================
void ds18b20_setup() {
    debugSerial.println(F("start DS18B20 sensor"));
    sensors.begin(); // start the sensor
    debugSerial.print(F("Found "));
    debugSerial.print(sensors.getDeviceCount(), DEC);
    debugSerial.println(F(" devices."));
    debugSerial.print(F("Parasite power is: "));
    if (sensors.isParasitePowerMode()) debugSerial.println(F("ON"));
    else debugSerial.println(F("OFF"));
    if (!sensors.getAddress(insideThermometer, 0)) {
        debugSerial.println("Unable to find address for Device 0");
        flash(FOREVER, VERY_FAST);
    }
    sensors.setResolution(insideThermometer, 9); // set the resolution
    debugSerial.print(F("Device 0 Resolution: "));
    debugSerial.print(sensors.getResolution(insideThermometer), DEC); 
    debugSerial.println();
    flash(2, SLOW);
}

void ds18b20_temperatur() {
    sensors.requestTemperatures();
    temperature = sensors.getTempC(insideThermometer);
    debugSerial.print(F("the temperature is: "));
    debugSerial.println(temperature);
    flash(2, SLOW);
}