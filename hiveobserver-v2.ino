/*
 * hiveobserver-v2.ino
 * 
 * ToDo:
 *  GPS aquire almanach and Epherials erevery n search
 * 
 * Description: 
 *  Phase I sends GPS position data over LoraWAN to TTN
 *  Phase II implement Temperatur sensor
 *  Pahse III implement balance
 * 
 * License:
 *  Copyright (c) 2020 Christoph Latzer
 *  MIT License
 *  
 * Credits:
 *  Gonzalo Casas - mkrwan_03_gps_tracker.ino - GPS Tracker example code
 *  slash-dev - NeoGPS stuff
 *  ukhas.org.uk - ublox psm 
 */

//=====definitions=====================
#define debugSerial Serial

//=====includes=====================
#include "trackermkr.h"
#include "trackergps.h"
#include "trackerds18b20.h"
#include "trackerlora.h"

void setup() {
// DebugSerial
    debugSerial.begin( 9600 );
    while (!debugSerial && millis() < 5000); // Wait a maximum of 5s for Serial Monitor serial
    debugSerial.println(F("Starting up..."));
    flash(2, FAST);
// setup from sub scipts     
    mkr_setup();  // required first as it defines flash, used as visual feedback in other sub scripts
    gps_setup();
    ds18b20_setup();
    lora_setup();
}

void loop() {
// put your main code here, to run repeatedly:
    gps_position(); // writes latitude longitude altitude and satellites in global variable position
    int temperatur = ds18b20_temperatur(); // temperautue in C * 10
    int battery = battery_level(); // value from 0 - 255

    lora_send(position, temperatur, battery);

    //delay(1000 * 60 * 2);
    debugSerial.flush(); // flush everything befor going to sleep
    debugSerial.println("*** going to deep sleep");
    LowPower.deepSleep(1000 * 60 * 10); //after waking up from deepsleep the serial monitor needs to be re-opend 
    //delay(1000 * 60 * 2);
    debugSerial.println("*** woke up");
}
