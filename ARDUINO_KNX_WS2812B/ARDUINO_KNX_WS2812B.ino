/*
 * File: ARDUINO_KNX_WS2812B.ino
 * Author: Richard Haase
 * Created: 06.2021
 * Last Modified: 06.2021
 * https://github.com/TheNavy/KNX-WS2812B
 */
 
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <KnxTpUart.h>
// https://github.com/thorsten-gehrig/arduino-tpuart-knx-user-forum

// Initialize the KNX TP-UART library on the Serial port
KnxTpUart knx(&Serial, "1.2.150");

// IO Pins
const uint8_t tor1Pin = 3;     // Sensor TOR AUF
const uint8_t tor2Pin = 4;     // Sensor TOR ZU
const uint8_t ledPin =  5;     // Onboard-LED

// Globale Variablen
enum Dimmer { off, dimDown, dimUp, on };
enum DoorOpenClose { close, halfOpen, open };

Dimmer endAnimation;
DoorOpenClose tor;

bool tor_status = false; // Fährt der Motor?
bool tor_status_disable = false; // Deaktiviert den Torstatus (Tor bleibt länger aktiv!)
unsigned long tor_statusMillis = 0;
bool nacht = false; // Ist Nacht?
bool moving = false; // True sobald er feststellt, dass der Motor fährt (für Zeitfunktion)
const int torFahrzeit = 15000; // Fahrdauer des Tors
unsigned long startMillis = 0; // Startzeit des Tores
const int torTotzeit = 2000; // Pausiert die Sensoren die ersten 2 Sekunden
const int tor_statusTotzeit = 60000;

// Initialize WS2812B-LED-Strip
class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint16_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
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
  // 0 means endless cycles!
  uint8_t numberOfCycles;
  uint8_t currentCycle;

  Loop(uint8_t newnumberOfCycles) {
    numberOfCycles = newnumberOfCycles; 
    currentCycle = 0;
  }
};

Strip strip_0(300, 6, 300, NEO_GRB + NEO_KHZ800);
struct Loop strip0LoopEndless(0);
struct Loop strip0LoopOnce(1);

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
  delay(1000);
  
  knx.addListenGroupAddress("1/6/2"); //KNX-Adresse TOR
  knx.addListenGroupAddress("1/6/3"); //KNX-Adresse NACHT

  // WS2812B-LEDs Starten
  strip_0.strip.begin();
  strip_0.strip.setBrightness(128);
  strip_0.strip.show();

}

void loop() {
  // DEV-Funktion
  tor_status = true;
  
  // Die I/O Pins abfragen
  pinStatus();
  
  // Wenn der Motor anfängt zu fahren & dies noch nicht registriert wurde
  if ((tor_status) && (!moving)  && (!tor_status_disable)) {
    moving = true;
    startMillis = millis();    
  }

  // Wenn der Motor fährt
  if (moving) {
    unsigned long currentMillis = millis();
    strip_animation(1, strip0LoopEndless);
    if (currentMillis - startMillis >= torTotzeit) {
      if (tor == close) {
        //Wenn Tor ZU
        moving = false;
        endAnimation = dimDown;
        tor_status_disable = true;
        tor_statusMillis = millis();
      } else if (tor == open) {
        //Wenn Tor AUF
        moving = false;
        endAnimation = dimUp;
        tor_status_disable = true;
        tor_statusMillis = millis();
      } else if (currentMillis - startMillis >= torFahrzeit) {
        // Wenn Fahrzeit überschritten
        moving = false;
        endAnimation = dimDown;
        tor_status_disable = true;
        tor_statusMillis = millis();
      }
    }
  }

  // Wenn der Motor gefahren ist das Tor aber noch aktiv ist
  if (tor_status_disable) {
    unsigned long currentMillis = millis();
    if (currentMillis - tor_statusMillis >= tor_statusTotzeit) {
      tor_status_disable = false;
    }
  }

  // Wenn das Tor fertig gefahren ist
  if (endAnimation == dimDown) {
    // Tor runterdimmen
    if (strip_animation(2, strip0LoopOnce) & 0x01) {
      endAnimation = off;
      strip_animation(0, strip0LoopOnce);
    }
  } else if (endAnimation == dimUp) {
    if (strip_animation(3, strip0LoopOnce) & 0x01) {
      endAnimation = off;
    }
  }

 // Nacht-Licht
 if ((!moving) && (endAnimation == off) && (tor == close)) {
  // Tor zu und keine Animation aktiv
  if (nacht) {
    // Nachtlicht aktiv
  } else {
    // Nachtlicht inaktiv
  }
 }
}
