// 2020 August 16th
// Created by Rehaan Irani
// Credit: FastLED

#include <FastLED.h>

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

#define NUM 200
#define PIN 6

int x = 0;
int one = 0;
int two = 0;
int three = 0;
int speed = 20;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

CRGB led[NUM];

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27, 16, 2) for 16x2 LCD.

void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(led, NUM);
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (x == 0) {
    lcd.setCursor(0, 0);
    lcd.print("LED STRIP CONTROLLER");

    lcd.setCursor(6, 1);
    lcd.print("Setting?");

    lcd.setCursor(2, 2);
    lcd.print("BLUE");

    lcd.setCursor(2, 3);
    lcd.print("RED");

    lcd.setCursor(13, 2);
    lcd.print("GREEN");

    lcd.setCursor(13, 3);
    lcd.print("OTHER");

    delay(10);

    if (digitalRead(8) == HIGH) { // BLUE
      x =+ 11;
      one =+ 0;
      two =+ 255;
      three =+ 0;
      delay(100);
    }

    if (digitalRead(9) == HIGH) { // GREEN
      x =+ 12;
      one =+ 255;
      two =+ 0;
      three =+ 0;
      delay(1000);
    }

    if (digitalRead(10) == HIGH) { // RED
      x =+ 13;
      one =+ 0;
      two =+ 0;
      three =+ 255;
      delay(1000);
    }

    if (digitalRead(11) == HIGH) { // OTHER
      x =+ 4;
      delay(1000);
    }
  } // end if x == 0

  if (x > 10) {
    lcd.setCursor(2, 2);
    lcd.print("STATIONARY");

    lcd.setCursor(2, 3);
    lcd.print("BLINK");

    lcd.setCursor(13, 2);
    lcd.print("FADE ");

    lcd.setCursor(13, 3);
    lcd.print("CHASE");

    if (digitalRead(8) == HIGH) { // STATIONARY
      Serial.print("HELLO");
      for (int i = 0; i < NUM; i++) {
         led[i] = CRGB(one, two, three);
      }
      FastLED.show();
    }

    if (digitalRead(9) == HIGH) { // BLINK
      if (x > 10 && digitalRead(13) == HIGH) {
        speed -= 15;
      }

      if (digitalRead(12) == HIGH) {
        Serial.print("YES");
        speed += 15;
      }

      for (int i = 0; i < NUM; i++) {
        led[i] = CRGB(one, two, three);
      }

      FastLED.show();
      delay(speed);

      for (int i = 0; i < NUM; i++) {
        led[i] = CRGB(0, 0, 0);
      }

      FastLED.show();
      delay(speed);

      Serial.print(speed);
      Serial .print(" ");
    }

    if (digitalRead(10) == HIGH) { // FADE

      for (int i = 255; i > 0; i--) {
        setColour(i);
        delay(speed);

        if (x > 10 && digitalRead(13) == HIGH) {
          speed -= 15;
        }

        if (digitalRead(12) == HIGH) {
          Serial.print("YES");
          speed += 15;
        }

        for (int i = 0; i < 256; i++) {
          setColour(i);
          delay(speed);

          if (x > 10 && digitalRead(13) == HIGH) {
            speed -= 15;
          }

          if (digitalRead(12) == HIGH) {
            Serial.print("YES");
            speed += 15;
          }
        } // end for i = 0
      } // end for i = 255
    } // end FADE

    if (digitalRead(11) == HIGH) { // CHASE
      for (int i = 0; i < NUM; i++) {
        led[i] = CRGB(one, two, three);
        FastLED.show();
        led[i] = CRGB::Black;
        delay(speed);

        if (x > 10 && digitalRead(13) == HIGH) {
          speed -= 15;
        }

        if (digitalRead(12) == HIGH) {
          Serial.print("YES");
          speed += 15;
        }
      }
    } // end CHASE
  } // end if x > 10

  if (x == 4) {
    lcd.setCursor(0, 0);
    lcd.print("LED STRIP CONTROLLER");

    lcd.setCursor(4, 1);
    lcd.print("OTHER SETTING");

    lcd.setCursor(2, 2);
    lcd.print("PARTY");

    lcd.setCursor(2, 3);
    lcd.print("OCEAN");

    lcd.setCursor(12, 2);
    lcd.print("PARADISE");

    lcd.setCursor(12, 3);
    lcd.print("CLOUDY");

    if (digitalRead(8) == HIGH) { // PARTY
      x =+ 10;

      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; // motion speed

      FillLEDsFromPaletteColorsP(startIndex);

      FastLED.show();
      FastLED.delay(speed);
    } // end PARTY

    if (digitalRead(9) == HIGH) { // OCEAN
      x =+ 11;
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; // motion speed

      FillLEDsFromPaletteColorsO(startIndex);

      FastLED.show();
      FastLED.delay(speed);
    } // end OCEAN

    if (digitalRead(10) == HIGH) { // PARADISE
      x =+ 12;
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; // motion speed

      FillLEDsFromPaletteColorsF(startIndex);

      FastLED.show();
      FastLED.delay(speed);
    } // end PARADISE

    if (digitalRead(11) == HIGH) { // CLOUDY
      x =+ 13;
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; // motion speed

      FillLEDsFromPaletteColorsC(startIndex);

      FastLED.show();
      FastLED.delay(speed);
    } // end CLOUDY
  } // end if x == 4
}

void setColour(int val) {
    for (int i = 0; i < NUM; i++) {
      if (one > 0) {
        led[i] = CRGB(val, 0, 0);
      }

      if (two > 0) {
        led[i] = CRGB(0, val, 0);
      }

      if (three > 0) {
        led[i] = CRGB(0, 0, val);
      }
    }

    FastLED.show();
}

void pride() {
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88(87, 220, 250);
  uint8_t brightdepth = beatsin88(41, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16; // gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88(400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for(uint16_t i = 0 ; i < NUM; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16(brightnesstheta16) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV(hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM-1) - pixelnumber;

    nblend(led[pixelnumber], newcolor, 64);
  }
}

void FillLEDsFromPaletteColorsO(uint8_t colorIndex) {
  uint8_t brightness = 255;

  for(int i = 0; i < NUM; i++) {
    led[i] = ColorFromPalette(OceanColors_p, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void FillLEDsFromPaletteColorsP(uint8_t colorIndex) {
  uint8_t brightness = 255;

  for(int i = 0; i < NUM; i++) {
    led[i] = ColorFromPalette(PartyColors_p, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void FillLEDsFromPaletteColorsF(uint8_t colorIndex) {
  uint8_t brightness = 255;

  for(int i = 0; i < NUM; i++) {
    led[i] = ColorFromPalette(ForestColors_p, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void FillLEDsFromPaletteColorsC(uint8_t colorIndex) {
  uint8_t brightness = 255;

  for(int i = 0; i < NUM; i++) {
    led[i] = ColorFromPalette(CloudColors_p, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}
