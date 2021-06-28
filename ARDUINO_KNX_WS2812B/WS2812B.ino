/*
 * Der Funktion "strip_animation" könnten folgende Werte übergeben werden:
 * 0 = LEDs AUS
 * 1 = Animation RAUF / RUNTER
 * 2 = Animation TOR ZU
 * 3 = Animation TOR AUF
 */

// Hauptprogramm - Wählt Animation aus

/**
 * numCycles = Number of animation cycles. 0 = looping until reset.
 */
uint8_t strip_animation(uint8_t animation, struct Loop &loop) {
  uint8_t ret = 0x00;
  
  switch(animation) {
    case 0:
      strip0_loop0_reset(); 
      ret = 0x01;
      break;
    case 1:
	    ret = strip0_loop0_eff1(loop);
      strip_0.strip.show();
      break;
    case 2:
	    ret = strip0_loop0_eff2(loop);
      strip_0.strip.show();
      break;
    case 3:
	    ret = strip0_loop0_eff3(loop);
      strip_0.strip.show();
      break;
  }
  return ret;
}

uint8_t strip0_loop0_eff1(struct Loop &loop) {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 300
    // Steps: 155 - Delay: 1
    // Colors: 2 (255.0.0, 0.255.0)
    // Options: rainbowlen=300, toLeft=true, 
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<300;j++) {
    ind = strip_0.effStep + j * 0.5166666666666667;
    switch((int)((ind % 155) / 77.5)) {
      case 0: factor1 = 1.0 - ((float)(ind % 155 - 0 * 77.5) / 77.5);
              factor2 = (float)((int)(ind - 0) % 155) / 77.5;
              strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 155 - 1 * 77.5) / 77.5);
              factor2 = (float)((int)(ind - 77.5) % 155) / 77.5;
              strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
              break;
    }
  }
  
  if(strip_0.effStep >= 155) {
    if (loop.numberOfCycles > 0) {
      if (loop.currentCycle >= loop.numberOfCycles) {
        loop.currentCycle = 0;
        return 0x01;
      }
      else {
        loop.currentCycle++;
      }
    }
    else {
      strip_0.effStep = 0;
    }
  }
  else {
    strip_0.effStep++;
  }

  return 0x00;
}

uint8_t strip0_loop0_eff2(struct Loop &loop) {
    // Strip ID: 0 - Effect: Fade - LEDS: 300
    // Steps: 1000 - Delay: 1
    // Colors: 2 (255.0.0, 0.0.0)
    // Options: duration=1000, every=1, 
  uint8_t r,g,b;
  double e;
  e = (strip_0.effStep * 1) / (double)1000;
  r = ( e ) * 0 + 255 * ( 1.0 - e );
  g = ( e ) * 0 + 0 * ( 1.0 - e );
  b = ( e ) * 0 + 0 * ( 1.0 - e );
  for(uint16_t j=0;j<300;j++) {
    if((j % 1) == 0)
      strip_0.strip.setPixelColor(j, r, g, b);
    else
      strip_0.strip.setPixelColor(j, 0, 0, 0);
  }

  if(strip_0.effStep >= 1000) {
    if (loop.numberOfCycles > 0) {
      if (loop.currentCycle >= loop.numberOfCycles) {
        loop.currentCycle = 0;
        return 0x01;
      }
      else {
        loop.currentCycle++;
      }
    }
    else {
      strip_0.effStep = 0;
    }
  }
  else {
    strip_0.effStep++;
  }

  return 0x00;
}

uint8_t strip0_loop0_eff3(struct Loop &loop) {
    // Strip ID: 0 - Effect: Fade - LEDS: 300
    // Steps: 1000 - Delay: 1
    // Colors: 2 (0.255.0, 255.255.255)
    // Options: duration=1000, every=1, 
  uint8_t r,g,b;
  double e;
  e = (strip_0.effStep * 1) / (double)1000;
  r = ( e ) * 255 + 0 * ( 1.0 - e );
  g = ( e ) * 255 + 255 * ( 1.0 - e );
  b = ( e ) * 255 + 0 * ( 1.0 - e );
  for(uint16_t j=0;j<300;j++) {
    if((j % 1) == 0)
      strip_0.strip.setPixelColor(j, r, g, b);
    else
      strip_0.strip.setPixelColor(j, 0, 0, 0);
  }

  if(strip_0.effStep >= 1000) {
    if (loop.numberOfCycles > 0) {
      if (loop.currentCycle >= loop.numberOfCycles) {
        loop.currentCycle = 0;
        return 0x01;
      }
      else {
        loop.currentCycle++;
      }
    }
    else {
      strip_0.effStep = 0;
    }
  }
  else {
    strip_0.effStep++;
  }

  return 0x00;
}

void strip0_loop0_reset() {
	
  // Set black
	strip_0.strip.clear();

  // Reset strip values
  strip_0.Reset();
}
