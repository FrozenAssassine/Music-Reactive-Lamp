#include <Adafruit_NeoPixel.h>

int MusicInput = A0; //Input pin for the music
int LedOutput = 4; //Pin where the RGB-Strip is connected to
int NumberOfPixels = 21; //Number of pixels connected to the arduino
int CyclesToOff = 50; //Cycles until leds turn off if no music is played
int MaxInputValue = 500; //Play with this value

Adafruit_NeoPixel strip(NumberOfPixels, LedOutput, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(MusicInput, INPUT);
  analogReference(INTERNAL); //Set the input voltage to 1v instead of 5v
  strip.begin();
  strip.show();
}


int OffCount = 0;
void effect1(){
  int input = analogRead(MusicInput);
  int mappedinput = map(input, 0, MaxInputValue, 0, NumberOfPixels);

  if(mappedinput == 0)
  {
    OffCount++;
    if(OffCount > CyclesToOff)
    {
      OffCount = 0;
      for (int i = 0 ; i < NumberOfPixels; i++)
      {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
  }

  for(int i = mappedinput == 0 ? NumberOfPixels : mappedinput ; i< NumberOfPixels; i++)
  {
    strip.setPixelColor(i, 0,0,0);  
  }

  for (int i = 0 ; i < mappedinput; i++)
  {
    int blue = 0;
    if(i>7){
      blue = (i-7)*(i-7);
    }
    strip.setPixelColor(i, 255, 255/i, blue);
  }
  strip.show();
  delay(15); //little delay at the end
}

void loop()
{
  effect1();
}