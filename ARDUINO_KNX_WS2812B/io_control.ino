void pinStatus(){
  int tor1 = digitalRead(tor1Pin);
  int tor2 = digitalRead(tor2Pin);
  if ((tor1 == HIGH)&&(tor2 == LOW)) {
    tor = open; //TOR OFFEN
  } else if ((tor1 == LOW)&&(tor2 == LOW)) {
    tor = halfOpen; //TOR 10-90%
  } else if ((tor1 == LOW)&&(tor2 == HIGH)) {
    tor = close; //TOR ZU
  }
}
