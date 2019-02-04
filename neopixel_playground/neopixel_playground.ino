#include <Adafruit_NeoPixel.h>
#define WS2812_PIN 4 // Pin connected to WS2812 LED
#define BUTTON_PIN 0
#define LED_PIN    5
#define NUMBER_OF_NEOPIXELS 25

// how fast the bar changes
#define MAX_BAR_DELAY 25
//how fast the little pixel moves
#define MAIN_LOOP_DELAY 40

Adafruit_NeoPixel rgb = Adafruit_NeoPixel(NUMBER_OF_NEOPIXELS, WS2812_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize hardware
  Serial.begin(115200); // Serial
  rgb.begin(); // RGB LED string
  rgb.setBrightness(16); // no need to be bright indoors
  clear_neopixels();
  pinMode(BUTTON_PIN, INPUT); // Button input
  pinMode(LED_PIN, OUTPUT); // LED output
}


void clear_neopixels() {
  for (byte i = 0; i < NUMBER_OF_NEOPIXELS; i++) {
    rgb.setPixelColor(i, 0,0,0);
  }
  rgb.show();
}

void clear_pixel(byte led) {
  rgb.setPixelColor(led, 0,0,0);
}


//-----------------------------------
byte current_led = 1;
byte bar_delay = MAX_BAR_DELAY;
byte current_bar_length = 1;
bool red_fill = true;
// ring starts lit, then a red bar grows clockwise until the ring is all red.

void loop() {

  //  slowly grow a solid ring
  if (bar_delay-- == 0) { // wait for many loop cycles before removing bar pixel
    bar_delay = MAX_BAR_DELAY;
    if (current_bar_length++ >= NUMBER_OF_NEOPIXELS) current_bar_length = 1;
  }

  // the appearing part can be dark (off) or red
  if (red_fill) {
      for (byte i = 1; i <current_bar_length; i++) {
        rgb.setPixelColor(i, 28, 0, 0);
      }
    }

  // the disappearing part is golden
  for (byte i = current_bar_length; i <= NUMBER_OF_NEOPIXELS; i++) {
    rgb.setPixelColor(i, 64, 40, 0);
  }

  // fast moving pixel overlays the ring
  clear_pixel(current_led);
  if (current_led++ > NUMBER_OF_NEOPIXELS) current_led = 1;
  rgb.setPixelColor(current_led, 0, 255, 255);

  rgb.show();
  delay(MAIN_LOOP_DELAY);
}
