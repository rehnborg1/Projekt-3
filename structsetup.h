#ifndef STRUCTSETUP_H_
#define STRUCTSETUP_H_

#include "misc.h"
#include "led.h"
#include "button.h"
#include "led_vector.h"
#include "adc.h"
#include "ISR_interrupts.h"

// implementering av structar för leds, knappar samt potentiometer

struct led l1, l2, l3, l4, l5;
struct button b1, b2, b3, b4, b5;
struct adc a1;
struct led_vector v1;


//setup: Initierar leds, knappar, knapptryck, potentiometer samt pushvektor

void setup(void);

#endif /* STRUCTSETUP_H_ */