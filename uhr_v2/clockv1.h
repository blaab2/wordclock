#ifndef clockv1_h
#define clockv1_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <FastLED.h>

class clockv1 {
  private:

    //Private variables

    /*
      static int word_name1[];
      static int word_name2[];


      static int word_esisch[];

      static int number_3[];
      static int number_4[];
      static int number_5[];
      static int number_6[];
      static int number_7[];
      static int number_8[];*/

    static int num_leds;
    static CRGB* leds;

    static int vers;

    static int mode;
    static int h, s, v;

    //Private functions
    static void lightLED(int id);
    static void lightLEDs(int* map, int hueadd, int satadd, int mode);

    static void addWord(int* map);
    static int* shiftLEDs(int *map, int col, int row);
    static void showDigitalNumber(int number, int col, int row, int hueadd, int satadd);
    static void showWordClock(int hour, int minute);
    static int* getNames();

  public:
    // Public Functions
    clockv1(CRGB* rgbs, int num_Leds, int ver);
    static void show(int hours, int minute, int mode);
    static void setColor(int h, int s, int v);
    static void confettiNames();
    static void confetti();

};

#endif
