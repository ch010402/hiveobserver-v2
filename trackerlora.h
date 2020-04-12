/* extract of LoRa Stuff

prublic:
lora_setup();
lora_send();

privat:

 */

//=====includes=====================
#include <MKRWAN.h>
#include "arduino_secrets.h"

//=====definitions=====================
#define loraSerial Serial2

//// LoRaWAN
_lora_band region = EU868; // Select your region (AS923, AU915, EU868, KR920, IN865, US915, US915_HYBRID)
LoRaModem modem(loraSerial);
uint8_t txBuffer[13];

//=====functions=====================
void lora_setup() {
    if (!modem.begin(region)) {
        debugSerial.println(F("Failed to start module"));
        flash(FOREVER, VERY_FAST);
    }
    debugSerial.print("Your module version is: ");
    debugSerial.println(modem.version());
    debugSerial.print(F("Your device EUI is: "));
    debugSerial.println(modem.deviceEUI());
    
    int connected = modem.joinOTAA(appEui, appKey);
    if (!connected) {
        debugSerial.println(F("Something went wrong; are you indoor? Move near a window and retry"));
        flash(FOREVER, VERY_FAST);
    }
    debugSerial.println(F("Successfully joined the network!"));
    debugSerial.println(F("Enabling ADR and setting low spreading factor"));
    modem.setADR(true);
    modem.dataRate(5);
    flash(2, SLOW);
}

void buildPacket(int pos[], int temp, int bat) {
    debugSerial.println(F("start buliding package"));
    // reduce the numbers
    int shortlat = pos[0] / 100;
    int shortlon = pos[1] / 100;
    int alt_m = pos[2] / 100;
    int centitemp = ( temp + 500 );
    txBuffer[0] = device[0]; //device ID
    txBuffer[1] = ( shortlat >> 16 ) & 0xFF; // latitude
    txBuffer[2] = ( shortlat >> 8 ) & 0xFF;
    txBuffer[3] = shortlat & 0xFF;
    txBuffer[4] = ( shortlon >> 16 ) & 0xFF; // longitude
    txBuffer[5] = ( shortlon >> 8 ) & 0xFF;
    txBuffer[6] = shortlon & 0xFF;
    txBuffer[7] = ( alt_m >> 8 ) & 0xFF; // altitude
    txBuffer[8] = alt_m & 0xFF;
    txBuffer[9] = pos[3] & 0xFF; // satellites
    txBuffer[10] = (centitemp >> 8 ) & 0xFF; // temperatur
    txBuffer[11] = centitemp & 0xFF;
    txBuffer[12] = bat &  0xFF; // battery level
    /* future to come
    txBuffer[13] = ( weight >> 8 ) & 0xFF; // weight
    txBuffer[14] = weight & 0xFF;
    */
    debugSerial.print(F("package built: "));
    for (int i = 0; i < sizeof(txBuffer); i++) {
        debugSerial.print(txBuffer[i]);
    }
    flash(2, SLOW);
 }

void lora_send(int pos[], int temp, int bat) {
    buildPacket(pos, temp, bat); //build the package to send
    modem.beginPacket(); // send Data
    modem.write(txBuffer, sizeof(txBuffer));
    int err = modem.endPacket(false); // error handling
    if (err > 0) {
        debugSerial.print(F("Data sent"));
    }
    else {
        debugSerial.println("Error sending data");
        flash(10, VERY_FAST);
    }
    flash(2, SLOW);
}