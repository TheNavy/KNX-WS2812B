// https://github.com/thorsten-gehrig/arduino-tpuart-knx-user-forum
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <KnxTpUart.h>

// Initialize the KNX TP-UART library on the Serial port
KnxTpUart knx(&Serial, "1.2.150");

// IO Pins
const int tor1Pin = 3;     // REED1-Pin für Sensor 90%
const int tor2Pin = 4;     // REED2-Pin für Sensor 10%
const int ledPin =  5;     // Onboard-LED
int tor1 = 0;
int tor2 = 0;

// Initialize WS2812B-LED-Strip
class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

Strip strip_0(120, 6, 120, NEO_GRB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);

void setup() {
  // LED-Pin als Output definieren und ausschalten
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // REED1&2-Pin als Input definieren
  pinMode(tor1Pin, INPUT);
  pinMode(tor2Pin, INPUT);

  // KNX-Bus starten
  Serial.begin(19200, SERIAL_8E1);
  knx.uartReset();

  knx.addListenGroupAddress("1/6/2");

  delay(1000);

  // WS2812B-LEDs Starten
  strip_0.strip.begin();

}

void loop() {
  //knxRead();
}
