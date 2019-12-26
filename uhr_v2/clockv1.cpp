/*
  DCF77.c - DCF77 library 
  Copyright (c) Thijs Elenbaas 2012

*/

#include "clockv1.h"     


#define _clockv1_VERSION 1_0_0 // software version of this library

#define names_hueadd_1 60
#define names_hueadd_2 80
#define names_satadd 150
/**
 * Constructor
 */
clockv1::clockv1(CRGB* rgbs,int num_Leds, int ver) 
{
  leds = rgbs;
  num_leds = num_Leds;
  vers = ver;
}


void clockv1::showWordClock(int hour, int minute)
{

  int hueadd =0;
  int satadd =0;

  int on[20];

  if (vers == 0)
  {
    // Daniel
    on[0] = 6;
    on[1] = 14;
    on[2] = 29;
    on[3] = 44;
    on[4] = 59;
    on[5] = 74;
    on[6] = 89;
    lightLEDs(on,names_hueadd_1,names_satadd,0);
    

    // Julia
    on[0] = 5;
    on[1] = 13;
    on[2] = 28;
    on[3] = 43;
    on[4] = 58;
    on[5] = 73;
    lightLEDs(on,names_hueadd_2,names_satadd,0);
  }

  if (vers == 1)
  {
    // Simon
    on[0] = 5;
    on[1] = 89;
    on[2] = 104;
    on[3] = 119;
    on[4] = 134;
    on[5] = 149;
    lightLEDs(on,names_hueadd_1,names_satadd,0);
     
    // Nadine
    on[0] = 6;
    on[1] = 14;
    on[2] = 28;
    on[3] = 42;
    on[4] = 56;
    on[5] = 70;
    on[6] = 84;
    lightLEDs(on,names_hueadd_2,names_satadd,0);
  }



      if (mode==1)
    {
      s = 0;
      h = 0;
    } 

  
  // Es isch
  on[0] = 6;
  on[1] = 0;
  on[2] = 1;
  on[3] = 3;
  on[4] = 4;
  on[5] = 5;
  on[6] = 6;
  lightLEDs(on,hueadd,satadd,0);


  // Glei
  if (minute % 5 > 2)
  {
    if (vers == 0)
    {
    on[0] = 4;
    on[1] = 9;
    on[2] = 10;
    on[3] = 11;
    on[4] = 12;
    lightLEDs(on,hueadd,satadd,0);
    }
    if (vers == 1)
    {
    on[0] = 4;
    on[1] = 10;
    on[2] = 11;
    on[3] = 12;
    on[4] = 13;
    lightLEDs(on,hueadd,satadd,0);
    }
  }


  // FENF
  if ((minute >= 3 && minute <= 7) || (minute >= 23 && minute <= 27) || (minute >= 33 && minute <= 37) || (minute >= 53 && minute <= 57))
  {
    on[0] = 4;
    on[1] = 15;
    on[2] = 16;
    on[3] = 17;
    on[4] = 18;
    lightLEDs(on,hueadd,satadd,0);
  }


  // ZEHN
  if ((minute >= 8 && minute <= 12) || (minute >= 18 && minute <= 22) || (minute >= 38 && minute <= 42) || (minute >= 48 && minute <= 52))
  {
    on[0] = 4;
    on[1] = 19;
    on[2] = 20;
    on[3] = 21;
    on[4] = 22;
    lightLEDs(on,hueadd,satadd,0);
  }


  // VOR
  if ((minute >= 18 && minute <= 27) || (minute >= 48 && minute <= 57))
  {
    on[0] = 3;
    on[1] = 30;
    on[2] = 31;
    on[3] = 32;
    lightLEDs(on,hueadd,satadd,0);
  }


  // NACH
  if ((minute >= 3 && minute <= 12) || (minute >= 33 && minute <= 42))
  {
    on[0] = 4;
    on[1] = 24;
    on[2] = 25;
    on[3] = 26;
    on[4] = 27;
    lightLEDs(on,hueadd,satadd,0);
  }

  // VIERDL
  if ((minute >= 13 && minute <= 17) || (minute >= 43 && minute <= 47))
  {
    on[0] = 6;
    on[1] = 38;
    on[2] = 39;
    on[3] = 40;
    on[4] = 41;
    on[5] = 42;
    on[6] = 43;
    lightLEDs(on,hueadd,satadd,0);
  }

  // DREi (VIERDL)
  if (minute >= 43 && minute <= 47)
  {
    on[0] = 4;
    on[1] = 34;
    on[2] = 35;
    on[3] = 36;
    on[4] = 37;
    lightLEDs(on,hueadd,satadd,0);
  }

  // HALBER
  if (minute >= 18 && minute <= 42)
  {
    on[0] = 6;
    on[1] = 45;
    on[2] = 46;
    on[3] = 47;
    on[4] = 48;
    on[5] = 49;
    on[6] = 50;
    lightLEDs(on,hueadd,satadd,0);
  }

  // IN DER FRIA
  if (hour >= 2 && hour <= 10)
  {
    on[0] = 9;
    on[3] = 120;
    on[4] = 121;
    on[5] = 123;
    on[6] = 124;
    on[7] = 125;
    on[8] = 126;
    on[9] = 127;
     if (vers == 0)
    {
    on[1] = 118;
    on[2] = 119;
    }
    if (vers == 1)
    {
    on[1] = 117;
    on[2] = 118;
    }
    
    lightLEDs(on,hueadd,satadd,0);
  }

  // MIDDAGS
  if (hour >= 11 && hour <= 16)
  {
    on[0] = 7;
    on[1] = 142;
    on[2] = 143;
    on[3] = 144;
    on[4] = 145;
    on[5] = 146;
    on[6] = 147;
    on[7] = 148;
    lightLEDs(on,hueadd,satadd,0);
  }
  
  // ABENDS
  if (hour >= 17 && hour <= 22)
  {
    on[0] = 6;
    on[1] = 135;
    on[2] = 136;
    on[3] = 137;
    on[4] = 138;
    on[5] = 139;
    on[6] = 140;
    lightLEDs(on,hueadd,satadd,0);
  }
  
  // NACHDS
  if (hour >= 23 || hour <= 1)
  {
    if (vers == 0)
    {
    on[0] = 6;
    on[1] = 129;
    on[2] = 130;
    on[3] = 131;
    on[4] = 132;
    on[5] = 133;
    on[6] = 134;
    }
    if (vers == 1)
    {
    on[0] = 6;
    on[1] = 128;
    on[2] = 129;
    on[3] = 130;
    on[4] = 131;
    on[5] = 132;
    on[6] = 133;
    }
    lightLEDs(on,hueadd,satadd,0);
  }
  
  if ( minute > 12)
    hour++;

  hour = hour % 12;

    
  if (hour == 1)
  {
    on[0] = 4;
    on[1] = 85;
    on[2] = 86;
    on[3] = 87;
    on[4] = 88;
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 2)
  {
    if (vers == 0)
    {
    on[0] = 5;
    on[1] = 68;
    on[2] = 69;
    on[3] = 70;
    on[4] = 71;
    on[5] = 72;
    }
    if (vers == 1)
    {
    on[0] = 5;
    on[1] = 53;
    on[2] = 54;
    on[3] = 55;
    on[4] = 56;
    on[5] = 57;
    }
    lightLEDs(on,hueadd,satadd,0);
  }
  
  if (hour == 3)
  {
    on[0] = 5;
    on[1] = 75;
    on[2] = 76;
    on[3] = 77;
    on[4] = 78;
    on[5] = 79;
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 4)
  {
      if (vers == 0)
    {
    on[0] = 5;
    on[1] = 112;
    on[2] = 113;
    on[3] = 114;
    on[4] = 115;
    on[5] = 116;
    }
      if (vers == 1)
    {
      on[0] = 5;
      on[1] = 80;
      on[2] = 81;
      on[3] = 82;
      on[4] = 83;
      on[5] = 84;
    }
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 5)
  {
     if (vers == 0)
    {
    on[0] = 5;
    on[1] = 80;
    on[2] = 81;
    on[3] = 82;
    on[4] = 83;
    on[5] = 84;
    }
    if (vers == 1)
    {
    on[0] = 4;
    on[1] = 112;
    on[2] = 113;
    on[3] = 114;
    on[4] = 115;
      }
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 6)
  {
      if (vers == 0)
    {
    on[0] = 6;
    on[1] = 52;
    on[2] = 53;
    on[3] = 54;
    on[4] = 55;
    on[5] = 56;   
    on[6] = 57;
    }
      if (vers == 1)
    {
    on[0] = 6;
    on[1] = 60;
    on[2] = 61;
    on[3] = 62;
    on[4] = 63;
    on[5] = 64;   
    on[6] = 65;
    }
    
    lightLEDs(on,hueadd,satadd,0);
  }


  if (hour == 7)
  {
    
    on[0] = 7;
    on[1] = 105;
    on[2] = 106;
    on[3] = 107;
    on[4] = 108;
    on[5] = 109;   
    on[6] = 110;
    on[7] = 111;
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 8)
  {
    on[0] = 5;
    on[1] = 90;
    on[2] = 91;
    on[3] = 92;
    on[4] = 93;
    on[5] = 94;
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 9)
  { 
     if (vers == 0)
    {
    on[0] = 5;
    on[1] = 63;
    on[2] = 64;
    on[3] = 65;
    on[4] = 66;
    on[5] = 67;
    }
    if (vers == 1)
    {
    on[0] = 5;
    on[1] = 70;
    on[2] = 71;
    on[3] = 72;
    on[4] = 73;
    on[5] = 74;
      }
    lightLEDs(on,hueadd,satadd,0);
  }

  if (hour == 10)
  {
     if (vers == 0)
    {
    on[0] = 5;
    on[1] = 60;
    on[2] = 61;
    on[3] = 62;
    on[4] = 63;
    on[5] = 64;
    }
    if (vers == 1)
    {
      on[0] = 5;
    on[1] = 67;
    on[2] = 68;
    on[3] = 69;
    on[4] = 70;
    on[5] = 71;
    }
    lightLEDs(on,hueadd,satadd,0);
  }
    
  if (hour == 11)
  {
    on[0] = 4;
    on[1] = 100;
    on[2] = 101;
    on[3] = 102;
    on[4] = 103;
    lightLEDs(on,hueadd,satadd,0);
  }
  
  if (hour == 0)
  {
    on[0] = 6;
    on[1] = 95;
    on[2] = 96;
    on[3] = 97;
    on[4] = 98;
    on[5] = 99;
    on[6] = 100;
    lightLEDs(on,hueadd,satadd,0);
  } 

  
}

/**
 * converts an integer to a led mapping
 */
void clockv1::showDigitalNumber(int number,int col, int row, int hueadd, int satadd)
{

  int on[20];

  on[0] = 0;
  
  if (number==1)
  {
    on[0] = 5;
    on[1] = 3;
    on[2] = 18;
    on[3] = 33;
    on[4] = 48;
    on[5] = 63;
    
  }
  
  if (number==2)
  {
    on[0] =  17;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  20;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  46;
    on[13] =  61;
    on[14] =  62;
    on[15] =  63;
    on[16] =  64;
    on[17] =  65;
  }

  if (number==3)
  {
    on[0] =  17;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  20;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  50;
    on[13] =  61;
    on[14] =  62;
    on[15] =  63;
    on[16] =  64;
    on[17] =  65;
  }

   if (number==4)
  {
    on[0] =  11;
    on[1] =  1;
    on[2] =  16;
    on[3] =  5;
    on[4] =  20;
    on[5] =  31;
    on[6] =  32;
    on[7] =  33;
    on[8] =  34;
    on[9] =  35;
    on[10] =  50;
    on[11] =  65; 
  }

   if (number==5)
  {
    on[0] =  17;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  16;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  50;
    on[13] =  61;
    on[14] =  62;
    on[15] =  63;
    on[16] =  64;
    on[17] =  65;
  }


     if (number==6)
  {
    on[0] =  18;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  16;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  46;
    on[13] =  61;
    on[14] =  62;
    on[15] =  63;
    on[16] =  64;
    on[17] =  65;
    on[18] =  50;
  }


     if (number==7)
  {
    on[0] =  11;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  33;
    on[7] =  34;
    on[8] =  35;
    on[9] =  65;
    on[10] =  50;
    on[11] =  20;
  }


     if (number==8)
  {
    on[0] =  19;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  16;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  46;
    on[13] =  61;
    on[14] =  62;
    on[15] =  63;
    on[16] =  64;
    on[17] =  65;
    on[18] =  50;
    on[19] =  20;
  }


     if (number==9)
  {
    on[0] =  18;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  16;
    on[7] =  31;
    on[8] =  32;
    on[9] =  33;
    on[10] =  34;
    on[11] =  35;
    on[12] =  61;
    on[13] =  62;
    on[14] =  63;
    on[15] =  64;
    on[16] =  65;
    on[17] =  50;
    on[18] =  20;
  }

     if (number==0)
  {
    on[0] =  16;
    on[1] =  1;
    on[2] =  2;
    on[3] =  3;
    on[4] =  4;
    on[5] =  5;
    on[6] =  16;
    on[7] =  31;
    on[8] =  35;
    on[9] =  46;
    on[10] =  61;
    on[11] =  62;
    on[12] =  63;
    on[13] =  64;
    on[14] =  65;
    on[15] =  50;
    on[16] =  20;
  }
  
  
  lightLEDs(shiftLEDs(on,col,row),hueadd,satadd,0);

  
}

void clockv1::show(int hours, int minutes, int Mode)
{

  int hour10 = 0; //CRGB::Black;
  int hour1 = 0; //CRGB::Black;
  int minute10 = 0; //CRGB::Black;
  int minute1 = 0; //CRGB::Black;

  mode = Mode;
  
  /* Digital MODE */
  if (mode==4)
  {
    hour10 = 126; //CRGB::Red;
  }
  else if(mode==5)
  {
    hour1 = 126; //CRGB::Red;
  } 
  else if(mode==6)
  {
    minute10 = 126; //CRGB::Red;
  } 
  else if(mode==7)
  {
    minute1 = 126; //CRGB::Red;
  }
 
  if (mode >2)
  {
    FastLED.clear();
 
    showDigitalNumber((int) floor( hours / 10.0),0,0,hour10,0);
    showDigitalNumber( hours % 10,8,0,hour1,0);
    
    showDigitalNumber((int) floor( minutes / 10.0),0,5,minute10,0);    
    showDigitalNumber( minutes % 10,8,5,minute1,0);
  }
  else
  {

     fadeToBlackBy( leds, num_leds, 10);
     showWordClock(hours, minutes);
    }



    FastLED.show();
 
}


/**
 * Shifts a map "col" fields to the right and "row" fields downwards
 */
int* clockv1::shiftLEDs(int* map,int col,int row)
{
  int i;
  
  for(i = 1; i < map[0]+1; i++)
  {
    for (int c = 1; c <= col; c++)
    {
      map[i]=map[i]+1;
      
      if (map[i] % 15 == 0)
      {
        map[i] = map[i] - 15;
      }
    }
    for (int r = 1; r <= row; r++)
    {
      map[i]=map[i]+15;
      
      if (map[i] > 150)
      {
        map[i] = map[i] - 150;
      }
    }
  }
  
  return map;
  
}



void clockv1::lightLEDs(int* map, int hueadd, int satadd, int mode2)
{
    int font_map[150] =   { 14,  13, 12,  11,  10,  9,   8,    7,   6,    5,   4,   3,   2,   1,   0,
                15,  16, 17,  18,  19,  20,  21,  22,  23,   24,  25,  26,  27,  28,  29,
                44,  43, 42,  41,  40,  39,  38,  37,  36,   35,  34,  33,  32,  31,  30,
                45,  46, 47,  48,  49,  50,  51,  52,  53,   54,  55,  56,  57,  58,  59,
                74,  73, 72,  71,  70,  69,  68,  67,  66,   65,  64,  63,  62,  61,  60,
                75,  76, 77,  78,  79,  80,  81,  82,  83,   84,  85,  86,  87,  88,  89,
                104, 103, 102, 101, 100, 99,  98,  97,  96,   95,  94,  93,  92,  91,  90,
                105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
                134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120,
                135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149
                };

              
    for(int i = 1; i<map[0]+1;i++)
    {
      if (map[i]<255)
      {
        if (mode2 == 0)
        leds[font_map[map[i]]] = CHSV(h+hueadd,s+satadd,v);
        else
        leds[font_map[map[i]]] += CHSV(h+hueadd,s+satadd,v);      
      }         
    }
  
}



void clockv1::setColor(int H, int S, int V)
{
  h = H;
  s = S;
  v = V;
}


void clockv1::confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, num_leds, 10);
  int pos = random16(num_leds);
  //leds[pos] += CHSV( gHue-32 + random8(64) , 200, getPodiV());
  
  int on2[2];
  on2[0] = 1;
  on2[1] = pos;
  

  lightLEDs(on2, random8(64)-32,0,1);
}

void clockv1::confettiNames() 
{

   int on[20];


 if (vers == 0)
  {
    on[0] = 11;
    on[1] = 14;
    on[2] = 29;
    on[3] = 44;
    on[4] = 59;
    on[5] = 74;
    on[6] = 89;
    on[7] = 13;
    on[8] = 28;
    on[9] = 43;
    on[10] = 58;
    on[11] = 73;
  }

  if (vers == 1)
  {
    // Simon
    on[0] = 11;
    on[1] = 89;
    on[2] = 104;
    on[3] = 119;
    on[4] = 134;
    on[5] = 149;
    on[6] = 14;
    on[7] = 28;
    on[8] = 42;
    on[9] = 56;
    on[10] = 70;
    on[11] = 84;

  }

                    
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, num_leds, 10);
  int pos = random8(on[0])+1;

  int on2[2];
  on2[0] = 1;
  on2[1] = on[pos];
  

  lightLEDs(on2, (names_hueadd_1+names_hueadd_2)/2.0f,names_satadd,1);
  //leds[font_map[on[pos]]] += CHSV( gHue-10+70 + random8(20) , getPodiSat(), getPodiV());
  delay(10);
}

/**
 * Initialize parameters
 */


int clockv1::vers = 0;
int clockv1::h = 0;
int clockv1::s = 0;
int clockv1::v = 255;
int clockv1::mode = 0;
int clockv1::num_leds = 150;
CRGB* clockv1::leds;

