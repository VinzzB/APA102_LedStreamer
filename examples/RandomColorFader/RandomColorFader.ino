#include <APA102_LedStreamer.h>

const int leds = 120;
const int bri = 20; // Range: [0 - 31] 

APA102_LedStreamer strip = APA102_LedStreamer(leds);

const byte yellow[3] = { 254, 254, 0 };
const byte red[3]    = { 254, 0, 0 };
const byte green[3]  = { 0, 254, 0 };
const byte purple[3]  = { 128, 0, 128 }; 
const byte blue[3]   = { 0, 0, 254 };
const byte magenta[3]  = { 254, 0, 254 }; 
const byte orange[3]  = { 254, 128, 0 }; 

const byte* colors[] = { yellow, red, green, purple, blue, magenta, orange  };

byte prevColor[3] = {255,0,0};
void setup() { }

void loop() {
  int colorIdx = random(7); 
  crossFade(colors[colorIdx],255,20);
}

//colorCrossFader from https://www.arduino.cc/en/Tutorial/ColorCrossfader
int calculateStep(byte prevValue, byte endValue, int inSteps) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = inSteps/step;              //   divide by 1020
    //step = step / inSteps;
  } 
  return step;
}
//colorCrossFader from https://www.arduino.cc/en/Tutorial/ColorCrossfader
byte calculateVal(int step, byte fromVal, byte toVal, int i) {
  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,    
    if (step > 0 && fromVal < toVal) {              //   increment the value if step is positive...
      fromVal += 1;           
    } 
    else if (step < 0 && fromVal > toVal) {         //   ...or decrement it if step is negative
      fromVal -= 1;
    } 
  }
  return fromVal;
}
//colorCrossFader from https://www.arduino.cc/en/Tutorial/ColorCrossfader
void crossFade(const byte color[3], int inSteps, int wait) {

  if(color[0] == prevColor[0] && color[1] == prevColor[1] && color[2] == prevColor[2])
    return;

  int stepR = calculateStep(prevColor[0], color[0],inSteps);
  int stepG = calculateStep(prevColor[1], color[1],inSteps); 
  int stepB = calculateStep(prevColor[2], color[2],inSteps);
  for (int i = 0; i <= inSteps; i++) {    
    prevColor[0] = calculateVal(stepR, prevColor[0], color[0], i);
    prevColor[1] = calculateVal(stepG,  prevColor[1], color[1], i);
    prevColor[2] = calculateVal(stepB, prevColor[2], color[2], i);
    delay(wait);
    strip.setLeds(prevColor[0], prevColor[1],prevColor[2], bri);      
  }  
}
