// Slow-scope.  A free-running AVR / ADC "oscilloscope"

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

#define SAMPLE_DELAY  20 /* ms, controls the scroll-speed of the scope */

// -------- Functions --------- //
static inline void initFreerunningADC(void) {
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    /* ADC clock prescaler /8 */

  ADMUX |= (1 << ADLAR);     /* left-adjust result, return only 8 bits */

  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
  ADCSRA |= (1 << ADATE);                       /* auto-trigger enable */
  ADCSRA |= (1 << ADSC);                     /* start first conversion */
}

int main(void) {
  // -------- Inits --------- //
  //initUSART();
    UBRR0H = 51 >> 8;                        /* defined in setbaud.h */
    UBRR0L = 51 & 0xff;
  #if USE_2X
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif
                                    /* Enable USART transmitter/receiver */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
    //04302022 Willie Shen: Copied over from Serial Organ
  initFreerunningADC();
  // ------ Event loop ------ //
  while (1) {
    transmitByte(ADCH);       /* transmit the high byte, left-adjusted */
    _delay_ms(SAMPLE_DELAY);
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
