#include <APA102_LedStreamer.h>

const int leds = 120;
const int bri = 20; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(leds); 

void setup() {
  
  //set initial state OFF
  strip.setLeds(0,0,0,0,false); // arguments: r, g, b, bri, useBuffer
  
}

void loop() {

  int snakeLength = leds / 2;
  for(unsigned int x = 0; x < strip.leds()+snakeLength;x++) {
    strip.setLeds(x <= snakeLength ? 0 : x - snakeLength, 
                  x <= snakeLength ? x : snakeLength,
                  255,255, 255, bri);
    delay(100);
  }

  //two colors
  for(unsigned int x = 0; x < strip.leds()+snakeLength;x++) {
    strip.setLeds(x <= snakeLength ? 0 : x - snakeLength, 
                  x <= snakeLength ? x : snakeLength,
                  0,  0,  255,bri, 
                  255,0,  0,  5);
    delay(100);
  }

  
}
