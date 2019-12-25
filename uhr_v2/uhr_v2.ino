/* ############################################################################################# 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HEADER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * ############################################################################################# */
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <RTClib.h>
// FastLED for the LED stripes
#include <FastLED.h>
#include "clockv1.h"

#include <EEPROM.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RTC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// How many leds in your strip?
#define NUM_LEDS 150

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11

#define BRIGHTNESS 255
#define FRAMES_PER_SECOND  6<0

#define LENGTH 10

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

int height[LENGTH];

// Define the array of leds
CRGB leds[NUM_LEDS];

#define vers 0  // 0 = Daniel, 1 = Simon

clockv1 clock(leds,NUM_LEDS,vers);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED SCHEDULER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t gTimeCodeBase = 0;
uint32_t gTimeCode = 0;
uint32_t gLastTimeCodeDoneAt = 0;
uint32_t gLastTimeCodeDoneFrom = 0;

#define TC(HOURS,MINUTES,SECONDS) \
  ((uint32_t)(((uint32_t)((HOURS)*(uint32_t)(3600000))) + \
  ((uint32_t)((MINUTES)*(uint32_t)(60000))) + \
  ((uint32_t)((SECONDS)*(uint32_t)(1000)))))


#define AT(HOURS,MINUTES,SECONDS) if( atTC(TC(HOURS,MINUTES,SECONDS)) )
#define FROM(HOURS,MINUTES,SECONDS) if( fromTC(TC(HOURS,MINUTES,SECONDS)) )

static bool atTC( uint32_t tc)
{
  bool maybe = false;
  if( gTimeCode >= tc) {
    if( gLastTimeCodeDoneAt < tc) {
      maybe = true;
      gLastTimeCodeDoneAt = tc;
    }
  }
  return maybe;
}

static bool fromTC( uint32_t tc)
{
  bool maybe = false;
  if( gTimeCode >= tc) {
    if( gLastTimeCodeDoneFrom <= tc) {
      maybe = true;
      gLastTimeCodeDoneFrom = tc;
    }
  }
  return maybe;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BUTTONs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// Setze den Pin für Button1 auf 2
const byte button1Pin = 2;
const byte button2Pin = 4;

uint32_t btncheckedtime = 0;

int btn1pressed = 0;
int btn2pressed = 0;

const int poti1Pin = A2;
const int poti2Pin = A3;

// Definiere eine globale volatile Variable für den Status der MODE
int MODE = 2;


/* ############################################################################################# 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SETUP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * ############################################################################################# */
void setup () {
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  readMode();
  setup_led();

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RTC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  //Serial.begin(9600);

  //delay(100); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //while (1);
  }
  else
  {
    //rtc.adjust(DateTime(2014, 1, 22, 11, 43, 0));
    if (rtc.lostPower()) {
      Serial.println("RTC lost power, lets set the time!");
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
  }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BUTTONs ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  // Lege den Interruptpin als Inputpin ohne Pullupwiderstand fest
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // Lege die ISR 'rtc_out' auf den Interruptpin mit Modus 'RISING':
  // "Bei aufsteigender Flanke auf dem Interruptpin" --> "Führe die ISR aus"
  //attachInterrupt(digitalPinToInterrupt(button1Pin), rtc_out, RISING );
}

/* ############################################################################################# 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LOOP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * ############################################################################################# */
void loop () {
  
  // Set the current timecode, based on when the performance started
  gTimeCode = millis() - gTimeCodeBase;

  Performance();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

}

void Performance()
{
  FROM(0,0,0) { confetti(); }
  FROM(0,0,7) { clock.confettiNames(); }
  FROM(0,0,15) { normalLoop(); }
  /*
  FROM(0,0,15) { rtc.adjust(DateTime(2014, 1, 22, 0, 43, 0));}
  FROM(0,0,16) { normalLoop(); }
  FROM(0,0,20) { rtc.adjust(DateTime(2014, 1, 22, 1, 43, 0));}
  FROM(0,0,21) { normalLoop(); }
  FROM(0,0,25) { rtc.adjust(DateTime(2014, 1, 22, 2, 50, 0));}
  FROM(0,0,26) { normalLoop(); }
  FROM(0,0,30) { rtc.adjust(DateTime(2014, 1, 22, 3, 57, 0));}
  FROM(0,0,31) { normalLoop(); }
  FROM(0,0,35) { rtc.adjust(DateTime(2014, 1, 22, 4, 53, 0));}
  FROM(0,0,36) { normalLoop(); }
  FROM(0,0,40) { rtc.adjust(DateTime(2014, 1, 22, 5, 50, 0));}
  FROM(0,0,41) { normalLoop(); }
  FROM(0,0,45) { rtc.adjust(DateTime(2014, 1, 22, 6, 48, 0));}
  FROM(0,0,46) { normalLoop(); }
  FROM(0,0,50) { rtc.adjust(DateTime(2014, 1, 22, 7, 46, 0));}
  FROM(0,0,51) { normalLoop(); }
  FROM(0,0,55) { rtc.adjust(DateTime(2014, 1, 22, 8, 45, 0));}
  FROM(0,0,56) { normalLoop(); }
  FROM(0,1,00) { rtc.adjust(DateTime(2014, 1, 22, 9, 13, 0));}
  FROM(0,1,01) { normalLoop(); }
  FROM(0,1,05) { rtc.adjust(DateTime(2014, 1, 22, 10, 33, 0));}
  FROM(0,1,06) { normalLoop(); }
  FROM(0,1,10) { rtc.adjust(DateTime(2014, 1, 22, 11, 23, 0));}
  FROM(0,1,11) { normalLoop(); }*/
}

void changeTime(int hour10, int hour1, int minute10, int minute1)
{
     DateTime now = rtc.now();
     int hour010 = floor(now.hour()/10);
     int hour01  = now.hour() % 10;
     int minute010 = floor(now.minute()/10);
     int minute01  = now.minute() % 10;

     hour010 = (hour010 + hour10) % 3;

     if (hour010 == 2)
     {
        hour01 = (hour01 + hour1);
        if (hour01 > 3)
          hour01 = 0;
     }
     else
        hour01 = (hour01 + hour1) % 10;

     minute010 = (minute010 + minute10) %  6;
     minute01  = (minute01 + minute1)   % 10;
     
     rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour01+hour010*10, minute01+minute010*10, now.second()));
    
}

int getPodiHue()
{
  return analogRead(poti2Pin)*255.0/1024.0*2.1;
}

int getPodiSat()
{
  if (analogRead(poti2Pin)>400)
    return 255;
  if (analogRead(poti2Pin)>700)
    return 100;
  else
    return 0;
  
}

int getPodiV()
{
  return analogRead(poti1Pin)*255.0/1024.0;
  }

void showTime()
{    
    DateTime now = rtc.now();
    FastLED.clear();
    clock.setColor(getPodiHue(),getPodiSat(),getPodiV());
    clock.show(now.hour(),now.minute(),MODE);
    FastLED.show();
    delay(100);
}

void normalLoop()
{
  checkButtons();
  processButtons();
  
  showTime();
}

void processButtons()
{
  if (btn1pressed)
  {
    btn1pressed = 0;
    MODE++;
    if (MODE>7)
      MODE = 1;

    if (MODE < 3)
        storeMode();
  
  }
  if (btn2pressed)
  {
    btn2pressed = 0;
    if (MODE==4)
      {
         changeTime(1,0,0, 0);
      }
    if (MODE==5)
      {
         changeTime(0,1,0, 0);
      }
    if (MODE==6)
      {
         changeTime(0,0,1, 0);
      }
    if (MODE==7)
      {
         changeTime(0,0,0, 1);
      }
  }
}

void readMode()
{
  int eeAddress = 0; //EEPROM address to start reading from  
  EEPROM.get(eeAddress, MODE);
  }

void storeMode()
{
  int eeAddress = 0;   //Location we want the data to be put.
  EEPROM.put(eeAddress, MODE);
  }

void checkButtons()
{
  if (millis() - gTimeCodeBase - 150 > btncheckedtime)
  {
    if (digitalRead(button1Pin))
      btn1pressed=1;
    
    if (digitalRead(button2Pin))
      btn2pressed=1;
  
      btncheckedtime = millis() - gTimeCodeBase;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue-32 + random8(64) , 200, getPodiV());
}



void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 60;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

/* ############################################################################################# 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STUFF ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * ############################################################################################# */

void setup_led() { 
       FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
       FastLED.setBrightness(BRIGHTNESS);
       gHue =   analogRead(poti2Pin)*255.0/1024.0;
       clock.setColor(getPodiHue(),getPodiSat(),getPodiV());
       FastLED.clear();
}

