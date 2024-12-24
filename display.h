#include <avr/io.h>
#include <util/delay.h>


#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

/*
    PD7:0 = A:DP (in alphabetical order)
    PB4, PB2:0 = DIG1:4
    pt = 1 => decimal point active

*/
void Display(int digit, int value, int decimal);  /* An example function declaration */

#endif