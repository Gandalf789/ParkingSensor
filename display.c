

#include "display.h"

//  PB5:4 & PB1:0 are the digit control
//  PORTD controls the 8 segments

void Display(int digit, int val, int pt)
{
    PORTB |= 0b00110011;
    PORTD &= 0b00000000;

    switch (val)
    {
    case 0:
        PORTD |= 0b11111100;
        break;
    case 1:
        PORTD |= 0b01100000;
        break;
    case 2:
        PORTD |= 0b11011010;
        break;
    case 3:
        PORTD |= 0b11110010;
        break;
    case 4:
        PORTD |= 0b00100110;
        break;
    case 5:
        PORTD |= 0b10110110;
        break;
    case 6:
        PORTD |= 0b10111110;
        break;
    case 7:
        PORTD |= 0b11100000;
        break;
    case 8:
        PORTD |= 0b11111110;
        break;
    case 9:
        PORTD |= 0b11110110;
        break;
    case 10:
        PORTD |= 0b00000001;
    default:
        break;
    }

    switch (digit)
    {
    case 1:
        PORTB &= ~(1<<0);
        break;
    case 2:
        PORTB &= ~(1<<1);
        break;
    case 3:
        PORTB &= ~(1<<4);
        break;
    case 4:
        PORTB &= ~(1<<5);
        break;
    default:
        break;
    }
    if(pt == 1)
    {
        PORTD |= (1<<0);
    }

    //_delay_ms(4);

}