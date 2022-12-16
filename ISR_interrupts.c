#include "ISR_interrupts.h"
#include "misc.h"
#include "structsetup.h"


// lysdioderna är släckta vid start
volatile bool led1_enabled = false,
led2_enabled = false,
led3_enabled = false,
led4_enabled = false,
led5_enabled = false;


// avbrottsrutiner för tryckknapp 1 och 2
ISR (PCINT2_vect)
{
	if (button_is_pressed(&b1))
	{
		led1_enabled = !led1_enabled;
	}
	else if (button_is_pressed(&b2))
	{
		led2_enabled = !led2_enabled;
	}

	return;
}

// avbrottsrutiner för tryckknapp 3, 4 och 5
ISR (PCINT0_vect)
{
	if (button_is_pressed(&b3))
	{
		led3_enabled = !led3_enabled;
	}
	else if (button_is_pressed(&b4))
	{
		led4_enabled = !led4_enabled;
	}
	else if (button_is_pressed(&b5))
	{
		led5_enabled = !led5_enabled;
	}
	return;
}