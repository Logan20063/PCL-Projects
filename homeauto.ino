#include <neopixel.h>

#define PIXEL_PIN D2
#define PIXEL_COUNT 21
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
    
int button = 3;
int preset = 1;
bool feedingTime = false;
bool buttonPressed = false;
int wait = 50;

void setup() {
    strip.begin();
    strip.show();
    pinMode(button, INPUT_PULLDOWN);
    Time.zone(-6);
}

void loop() {
    if(Time.hour() == 17 && Time.minute() == 00 && Time.second() == 0) {
        feedingTime = true;
        Particle.publish();
    }
    checkButton();
    if(feedingTime) {
        lightShow();
    }
}

void lightShow() {
    if(preset == 1) {
        for(int i=0; i<strip.numPixels(); i++) {
            strip.clear();
            strip.setPixelColor(i, 255, 0, 0);
            strip.show();
            delay(wait);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
    }
    if(preset == 2) {
        int num1 = random(0, 255);
        int num2 = random(0, 255);
        int num3 = random(0, 255);
      for(int i=0; i<strip.numPixels(); i++) {
           strip.clear();
           strip.setPixelColor(i, num1, num2, num3);
           strip.show();
           delay(wait);
           checkButton();
           if(!feedingTime) {
               return;
           }
        }
    }
    if(preset == 3) {
        for(int i=0; i < strip.numPixels(); i++) {
            strip.clear();
            strip.setPixelColor(i, 255, 0, 0);
            strip.setPixelColor(strip.numPixels() - i - 1, 255, 0, 0);
            strip.show();
            delay(wait);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
    }
    if(preset == 4) {
        int num1 = random(0, 255);
        int num2 = random(0, 255);
        int num3 = random(0, 255);
        for(int i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, 255, 0, 0);
            strip.show();
            delay(wait);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
        for(int i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 255, 0);
            strip.show();
            delay(wait);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
        for(int i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 0, 255);
            strip.show();
            delay(wait);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
    }
}

void checkButton() {
    if(digitalRead(3) == HIGH) {
        if(!buttonPressed) {
            buttonPressed = true;
            if(feedingTime) {
                feedingTime = false;
                Particle.publish();
            strip.clear();
            strip.show();
            } else {
                preset++;
                if(preset >= 5) {
                    preset = 1;
                }
            }
        }
    } else {
        buttonPressed = false;
    }
}
