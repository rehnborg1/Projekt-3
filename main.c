/********************************************************************************
* main.c: Demonstration av datastruktur f�r implementering av AD-omvandling
*         f�r analoga signaler. I detta fall l�ses analog pin A0 / PORTC0
*         f�r PWM-styrning av fem lysdioder med en periodtid p� 10 000 us.
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
*       Lysdioderna lagras i en dynamisk vektor f�r kollektiv PWM-styrning.
*       Vid nedtryckning av tryckknapparna sker avl�sning av den analoga 
*       insignalen fr�n potentiometern och anv�nds f�r att kontrollera 
*       ljusstyrkan p� lysdiodenrna, �vrig tid h�lls de sl�ckta.
*       En PWM-period p� 10 000 us anv�nds.
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
