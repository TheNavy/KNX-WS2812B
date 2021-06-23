# KNX-WS2812B
KNX Controller for WS2812B LEDs

1. Logik der Eingänge

| Sensor 1 | Sensor 2 | KNX-Signal Tor | KNX-Signal Nacht | Beschreibung | Was tun? |
| :------: | :------: | :------------: | :--------------: | :----------- | :------- |
| 1 | 1 | 1 | 0 | Tor fährt AUF | Fahranimation für X Sekunden / Danach Licht TOR auf |
| 0 | 0 | 0 | 0 | Tor ist 100% AUF | Licht TOR auf |
| 0 | 1 | 0 | 0 | Tor ist "halb" AUF | Licht Aus |
| 0 | 1 | 0 | 1 | Tor ist "halb" AUF & Nacht | Licht Nacht |
| 1 | 1 | 0 | 1 | Tor ist ZU & Nacht | Licht Nacht |
| 1 | 1 | 1 | 0 | Tor ist ZU | Licht Aus |
| 0 | 0 | 1 | 0 | Tor fährt ZU | Fahranimation für X Sekunden / Danach Licht Aus |