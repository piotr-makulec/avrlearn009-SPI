// Piotr Makulec, 2026
// Hardware SPI usage, controlling the LEDs with 74HC595 shift register
// Written for and tested on Arduino (ATmega328p).

#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

// chip select - conneted to the Latch Clock pin
#define CS PB2
// master out slave in - connected to the Data Input pin
#define MOSI PB3
// clock - connected to the Shift Clock pin
#define SCK PB5

// position of the LED currently ON
uint8_t cnt; 

void spiSendToReg(uint8_t oneByte);

int main(void) {
  spiInit();
  // send a software RESET to the register
  spiSendToReg(0);
  while (1) {
    cnt = 1;
    while (cnt) {
      spiSendToReg(cnt);
      _delay_ms(100);
      cnt <<= 1;
    }
    cnt = 0x80;
    while(cnt) {
      spiSendToReg(cnt);
      _delay_ms(100);
      cnt >>= 1;
    }
  }
}

/* send one byte - modified to be used with 74HC595 register */
void spiSendToReg(uint8_t oneByte) {
 SPDR = oneByte;
  // wait for the SPIF flag setting after the transmition is finished
  while(!(SPSR & (1 << SPIF)));
  // code below is specific to the 74HC595
  // rising edge on the Latch Clock pin causes the data in the register to be written to the Qa-Qh pins
  PORTB |= (1 << CS);
  // set the Latch Clock back LOW
  PORTB &= ~(1 << CS);
}
