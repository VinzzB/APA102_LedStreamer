#include <APA102_LedStreamer.h>

const int leds = 120;
const int bri = 20; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(leds); 

void setup() {
  
  //set initial state OFF
  strip.setLeds(0,0,0,0,false); // arguments: r, g, b, bri, useBuffer
  
}

void loop() {
  
  //On (White)
  strip.setLeds(255,255,255,bri,false);
  delay(10000);
  
  //Off
  strip.setLeds(0,0,0,0,false);
  delay(10000);
}
