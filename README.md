# APA102_LedStreamer

This library can drive an unlimited amount of APA102 Leds on an Arduino (and compatible devices). The refreshrate will slow down when adding more leds.
If you want to change the color or brightness of one LED, you need to send commands to EVERY LED in the strip!

  SPI CONNECTION:
  
    Arduino       | Led Strip
    -----------------------------
    MOSI          | DI
    SCLK          | CI
    5V (optional) | VCC (from power supply!)
    GND           | GND

  Tha APA102 LED strip runs on 5V. You can power all 5V arduino's with the same power supply as the LED. (Check your power supply output current!)
  Use a diode between the 5V pin and VCCin of the power supply. ( arduino 5v -|<|- VCCin). This allows the current to flow from the power supply to the arduino, but not in the opposite direction. (when USB is plugged in) 
  Do not power the LED strip direclty from your Arduino device and a USB connection. It works, but this could lead to a current peak on your USB port. (if you drive more then 10 leds)
  
  
  How the streamer works.
  
  The APA102 datasheet specifies an END frame to use after you've send all the LED-frames.
  This END frame is normally used to instruct ALL leds that the data has been sent and to show the assigned color.
  Thus, all data is buffered in each led and will be shown when the END frame is sent. (or when a new LED values are sent)
  But this END frame is not needed  (see ...). We can just sent a new START frame and start over again. 
  
  Instead of using the END frame we use the data as an input buffer. 
  This means that the lights will light up when we send the second command to the LED!
  The library knows when the last LED has been set. the next frame will be sent to the first LED again!
  
  For example, We have 3 LEDS on a strip:
    1. Send a START frame and three LED frames (as RED). -> At this point you won't see any changes in the leds.
    2. Send a START frame and three LED frames (as BLUE) -> The LEDS shows their previous assigned color (=RED)
    3. on the next iteration BLUE is shown. and so on...
  
  Methods in Library
  
  CTOR: the constructor accepts one argument. the amount of Leds you want to drive with the library.
```c++
  APA102_LedStreamer(unsigned int leds);
```
  This method show you how many LEDS are driven by the lib. (= the amount you have given in the CTOR)
```c++
  unsigned int leds();
```
  This methods shows you which LED (on the strip) is being set. (zero based) 
```c++
  unsigned int currentLed();
```
  Set the color and or brightness for one or more LED(s).
```c++
  void setNextLed(byte r, byte g, byte b, byte bri );
  void setNextLeds(byte r, byte g, byte b, byte bri, unsigned int count = 1);
```
  These two methods will set ALL the Leds in strip at once. Set 'useBuffer' to false if you don't want to stream data continuously.
```c++
  void setLeds(unsigned int offset, unsigned int count, byte r, byte g, byte b, byte bri, byte r2 = 0, byte g2 = 0, byte b2 = 0, byte bri2 = 0, bool useBuffer = true);
  void setLeds(byte r,  byte g,  byte b, byte bri, bool useBuffer = true );
```
  You can force the lib to start from the first LED again.
```c++
	void startFrame();
```
		

  
  
  
