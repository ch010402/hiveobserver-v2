/* extraction of GPS stuff to clean up code

public:
gps_setup();
gps_position();

privat:
sendUBXcommand(MSG, sizeof(MSG))
 */

//=====includes=====================
#include <NMEAGPS.h>
//#include <GPSport.h>

//=====definitions=====================
#define gpsSerial Serial1
//// GPS
static NMEAGPS  gps; // This object parses received characters into the gps.fix() data structure
static gps_fix  fix; // Define a set of GPS fix information.
int position[4]; // Latitude, Longitude, Altitude, number of satellites
//// UBX commands
uint8_t gps_off[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x4D, 0x3B}; // Set GPS to backup mode (sets it to never wake up on its own)
uint8_t gps_on[] = {0xB5, 0x62, 0x02, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4C, 0x37}; // Restart GPS from backup mode
uint8_t gps_down[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00,0x08, 0x00, 0x16, 0x74}; // Shuts GPS reciever down 
uint8_t gps_up[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00,0x09, 0x00, 0x17, 0x76}; // Wakes GPS receiver up

//=====functions=====================
void gps_setup() {
    debugSerial.println(F("start GPS module"));
    gpsSerial.begin( 9600 );
    debugSerial.println(F("GPS module started"));
    flash(2, SLOW);
}

void sendUBXcommand(uint8_t *MSG, uint8_t len) {
    debugSerial.println(F("send UBX command"));
    if (!gpsSerial) {
        gpsSerial.begin( 9600 );
    };
    for (int i = 0 ; i < len; i++) {
        gpsSerial.write(MSG[i]);
    //    delay(10);
    }
    //gpsSerial.end();
    debugSerial.print(F("UBX command: "));
    debugSerial.print(F(MSG));
    debugSerial.println(F(" sent"));
    flash(3, FAST);
}

void gps_position() {
    debugSerial.println(F("get the GPS position"));
    
    sendUBXcommand(gps_up, sizeof(gps_up)/sizeof(uint8_t)); // wake up GPS
    bool exit = false; // set exit condition to false
    delay(1000 * 10); // give GPS time to get a fix
    while (exit == false) {
        while (gps.available(gpsSerial) > 0) {
            fix = gps.read();
            position[0] = fix.latitudeL();
            position[1] = fix.longitudeL();
            position[2] = fix.altitude_cm();
            position[3] = fix.satellites;
            if (fix.valid.location && fix.valid.altitude) {
                exit = true; // exit when the fix gives a valid location and altitude
            }
        }
    }
    sendUBXcommand(gps_down, sizeof(gps_down)/sizeof(uint8_t)); // put GPS to seleep

    debugSerial.print(F("the GPS data are: "));
    int len = sizeof(position);
    for(int i = 0; i < len; i++) {
        debugSerial.print(F(position[i]));
        debugSerial.print(F(", "));
    }
    flash(2, SLOW);
}
