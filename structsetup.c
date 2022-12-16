#include "structsetup.h"

void setup(void)
{
	led_init(&l1, 6);
	led_init(&l2, 7);
	led_init(&l3, 8);
	led_init(&l4, 9);
	led_init(&l5, 10);

	button_init(&b1, 2);
	button_init(&b2, 3);
	button_init(&b3, 11);
	button_init(&b4, 12);
	button_init(&b5, 13);
	
	button_enable_interrupt(&b1);
	button_enable_interrupt(&b2);
	button_enable_interrupt(&b3);
	button_enable_interrupt(&b4);
	button_enable_interrupt(&b5);

	adc_init(&a1, A0);
	led_vector_init(&v1);

	led_vector_push(&v1, &l1);
	led_vector_push(&v1, &l2);
	led_vector_push(&v1, &l3);
	led_vector_push(&v1, &l4);
	led_vector_push(&v1, &l5);
	return;
}
