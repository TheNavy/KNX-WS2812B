/*
 * Der Funktion "strip_animation" könnten folgende Werte übergeben werden:
 * 0 = LEDs AUS
 * 1 = Animation RAUF / RUNTER
 * 2 = Animation TOR AUF
 * 3 = Animation TOR ZU
 */

// Hauptprogramm - Wählt Animation aus

/**
 * numCycles = Number of animation cycles. 0 = looping until reset.
 */
uint8_t strip_animation(uint8_t animation, struct Loop &loop) {
  uint8_t ret = 0;
  
  switch(animation) {
    case 0:
      strip0_loop0_reset(); 
      ret = 1;
      break;
    case 1:
      //ret = strip0_loop0_eff1();
	    ret = strip0_loop0_eff1(loop);
      strip_0.strip.show();
      break;
    case 2:
      //ret = strip0_loop0_eff2();
	    ret = strip0_loop0_eff2(loop);
      strip_0.strip.show();
      break;
    case 3:
      //ret = strip0_loop0_eff3();
	    ret = strip0_loop0_eff3(loop);
      strip_0.strip.show();
      break;
  }
  /*
  if (ret == 1) {
    ret = 0;
    return 1;    
  }
  */
}

uint8_t strip0_loop0_eff1(struct Loop &loop) {
    // Strip ID: 0 - Effect: Fade - LEDS: 120
    // Steps: 290 - Delay: 1
    // Colors: 2 (255.0.0, 0.0.0)
    // Options: duration=290, every=1, 
  // if(millis() - strip_0.effStart < 1 * (strip_0.effStep)) return 0x00;
  uint8_t r,g,b;
  double e;
  e = (strip_0.effStep * 1) / (double)290;
  r = ( e ) * 0 + 255 * ( 1.0 - e );
  g = ( e ) * 0 + 0 * ( 1.0 - e );
  b = ( e ) * 0 + 0 * ( 1.0 - e );
  for(uint16_t j=0;j<120;j++) {
    if((j % 1) == 0)
      strip_0.strip.setPixelColor(j, r, g, b);
    else
      strip_0.strip.setPixelColor(j, 0, 0, 0);
  }
  
  if(strip_0.effStep >= 290) {
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
    // Strip ID: 0 - Effect: Fade - LEDS: 120
    // Steps: 240 - Delay: 1
    // Colors: 2 (0.255.0, 255.255.255)
    // Options: duration=240, every=1, 
  // if(millis() - strip_0.effStart < 1 * (strip_0.effStep)) return 0x00;
  uint8_t r,g,b;
  double e;
  e = (strip_0.effStep * 1) / (double)240;
  r = ( e ) * 255 + 0 * ( 1.0 - e );
  g = ( e ) * 255 + 255 * ( 1.0 - e );
  b = ( e ) * 255 + 0 * ( 1.0 - e );
  for(uint16_t j=0;j<120;j++) {
    if((j % 1) == 0)
      strip_0.strip.setPixelColor(j, r, g, b);
    else
      strip_0.strip.setPixelColor(j, 0, 0, 0);
  }

  if(strip_0.effStep >= 240) {
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
    // Strip ID: 0 - Effect: Rainbow - LEDS: 120
    // Steps: 170 - Delay: 20
    // Colors: 2 (255.0.0, 0.255.0)
    // Options: rainbowlen=120, toLeft=true, 
  // if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<120;j++) {
    ind = strip_0.effStep + j * 1.4166666666666667;
    switch((int)((ind % 170) / 85)) {
      case 0: factor1 = 1.0 - ((float)(ind % 170 - 0 * 85) / 85);
              factor2 = (float)((int)(ind - 0) % 170) / 85;
              strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 170 - 1 * 85) / 85);
              factor2 = (float)((int)(ind - 85) % 170) / 85;
              strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 0 * factor2);
              break;
    }
  }

  if(strip_0.effStep >= 170) {
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
	
  // Set black - necessary?
	strip_0.strip.clear();

  // Reset strip values
  strip_0.Reset();

	// Keine ahnung ob das benötigt wird
	/*
	uint32_t black = strip_0.strip.Color(0, 0, 0);
    strip_0.strip.fill(black, 0, 120);
    strip_0.strip.show();    
	*/
}