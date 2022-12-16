/********************************************************************************
* main.c: Demonstration av datastruktur för implementering av AD-omvandling
*         för analoga signaler. I detta fall läses analog pin A0 / PORTC0
*         för PWM-styrning av fem lysdioder med en periodtid på 10 000 us.
********************************************************************************/
#include "led.h"
#include "button.h"
#include "led_vector.h"
#include "adc.h"
#include "ISR_interrupts.h"
#include "structsetup.h"

/********************************************************************************
* main: Ansluter fem lysdioder till pin 6 - 10, fem tryckknappar till pin 2-3 och 
*       11-13 samt en potentiometer till analog pin A0.
*       Lysdioderna lagras i en dynamisk vektor för kollektiv PWM-styrning.
*       Vid nedtryckning av tryckknapparna sker avläsning av den analoga 
*       insignalen från potentiometern och används för att kontrollera 
*       ljusstyrkan på lysdiodenrna, övrig tid hålls de släckta.
*       En PWM-period på 10 000 us används.
********************************************************************************/
int main(void)
{
	setup();
	
	while (1)
	{
		pwm_value_read(&a1);
	}

	return 0;
}
