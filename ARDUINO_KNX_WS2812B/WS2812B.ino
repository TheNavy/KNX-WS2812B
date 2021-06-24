/*
 * Der Funktion "strip_animation" könnten folgende Werte übergeben werden:
 * 0 = LEDs AUS
 * 1 = Animation RAUF / RUNTER
 * 2 = Animation TOR AUF
 * 3 = Animation TOR ZU
 */

void strip_animation(int animation) {
  if (animation == 0) {
    // TUE XY
    if(strip0_loop0() & 0x01)
    strip_0.strip.show();
  } else if (animation == 1) {
    // TUE YX
  } else if (animation == 2) {
    // TUE XX
  } else if (animation == 3) {
    // TUE YY
  }
}

uint8_t strip0_loop0() {
  uint8_t ret = 0x00;
  switch(strip0loop0.currentChild) {
    case 0: 
           ret = strip0_loop0_eff0();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
      strip0loop0.currentChild = 0;
      if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop0_eff0() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 120
    // Steps: 120 - Delay: 20
    // Colors: 2 (255.0.0, 0.255.0)
    // Options: rainbowlen=120, toLeft=true, 
  if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<120;j++) {
    ind = strip_0.effStep + j * 1;
    switch((int)((ind % 120) / 60)) {
      case 0: factor1 = 1.0 - ((float)(ind % 120 - 0 * 60) / 60);
              factor2 = (float)((int)(ind - 0) % 120) / 60;
              strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 120 - 1 * 60) / 60);
              factor2 = (float)((int)(ind - 60) % 120) / 60;
              strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
              break;
    }
  }
  if(strip_0.effStep >= 120) {strip_0.Reset(); return 0x03; }
  else strip_0.effStep++;
  return 0x01;
}
