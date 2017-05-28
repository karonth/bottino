# Bottino
Bottino è un bot telegram, sviluppato in arduino e basato su una matrice a led.
Le dimensioni compatte e la connettività wifi permettono di integrarlo in oggetti IOT per dare una dimensione fisica all'interazione virtuale.

Lo trovate su telegram come @Bottino_bot  

Per compilare sulla scheda Wemos D1 mini (driver usb https://wiki.wemos.cc/downloads) avrete bisogno del core esp8266 per Arduino: https://github.com/esp8266/Arduino
La veresione usata è la 2.2.0, le istruzioni per l'installazione le trovate nel repository sopra.


Il collegamento a Telegram è gestito da https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot e https://github.com/bblanchon/ArduinoJson ; installatele dal gestore delle librerie interno dell'ide Arduino

La libreria LedControl https://github.com/wayoda/LedControl/ gestisce la matrice a led; serve per la compilazione. 
Una piccola nota: certe versioni della librerie LedControl possono dare un errore sull'include di avr\pgmspace.h

in questo caso basta modificare il file LedControl.h sostituendo:

```c
#include <avr\pgmspace.h>
```

con

```c
#if (defined(AVR))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif
```

Dovrete creare un nuovo bot parlando col BotFather di telegram e usare il token nel programma. 

Al momento il bot supporta tre emoticon, ma potrete aggiungerne a piacimento.

Per disegnare altre faccine potete usare http://xantorohara.github.io/led-matrix-editor
