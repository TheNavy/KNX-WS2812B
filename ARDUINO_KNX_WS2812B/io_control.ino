int pinStatus(){
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
