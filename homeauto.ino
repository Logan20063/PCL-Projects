#include <neopixel.h>

#define PIXEL_PIN D2
#define PIXEL_COUNT 21
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
    
int button = 3;
int preset = 1;
bool feedingTime = false;
bool buttonPressed = false;

void setup() {
    Particle.function("setFeedingTime", setFeedingTime);
    Particle.function("snippet", snippet);
    strip.begin();
    strip.show();
    pinMode(button, INPUT_PULLDOWN);
    pinMode(7, OUTPUT);
    pinMode(6, INPUT_PULLDOWN);
    Time.zone(-6);
}

void loop() {
    if(Time.hour() == 19 && Time.minute() == 45 && Time.second() == 0) {
        feedingTime = true;
        Particle.publish("Lights_red");
    }
    checkButton();
    if(feedingTime) {
        lightShow();
    }
    // if(digitalRead(6) == HIGH) {
    //     setFeedingTime("");
    // }
}

void lightShow() {
    if(preset == 1) {
        for(int i=0; i<strip.numPixels(); i++) {
            strip.clear();
            strip.setPixelColor(i, 255, 0, 0);
            strip.show();
            delay(50);
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
           delay(50);
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
            delay(50);
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
            delay(50);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
        for(int i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 255, 0);
            strip.show();
            delay(50);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
        for(int i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, 0, 0, 255);
            strip.show();
            delay(50);
            checkButton();
            if(!feedingTime) {
                return;
            }
        }
    }
}

int setFeedingTime(String param) {
    feedingTime = true;
    if(feedingTime) {
        return 1;
    } else {
        return 0;
    }
}

void checkButton() {
    if(digitalRead(3) == HIGH) {
        digitalWrite(7, HIGH);
        if(!buttonPressed) {
            buttonPressed = true;
            if(feedingTime) {
                feedingTime = false;
                Particle.publish("Light_off");
            strip.clear();
            strip.show();
            } else {
                preset++;
                if(preset >= 5) {
                    preset = 1;
                }
                delay(100);
                // strip.setPixelColor(preset - 1, 255, 0, 0);
                // delay(250);
            }
        }
    } else {
        digitalWrite(7, LOW);
        buttonPressed = false;
    }
}

int snippet(String param) {
    lightShow();
    return 0;
}