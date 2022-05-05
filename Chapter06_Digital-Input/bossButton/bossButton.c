/*
bossButton.c

As long as we've got a button wired up to the AVR,
might as well have some fun.

Upload this code to your AVR, run bossButton.py.
Press button.

*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

static inline void blinkLED(void) {
  LED_PORT = (1 << LED0);
  _delay_ms(1000);
  LED_PORT &= ~(1 << LED0);
}


int main(void) {

  // -------- Inits --------- //
  BUTTON_PORT |= (1 << BUTTON);          /* input mode, turn on pullup */

  LED_DDR = (1 << LED0);
  blinkLED();

  //initUSART();
    UBRR0H = 103 >> 8;                        /* defined in setbaud.h */
    UBRR0L = 103 & 0xff;
  #if USE_2X
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif
                                    /* Enable USART transmitter/receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
  transmitByte('O');

  // ------ Event loop ------ //
  while (1) {

    if (bit_is_clear(BUTTON_PIN, BUTTON)) {
      transmitByte('X');
      blinkLED();
    }

  }                                                  /* End event loop */
  return 0;
}
