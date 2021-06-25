void serialEvent() {
  if (Serial.available() > 0) {
    digitalWrite(ledPin, LOW);
    KnxTpUartSerialEventType eType = knx.serialEvent();
    if (eType == KNX_TELEGRAM) {
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
          tor_status =  telegram->getBool();
        }
        if (target == "1/6/3") {
          nacht  = telegram->getBool();
        }
      }
    }
  } else {
    digitalWrite(ledPin, HIGH);
  }
}
