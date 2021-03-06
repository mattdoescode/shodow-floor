/*
   Matthew Loewen
   11/18/2018

   This code powers the prototype dance floor

  Using 2 neo pixels as "dance lights" (they broke so code was commented out) 
  and a series of photocells to record when a shadow was cast over them
  print out a line of 0's and 1'0 to play sounds
  
*/

//Code to control the neopixels
//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h>
//#endif

//neo pixel connection pins
//const int neoPixelPin1 = 5;
//const int neoPixelPin2 = 7;
//
////num of leds
//const int NUMPIXELS = 12;

//set up leds
//Adafruit_NeoPixel neoPixel1 = Adafruit_NeoPixel(NUMPIXELS, neoPixelPin1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel neoPixel2 = Adafruit_NeoPixel(NUMPIXELS, neoPixelPin2, NEO_GRB + NEO_KHZ800);

//Analog pins were using
static const uint8_t analog_pins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};

//base brightness vals for the leds
int startingVals[10];

const int tolerance = 30;

// Measure the voltage at 5V and the actual resistance of your resistors
// This helps determine the values read from photocells
const float VCC = 4.94; // Measured voltage of Ardunio 5V line
const float R_DIV = 10080.0; // Measured resistance of 10k resistor

void setup()
{
  Serial.begin(9600);

  //neopixel code
  //  #if defined (__AVR_ATtiny85__)
  //    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //  #endif
  //
  //  neoPixel1.begin();
  //  neoPixel2.begin();
  //
  //  for (int i = 0; i < NUMPIXELS; i++) {
  //    neoPixel1.setPixelColor(i, neoPixel1.Color(150, 0, 0));
  //    neoPixel2.setPixelColor(i, neoPixel2.Color(150, 0, 0));
  //  }
  //
  //  neoPixel1.show();
  //  neoPixel2.show();

  //setup LED pins for INPUT
  for (int i = 0; i < sizeof(analog_pins); i++) {
    pinMode(analog_pins[i], INPUT);
    startingVals[i] = analogRead(analog_pins[i]);
  }
}

void loop() {

  //the string to send processing
  String sendIt = "";

  //loop through all of the pins and get values
  for (int i = 0; i < sizeof(analog_pins); i++) {
    int lightADC = analogRead(analog_pins[i]);
    float lightV = lightADC * VCC / 1023.0;
    float lightR = R_DIV * (VCC / lightV - 1.0);

    //if the invidual cell has less light than it begain with
    //ie is a shadow over the cell
    if (startingVals[i] - tolerance > lightADC) {
      sendIt += "1";
    } else {
      sendIt += "0";
    }
  }

  Serial.println(sendIt);

//  for (int i = 0; i < sizeof(analog_pins); i++) {
//    Serial.print("reading sensor " + String(i + 1) + " original ");
//    Serial.print(startingVals[i]);
//    Serial.print(" now reading ");
//    Serial.print(analogRead(analog_pins[i]));
//    Serial.println();
//  }
  delay(10);
}
