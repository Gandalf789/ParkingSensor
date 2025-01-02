#define __AVR_ATmega328P__

#include "timers.h"

#define F_CPU 16000000UL

void init_timer0()
{
  // exemplu de configurare pentru Timer 1 în mod CTC
  // care va genera întreruperi cu frecvența de 2Hz

  // resseting the control registers for good measure
  TCCR0A = 0;
  TCCR0B = 0;

  //reset the counter too
  TCNT0 = 0;


  OCR0A = 250;            // compare match register 16MHz/256/2Hz-1
  TCCR0A = (1 << WGM01);   // CTC mode
  TCCR0B = (1 << CS01) | (1<<CS00);    // prescaler 64
}

void init_PWM2A()
{
  
  TCCR2A = 0;
  TCCR2B = 0;

  TCNT2 = 0;

  OCR2A = 125;

  TCCR2A |= (1<<WGM21) | (1<<WGM20); // Fast PWM mode,

  TCCR2A |= (1<<COM2A1); // sets non-inverting mode


  TCCR2B |=  (1<<CS21) | (1<<CS22); // sets prescaler to 1024

}


void init_timer1()
{
   TCNT1 = 0;
   OCR1A = 250;
   TCCR1B |= (1<<WGM12); // CTC mode
   TCCR1B |= (1<<CS11) | (1<<CS10); // PRESCALER TO 64
   TIMSK1 |= (1<<OCIE1A); 
}
