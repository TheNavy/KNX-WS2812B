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
          // TODO XY
        }
      }
      if (target == "1/6/3") {
        int received_1_6_3 = telegram->getBool();
        if (received_1_6_3) {
          digitalWrite(ledPin, LOW);
        }
        else {
          // TODO XY
        }
      }
    }
  }
}
