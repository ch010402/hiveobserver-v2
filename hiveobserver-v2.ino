/*
 * hiveobserver-v2.ino
 * 
 * ToDo:
 *  reoganize and clenaup code
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
// put your setup code here, to run once:
    gps_setup();
    ds18b20_setup();
}

void loop() {
// put your main code here, to run repeatedly:
    gps_position();
    ds18b20_temperatur();

}
