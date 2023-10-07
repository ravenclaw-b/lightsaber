#include <FastLED.h>
#include <OneButton.h>

#define LED_PIN 2
#define NUM_LEDS 144
#define IGNITION_PIN 3
#define BUZZER_PIN 9 // Define the buzzer pin

bool ignited = false;

CRGB leds[NUM_LEDS];

OneButton btn = OneButton(
  IGNITION_PIN,  // Input pin for the button
  true,        // Button is active LOW
  true         // Enable internal pull-up resistor
);

void setup() 
{
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 5000);
  FastLED.clear();
  FastLED.show();

  pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an OUTPUT

  btn.attachClick(click1);
}


void loop() 
{
  // RED GREEN BLUE
  btn.tick();

  //if (ignited)
  //{
  //  for (int j = 0; j < 255; j++) 
  //  {
  //    for (int i = 0; i < NUM_LEDS; i++) 
  //    {
  //      leds[i] = CHSV(i - (j * 2), 255, 255); /* The higher the value 4 the less fade there is and vice versa */ 
  //    }
  //  FastLED.show();
  //  delay(10); /* Change this to your hearts desire, the lower the value the faster your colors move (and vice versa) */
  //  }
  //}
}

void click1()
{
  if (!ignited)
  {
    // Ignition sound
    tone(BUZZER_PIN, 440); // Start with a low-frequency sound

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(0, 0, 255);
      FastLED.show();
    }
    noTone(BUZZER_PIN);
    delay(200);
    ignited = true;
  }
  else 
  {
    // Turn-off sound
    int freq = 200;
    for (int i = NUM_LEDS-1; i >= 0; i--)
    {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
      freq += 20;
      tone(BUZZER_PIN, freq);
    }
    noTone(BUZZER_PIN);
    delay(200);
    ignited = false;
  }
}


//for (int i = 0; i < NUM_LEDS; i++)
//{
//  leds[i] = CRGB(0, 0, random(60, 255));
//}

//FastLED.show();
//delay(50);
