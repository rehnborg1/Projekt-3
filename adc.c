/********************************************************************************
* adc.c: Inneh�ller funktionsdefinitioner f�r implementering av AD-omvandling
*        f�r analoga signaler via strukten adc.
********************************************************************************/
#include "adc.h"
#include "structsetup.h"

/********************************************************************************
* adc_init: Initierar analog pin f�r avl�sning och AD-omvandling av insignaler,
*           som antingen kan anges som ett tal mellan 0 - 5 eller via konstanter
*           A0 - A5 (som motsvarar heltal 14 - 19).
*
*           - self: Pekare till analog pin som skall anv�ndas f�r AD-omvandling.
*           - pin : Analog pin som skall l�sas f�r AD-omvandling.
********************************************************************************/
void adc_init(struct adc* self,
const uint8_t pin)
{
	if (pin >= 0 && pin <= 5)
	{
		self->pin = pin;
	}
	else if (pin >= 14 && pin <= 19)
	{
		self->pin = pin - 14;
	}

	self->pwm_on_us = 0;
	self->pwm_off_us = 0;

	(void)adc_read(self);
	return;
}

/********************************************************************************
* adc_read: L�ser av en analog insignal och returnerar motsvarande digitala
*           motsvarighet mellan 0 - 1023.
*
*           - self: Pekare till AD-omvandlaren som skall l�sas av.
********************************************************************************/
uint16_t adc_read(const struct adc* self)
{
	ADMUX = (1 << REFS0) | self->pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	return ADC;
}

/********************************************************************************
* adc_duty_cycle: L�ser av en analog insignal och returnerar motsvarande
*                 duty_cycle som ett flyttal mellan 0 - 1.
*
*                 - self: Pekare till AD-omvandlaren som skall l�sas av.
********************************************************************************/
double adc_duty_cycle(const struct adc* self)
{
	return adc_read(self) / ADC_MAX;
}

/********************************************************************************
* adc_get_pwm_values: L�ser av en analog insignal och ber�knar on- och off-tid
*                     f�r PWM-generering, avrundat till n�rmaste heltal.
*
*                     - self         : Pekare till AD-omvandlaren som skall
*                                      l�sas av.
*                     - pwm_period_us: PWM-perioden (on-tid + off-tid) m�tt i
*                                      mikrosekunder (default = 10 000 us).
********************************************************************************/
void adc_get_pwm_values(struct adc* self,
uint16_t pwm_period_us)
{
	if (!pwm_period_us) pwm_period_us = 10000;
	self->pwm_on_us = (uint16_t)(adc_duty_cycle(self) * pwm_period_us + 0.5);
	self->pwm_off_us = pwm_period_us - self->pwm_on_us;
	return;
}


/******************************************************************************** 
pwm_value_read: l�ser av och t�nder lysysdioderna om de �r aktiverade samt sl�cker 
				lysdioderna om de �r inaktiverade.
********************************************************************************/
void pwm_value_read (struct adc* self)
{

adc_get_pwm_values(&a1, 0);

if (led1_enabled)  led_on(&l1);
if (led2_enabled)  led_on(&l2);
if (led3_enabled)  led_on(&l3);
if (led4_enabled)  led_on(&l4);
if (led5_enabled)  led_on(&l5);

delay_us(a1.pwm_on_us);

led_off(&l1);
led_off(&l2);
led_off(&l3);
led_off(&l4);
led_off(&l5);

delay_us(a1.pwm_off_us);

return;
	
}