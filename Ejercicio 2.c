// See /opt/microchip/xc8/v1.10/docs/chips/16f886.html
// for details on #pragma config

#include <xc.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF

#pragma intrinsic(_delay)
#define _XTAL_FREQ 20000000 // necessary for __delay_us

/*
	frecuencia / 4 = 5 Mhz = 5 * 10^6 Hz
	5 * 10^6 / 256 = 19531.25  pulsos
	19531.25 -----     1 sg
	   x     ----- 0.005 sg
	x = 97.65 +- 98
	256 - 98 = 158
*/

char x;
void init_T0()
{
    // OPTION_REGbits = 0b00000111 igual que lo de abajo.
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    INTCONbits.T0IE = 1;
    TMR0 = 158;
}

void __interrupt() INT_T0(void)
{
    TMR0 = 158;
    x++;
    PORTB = x;
    INTCONbits.T0IF = 0;
}

void main(void) {
    init_T0();
    TRISB = 0;
    INTCONbits.GIE = 1;
    while (1);
}
