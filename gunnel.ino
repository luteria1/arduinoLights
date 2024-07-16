#include <FastLED.h>
#include <SPI.h>

#define NUM_BINS 8
#define NUM_LEDS 300
#define LED_PIN  6
CRGB leds[NUM_LEDS];
int input[NUM_BINS+1]; //beat detection is the last bit
uint8_t brightness;
uint8_t colorIndex[NUM_LEDS];
uint8_t index=0;

DEFINE_GRADIENT_PALETTE( greenblue_gp ) { 
  0  ,  133,  0, 252,
  89 ,  0, 237,253,
  172, 0 ,  0, 255,
  255,133,  0, 252
};

CRGBPalette16 greenblue = greenblue_gp;
int a=0;
/*
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  input[a]=(int) c;
  a++;
  if (a==9) digitalWrite(3,LOW);
  //brightness=input[8];

}  // end of interrupt service routine (ISR) for SPI
*/

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  //FastLED.setBrightness();
  
  Serial.begin(9600);
 // pinMode(MISO,OUTPUT);
  //SPCR |= _BV(SPE);

  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  FastLED.clear();
  brightness=128;
  //FastLED.setBrightness((uint8_t) brightness);

}

void loop() {
	//FastLED.setBrightness(brightness);
	uint16_t beatA = beatsin8(20, 32, 100);
    uint16_t beatB = beatsin8(20, 4, 5);
	FastLED.clear();
	
	//brightness=20;
	for (int i=0;i<NUM_LEDS;i++){
		leds[i] = ColorFromPalette(greenblue,(int) (((double)i/299.0)*255.0)+index,brightness);
	}
	index=index+beatB;
    FastLED.show();
	if (a==9){
		digitalWrite(3,HIGH);
	}
	
}

