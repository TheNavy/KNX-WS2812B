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


void setup() {
  // LED-Pin als Output definieren und ausschalten
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // REED1&2-Pin als Input definieren
  pinMode(tor1Pin, INPUT);
  pinMode(tor2Pin, INPUT);

  Serial.begin(19200, SERIAL_8E1);
  knx.uartReset();

  knx.addListenGroupAddress("1/6/2");

  delay(1000);

}

void loop() {
  knxRead();
}

void knxRead() {
  KnxTpUartSerialEventType eType = knx.serialEvent();
  if (eType == TPUART_RESET_INDICATION) {
  } 
  else if (eType == UNKNOWN) {
  } 
  else if (eType == KNX_TELEGRAM) {
    KnxTelegram* telegram = knx.getReceivedTelegram();
    // Telegrammauswertung auf KNX (bei Empfang immer notwendig)
    String target =
      String(0 + telegram->getTargetMainGroup())   + "/" +
      String(0 + telegram->getTargetMiddleGroup()) + "/" +
      String(0 + telegram->getTargetSubGroup());

    // Here you have the telegram and can do whatever you want
    if (telegram->getCommand() == KNX_COMMAND_WRITE) {
      // Auswertung des empfangenen KNX-Telegrammes mit Schreibbefehl (Flag) -> Aktion
      if (target == "1/6/2") {
        int received_1_6_2 = telegram->getBool();
        if (received_1_6_2) {
          digitalWrite(ledPin, HIGH);
        }
        else {
          digitalWrite(ledPin, LOW);
        }
      }
    }
  }
}


/*
void pinStatus(){
  tor1 = digitalRead(tor1Pin);
  tor1 = digitalRead(tor2Pin);
  if ((tor1 == LOW)&&(tor2 == LOW)) {
    return 0; //TOR OFFEN
  } else if ((tor1 == LOW)&&(tor2 == HIGH)) {
    return 1; //TOR 10-90%
  } else if ((tor1 == HIGH)&&(tor2 == HIGH)) {
    return 2; //TOR ZU
  } else {
    return 3; // ERROR
  }
}
*/
