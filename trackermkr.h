/* extract of mkr stuff 

public:
flash(int count, speed [VERY_FAST, FAST, SLOW])
 */

//=====includes=====================

//=====definitions=====================
// Flash
#define VERY_FAST 50  //error
#define FAST 200      //waiting/working
#define SLOW 500      //ok
#define FOREVER -1

//=====functions=====================
// let the led flash
void flash(int times, unsigned int speed) {
  while (times == -1 || times--) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(speed);
    digitalWrite(LED_BUILTIN, LOW);
    delay(speed);
  }
}