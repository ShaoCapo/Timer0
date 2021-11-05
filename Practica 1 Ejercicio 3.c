#include <xc.h>

#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, DEBUG = OFF, FOSC = HS
#pragma config FCMEN = OFF, MCLRE = ON, WDTE = OFF, CP = OFF, LVP = OFF
#pragma config PWRTE = ON, BOR4V = BOR21V, WRT = OFF

#pragma intrinsic(_delay)
#define _XTAL_FREQ 20000000 // necessary for __delay_us

/*	frecuencia / 4 = 5 Mhz = 5 * 10^6 Hz
	5 * 10^6 / 256 = 19531.25  pulsos
	19531.25 -----     1 sg
	   x     ----- 0.005 sg
	x = 97.65 +- 98
	256 - 98 = 158
	Para que pase 1 sg tiene que contar 200 veces
	con el timer calculado
*/

char x;

void init_T0(){
	OPTION_REGbits.T0CS = 0;
	OPTION_REGbits.PSA = 0;
	OPTION_REGbits.PS = 0b111;
	INTCONbits.TOIE = 1;
	if (y == 200){
		TMR0 = 158;
	}
}

main (){

	TRISB = 1;
	int y = 0;
	init_T0 ();
	y++;
	INTCONbits.GIE = 1;
	while(1);
}




