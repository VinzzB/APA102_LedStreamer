#include <APA102_LedStreamer.h>

const int leds = 120;
const int bri = 20; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(leds); 

void setup() {  
  //set initial state OFF
  strip.setLeds(0,0,0,0,false); // arguments: r, g, b, bri, useBuffer  
}

void loop() {  
    strip.setNextLed(getRandomByte(256),getRandomByte(256),getRandomByte(256),bri);
    if (strip.currentLed() == 0) delay(100);
}

byte getRandomByte(int _max) {
    randomSeed(analogRead(0));
    return random(_max);
  }
