#ifndef APA102_LedStreamer_h
#define APA102_LedStreamer_h
  #include "Arduino.h"
  #include "SPI.h"
  class APA102_LedStreamer
  {
    public:
		APA102_LedStreamer(unsigned int leds);		
		void setNextLed(byte r, byte g, byte b, byte bri );
		void setNextLeds(byte r, byte g, byte b, byte bri, unsigned int count = 1);
		void setLeds(unsigned int offset, unsigned int count, byte r, byte g, byte b, byte bri, byte r2 = 0, byte g2 = 0, byte b2 = 0, byte bri2 = 0, bool useBuffer = true);
		void setLeds(byte r,  byte g,  byte b, byte bri, bool useBuffer = true );
		void startFrame();
		unsigned int currentLed();
		
		unsigned int leds();
    private:
		unsigned int _leds;
		unsigned int _currentLed = 0;
  };
#endif