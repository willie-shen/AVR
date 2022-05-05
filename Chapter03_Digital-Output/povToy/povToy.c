// POV toy demo framework //

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) {
  PORTB = oneByte;
  _delay_ms(2000);
}

int main(void) {
  // -------- Inits --------- //
  DDRB = 0x00111111;                    /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) {                                              /* mainloop */
    POVDisplay(0b00001110);
    POVDisplay(0b00011000);
    POVDisplay(0b00111101);//POVDisplay(0b10111101); 
    POVDisplay(0b00110110);//POVDisplay(0b01110110);
    POVDisplay(0b00111100);
    POVDisplay(0b00111100);
    POVDisplay(0b00111100);
    POVDisplay(0b00110110);//POVDisplay(0b01110110);
    POVDisplay(0b00111101);//POVDisplay(0b10111101);
    POVDisplay(0b00011000);
    POVDisplay(0b00001110);

    PORTB = 0;
    _delay_ms(1000);
  }                                                    /* end mainloop */
  return 0;
}
