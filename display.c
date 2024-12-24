
#define __ATMEGA328P__

#include "display.h"


void Display(int digit, int val, int pt)
{
    PORTB |= (1<<0) | (1<<4);
    PORTD |= (1<<0);
    PORTC |= (1<<2);

    PORTB &= ~(1<<5);
    PORTC &= ~(1<<3);
    PORTD &= 0b01000000;

    switch (val)
    {
    case 0:
        // a b c d e f
        PORTC |= (1<<3);
        PORTD |= (1<<7) | (1<<5) | (1<<4) | (1<<2);
        PORTB |= (1<<5);
        break;
    case 1:
        // b c
        PORTD |= (1<<7) | (1<<2);
        break;
    case 2:
        // a b g e d
        PORTD |= (1<<1) | (1<<4) | (1<<5) | (1<<7);
        PORTC |= (1<<3);
        break;
    case 3:
        // a b c d g
        PORTD |= (1<<1) | (1<<2) | (1<<4) | (1<<7);
        PORTC |= (1<<3);
        break;
    case 4:
        // f g c
        PORTD |= (1<<1) | (1<<2);
        PORTB |= (1<<5);
        break;
    case 5:
        // a f g c d
        PORTD |= (1<<1) | (1<<2) | (1<<4);
        PORTB |= (1<<5);
        PORTC |= (1<<3);
        break;
    case 6:
        // a f e d c g
        PORTD |= (1<<1) | (1<<2) | (1<<4) | (1<<5);
        PORTB |= (1<<5);
        PORTC |= (1<<3);
        break;
    case 7:
        //a b c
        PORTD |= (1<<2) | (1<<7);
        PORTC |= (1<<3);
        break;
    case 8:
        // a b c d e f g
        PORTD |= (1<<1) | (1<<2) | (1<<4) | (1<<5) | (1<<7);
        PORTB |= (1<<5);
        PORTC |= (1<<3);
        break;
    case 9:
        // a b c d f g
        PORTD |= (1<<1) | (1<<2) | (1<<4) | (1<<7);
        PORTB |= (1<<5);
        PORTC |= (1<<3);
        break;
    default:
        break;
    }

    switch (digit)
    {
    case 1:
        PORTC &= ~(1<<2);
        break;
    case 2:
        PORTB &= ~(1<<4);
        break;
    case 3:
        PORTB &= ~(1<<0);
        break;
    case 4:
        PORTD &= ~(1<<0);
        break;
    default:
        break;
    }
    if(pt == 1)
    {
        PORTD |= (1<<3);
    }

    _delay_ms(4);

}