/*
  Rainbow example for APA102_LedStreamer created by VinzzB.

  SPI Connection:
  
    Arduino       | Led Strip
    -----------------------------
    MOSI          | DI
    SCLK          | CI
    5V (optional) | VCC (from power supply!)
    GND           | GND

  Tha APA102 LED strip runs on 5V. You can power all 5V arduino's with the same power supply.  (Check power supply output current!)
  Use a diode between the 5V pin and VCCin of the power supply. ( arduino 5v -|<|- VCCin). This allows the current to flow from the power supply to the arduino, but not in the opposite direction. (when USB is plugged in) 

  DataMembers:
   - leds: The amount of leds used on the strip.
   - bri : the brightness of the LED. Range between 0 and 31. 0 = OFF. 31 = Full brightness
   - colorOffsetPerLed: Range between [0 and 750]. 
                        0 = no rainbow, fades between the rainbow colors for the whole strip. 
                        1 = the widest rainbow. This rainbow fits on a 750 Led strip. Or scrolls on smaller strips.
                        >1 = smller rainbows. This will skip some colors between each LED. Calculations slows the rainbow down when scrolling!
   - highResolution: High resolution fade. True = slower but smoother | False = faster but less smooth when using offsets.
   - prevColor: The color to start with. After that, changes when fading or scrolling.
*/

#include <APA102_LedStreamer.h>

//Datamembers
const int leds = 120;
const int bri = 20; // Range: [0 - 31] 
int colorOffsetPerLed = 10; // Range: [1 - 750] 
bool highResolution = true; 
byte prevColor[3] = {255,0,0};

//init lib
APA102_LedStreamer strip = APA102_LedStreamer(leds);

void setup() { 
    pinMode(10,OUTPUT);
    digitalWrite(10,LOW);
    pinMode(4,OUTPUT);
    digitalWrite(4,LOW);
  }

void loop() {
  
  //high resolution rainbow (slower)
  writeRainbowToStrip(colorOffsetPerLed,highResolution);
  //use delay or a millis() calculation to slow the rainbow scroll down. 
  delay(100);
}


void writeRainbowToStrip(int colorOffset, bool highRes){
  byte newColor[3];/*=*/memcpy(newColor,prevColor,3);
  for(unsigned int l =0;l < strip.leds(); l++) {
    if(highRes && strip.currentLed() == 0){
            getNextRainbowColor(newColor,1);
            memcpy(prevColor,newColor,3);
    }  
    getNextRainbowColor(newColor, colorOffset);
    strip.setNextLed(newColor[0],newColor[1],newColor[2],bri);
    if(!highRes &&strip.currentLed() == 1) memcpy(prevColor,newColor,3);
  }
}


void getNextRainbowColor(byte* inrgb, int colorOffset){
    //VinzzB: refactored code from https://gist.github.com/jamesotron/766994
    //iterate through offset for a nice fade effect. 
    for(int x = 0; x < colorOffset;x++){ 
      //Calculate which RGB (0/1/2) value to decrement and which to increment.
      int decColor = inrgb[2] == 0 && inrgb[0] !=0 ? 0 : inrgb[0] == 0 && inrgb[1] != 0 ? 1 : 2;
      int incColor =  decColor == 2 ? 0 : decColor + 1;
      //apply the new value.
      if (inrgb[decColor] >0) inrgb[decColor] -= 1;
      if (inrgb[incColor] <255) inrgb[incColor] += 1;
    }
}
