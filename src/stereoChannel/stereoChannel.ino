#include <Adafruit_NeoPixel.h>

int INPUT_L = A0; //Left channel input
int INPUT_R = A1; //Right channel input
int NumberOfPixels = 21; //Number of pixels per strip
int StripLeftOutput = 4; //Output for the left channel RGB-strip
int StripRightOutput = 3; //Output for the right channel RGB-strip
int CyclesToOff = 50; //Cycles until leds turn off if no music is played
int MaxInputValue = 500; //Play with this value

Adafruit_NeoPixel stripLeft(NumberOfPixels, StripLeftOutput, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripRight(NumberOfPixels, StripRightOutput, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(INPUT_L, INPUT);
  pinMode(INPUT_R, INPUT);
  
  //Remove this if your input voltage is higher than 1v:
  analogReference(INTERNAL); //Set the input voltage to 1v instead of 5v
  
  stripLeft.begin();
  stripRight.begin();
  stripLeft.show();
  stripRight.show();
}

int OffCountLeft = 0, OffCountRight = 0;

void RightChannel(){
  int right = analogRead(INPUT_R);
  int mappedinput = map(right, 0, 500, 0, NumberOfPixels);

  if(mappedinput == 0)
  {
    OffCountRight++;
    if(OffCountRight > CyclesToOff)
    {
      OffCountRight = 0;
      for (int i = 0 ; i < NumberOfPixels; i++)
      {
        stripRight.setPixelColor(i, 0, 0, 0);
      }
    }
  }

  for(int i = mappedinput == 0 ? NumberOfPixels : mappedinput ; i< NumberOfPixels; i++)
  {
    stripRight.setPixelColor(i, 0,0,0);  
  }

  for (int i = 0 ; i < mappedinput; i++)
  {
    //strip.setPixelColor(i,255,0,255);
    int blue = 0;
    if(i>7){
      blue = (i-7)*(i-7);
    }
    stripRight.setPixelColor(i, 255, 255/i, blue);
  }
}

void LeftChannel(){
  int left = analogRead(INPUT_L);
  int mappedinput = map(left, 0, MaxInputValue, 0, NumberOfPixels);

  if(mappedinput == 0)
  {
    OffCountLeft++;
    if(OffCountLeft > CyclesToOff)
    {
      OffCountLeft = 0;
      for (int i = 0 ; i < NumberOfPixels; i++)
      {
        stripLeft.setPixelColor(i, 0, 0, 0);
      }
    }
  }

  for(int i = mappedinput== 0 ? NumberOfPixels : mappedinput ; i< NumberOfPixels; i++)
  {
    stripLeft.setPixelColor(i, 0,0,0);  
  }

  for (int i = 0 ; i < mappedinput; i++)
  {
    //strip.setPixelColor(i,255,0,255);
    int blue = 0;
    if(i>7){
      blue = (i-7)*(i-7);
    }
    stripLeft.setPixelColor(i, 255, 255/i, blue);
  }
}

void loop() {
  RightChannel();
  LeftChannel();
  stripLeft.show();
  stripRight.show();
  delay(15);
}