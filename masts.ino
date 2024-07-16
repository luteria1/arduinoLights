//#define FASTLED_FORCE_SOFTWARE_SPI
#include <SPI.h>
#include<FastLED.h>

#define DATA_PIN 6
#define NUM_LEDS 300
#define NUM_BINS 8
CRGB leds[NUM_LEDS]; 
int input[NUM_BINS+1]; //the last bit is for beat detectionwww
//int 255 =255;
//int 255 =255;
CRGB color0 = CHSV(144,255,255);
CRGB color1 = CHSV(152,255,255);
CRGB color2 = CHSV(160,255,255);
CRGB color3 = CHSV(168,255,255);
CRGB color4 = CHSV(176,255,255);
CRGB color5 = CHSV(184,255,255);
CRGB color6 = CHSV(182,255,255);
CRGB color7 = CHSV(200,255,255);

CRGB colorArray[]={color0,color1,color2,color3,color4,color5,color6,color7};

void setup() {
	Serial.begin(8600);
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPI.attachInterrupt();

  // LED steup
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds,NUM_LEDS);
	pinMode(3,OUTPUT);
	digitalWrite(3,HIGH);
	FastLED.clear();
}

// SPI interrupt routine
int a=0;

ISR (SPI_STC_vect)
{
  byte c = SPDR;
  input[a]=(int) c;
  a++;
  if (a==8) digitalWrite(3,LOW);
}  // end of interrupt service routine (ISR) for SPI

void loop () {
	//Serial.println(a,DEC);
	if (a>=8){
		digitalWrite(3,LOW);
		FastLED.clear();
		
		int c=0;
		for (int i=0;i<NUM_BINS;i++){
			for (int ii=0;ii<(int) ((double) input[i]/240.0*((double) NUM_LEDS));ii++){
				leds[c]=colorArray[i];
				c++;
			}
		}

		FastLED.show();
		//delay(20);
		digitalWrite(3,HIGH);
		a=0;
	}
}

