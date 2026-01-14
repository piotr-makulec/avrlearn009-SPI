// Piotr Makulec, 2026
// Written for and tested on Arduino (ATmega328p).

#include <avr/io.h>
#include "spi.h"

/* SPI initialization */
void spiInit(void) {
  // set MOSI, CLK and CS as output
  DDRB |= (1 << MOSI) | (1 << SCK) | (1 << CS);
  // SPI enable, set as master, clock frequency = F_CPU / 64, low on idle, sample on leading edge
  SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1);
}

/* send one bite */
void spiSend(uint8_t oneByte) {
  SPDR = oneByte;
  // wait for the SPIF flag setting after the transmition is finished
  while(!(SPSR & (1 << SPIF)));
}

/* receive one bit */
uint8_t spiReceive(void) {
  // wait for the SPIF flag setting after the transmition is finished
  while(!(SPSR & (1 << SPIF)));
  return SPDR;
}
