/*
	APA102 LED Streamer. V1.00
	----------------------------------
	Created by VinzzB (Vincent Bloemen) - july 2016
	This library can (theoretically) drive up to 65.535 (2^16) - 1) leds on an ATMEGA and 4.294.967.295 (2^32 - 1) on a DUE. (integer typed value) 
	The refreshrate slows down when more LEDs are added.
	
	sources / documentation:
		https://cpldcpu.wordpress.com/2014/11/30/understanding-the-apa102-superled/
		https://github.com/pololu/apa102-arduino/blob/master/APA102.h
		https://www.youtube.com/watch?v=UYvC-hukz-0 and https://www.youtube.com/watch?v=i4qh1HFU9-s
*/

#include "Arduino.h"
#include "SPI.h"
#include "APA102_LedStreamer.h"

/* CONSTRUCTORS */
APA102_LedStreamer::APA102_LedStreamer(unsigned int leds) { 
	_leds = leds; 
	SPI.begin();
}

void APA102_LedStreamer::startFrame(){
  _currentLed = 0; //zero index  
  SPI.transfer(0); SPI.transfer(0);SPI.transfer(0); SPI.transfer(0); //start frame
}

//Set the value (in Buffer) for the next LED in line (see currentLed()). 
//bri can be set between 0 and 31. All values above 31 will set the LED at it full brightness.
//the values will show up when the next iteration for this LED occurs!
void APA102_LedStreamer::setNextLed(byte r, byte g, byte b, byte bri){
	//Needs a Startframe first?
	if(_currentLed == 0) startFrame();
	//transfer LED Frame data
	//check brightness level; (0~31)	
	SPI.transfer(bri | 0b11100000);  //3bits (MSB) = always 1 & 5bit LSB = brightness
	SPI.transfer(b);
	SPI.transfer(g);
	SPI.transfer(r);
	//increment led index. Reset led Index?
	if (++_currentLed >= _leds) {		
		_currentLed = 0;//just reset and wait for next iteration.		
	};
}

//puts the given RGB & Bri values into the buffer for the next led(s) in the line. (see currentLed())
void APA102_LedStreamer::setNextLeds(byte r, byte g, byte b, byte bri, unsigned int count){
	for(unsigned int x = 0; x < count; x++) { setNextLed(r,g,b,bri); }
}

void APA102_LedStreamer::setLeds(byte r,  byte g,  byte b, byte bri, bool useBuffer ) {
	setLeds(0,_leds,r,g,b,bri,0,0,0,0,useBuffer);
}

//This will light up a section (or all) leds with the values specified.
//Set 'useBuffer' to false if you want the LEDs to react immediatly. (not needed when continuously streaming data)
void APA102_LedStreamer::setLeds(unsigned int offset, unsigned int count, 
									   byte r,  byte g,  byte b, byte bri,  
									   byte r2, byte g2, byte b2, byte bri2, bool useBuffer ) {		
		startFrame();//always start from the beginning when using this method.
		  for (unsigned int x = 0; x < _leds; x++) { 
			//out of range, use seconde values 
			if(x < offset || x >= offset + count)
			  setNextLed(r2,g2,b2,bri2); 
			else
			//in range, use primary values.
			  setNextLed(r,g,b,bri);
		  }
		  //we can't disable the led buffer, just send the same data a seoond time...
		  if(!useBuffer) setLeds(offset,count,r,g,b,bri,r2,g2,b2,bri2,true);
}
//Tells you the LED number to set the next value for. (Zero based index!)
unsigned int APA102_LedStreamer::currentLed() { return _currentLed; }

unsigned int APA102_LedStreamer::leds() { return _leds; }