#include <APA102_LedStreamer.h>

const int bri = 20; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(120); 

byte rgbIdx = 0; //max = 2 - shifts between R, G and B colors.

void setup() {  
  //set initial state OFF
  strip.setLeds(0,0,0,0,false); // arguments: r, g, b, bri, useBuffer  
}

void loop() {
  
    // rgbIdx = random(3);     
    strip.setNextLed(rgbIdx % 3 != 0 ? 0x00 : 0xFF,
                     rgbIdx % 3 != 1 ? 0x00 : 0xFF, 
                     rgbIdx % 3 != 2 ? 0x00 : 0xFF, bri);
    
    //wait a while when the strip has received all the data.
    if (strip.currentLed() == 0) {
      delay(500);    
      incrementRgbIndex(); //shift r,g,b when starting form led 0
    }
    incrementRgbIndex(); //shift between r,g,b for every led.
}

void incrementRgbIndex() {      
    if(rgbIdx++ == 2) rgbIdx=0; //rgb counter    
  }
