// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            D8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int hour = 20;
int minute = 50;
int seconds = 0;

int ledHour = 0;
int ledMinute = 0;

int delay_time = 1000;
int delay_previous = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

  // End of trinket special code
  //Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
}

void loop() {

  if(millis() - delay_previous >= delay_time){
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minute += 1;
      if (minute == 60){
        hour++;
        minute = 0;
        if (hour == 25){
          hour = 1;
        }
      }
    }


    ledHour = hour%NUMPIXELS;
    ledMinute = map(minute,0,60,0,12);

    char payload[6] = "";
    sprintf(payload,"%i:%i",ledHour,ledMinute);
    Serial.println(payload);
    pixels.clear();
    if (ledHour == ledMinute){
      pixels.setPixelColor((ledHour), pixels.Color(50,50,50)); // Moderately bright green color.
    }
    else{
      pixels.setPixelColor(ledHour, pixels.Color(150,0,0)); // Moderately bright green color.
      pixels.setPixelColor(ledMinute, pixels.Color(0,150,0)); // Moderately bright green color.
    }
    pixels.show();
    delay_previous = millis();
    }
}
