#include <APA102_LedStreamer.h>

const int leds = 120;
const int bri = 31; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(leds); 

void setup() {
  
  //set initial state OFF
  strip.setLeds(0,0,0,0,false); // arguments: r, g, b, bri, useBuffer
  
}

void loop() {

  //fade on (whites)
  for(byte x = 0; x < 255 ; x++){
    strip.setLeds(x,x,x,bri, x<255);
    delay(50);
  }
  
  delay(50);
  
  //fade off (whites)
  for(byte x = 255; x >0 ; x--){
    strip.setLeds(x,x,x,bri, x>0);
    delay(50);
  }

}
