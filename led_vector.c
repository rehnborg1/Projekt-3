/********************************************************************************
* led_vector.c: Innehåller funktionsdefinitioner för implementering av dynamiska
*               vektorer för lagring och styrning över multipla lysdioder eller
*               andra utportar via strukten led_vector.
********************************************************************************/
#include "led_vector.h"

/********************************************************************************
* led_vector_init: Initierar angiven vektor till tom vid start.
*
*                  - self: Pekare till vektorn som ska initieras.
********************************************************************************/
void led_vector_init(struct led_vector* self)
{
	self->leds = 0;
	self->size = 0;
	return;
}

/********************************************************************************
* led_vector_clear: Tömmer och nollställer angiven vektor.
*
*                   - self: Pekare till vektorn som ska tömmas.
********************************************************************************/
void led_vector_clear(struct led_vector* self)
{
	free(self->leds);
	self->leds = 0;
	self->size = 0;
	return;
}

/********************************************************************************
* led_vector_begin: Returnerar en pekare till det första elementet i angiven
*                   vektor. Ifall vektorn är tom returneras null.
*
*                  - self: Pekare till vektorn.
********************************************************************************/
struct led* led_vector_begin(const struct led_vector* self)
{
	return self->leds;
}

/********************************************************************************
* led_vector_end: Returnerar en pekare till adressen direkt efter det sista
*                 befintliga elementet i angiven vektor. Ifall vektorn är tom
*                 returneras null.
*
*                  - self: Pekare till vektorn.
********************************************************************************/
struct led* led_vector_end(const struct led_vector* self)
{
	return self->leds + self->size;
}

/********************************************************************************
* led_vector_last: Returnerar en pekare till det sista befintliga elementet i
*                  angiven vektor. Ifall vektorn är tom returneras null.
*
*                  - self: Pekare till vektorn.
********************************************************************************/
struct led* led_vector_last(const struct led_vector* self)
{
	return self->size > 0 ? led_vector_end(self) - 1 : 0;
}

/********************************************************************************
* led_vector_resize: Ändrar storleken på angiven vektor så att den efter
*                    omallokering rymmer angivet antal led-objekt, som kan
*                    tilldelas direkt via index i stället för en push-operation.
*                    Vid misslyckad minnesallokering returneras felkod 1.
*                    Annars om omallokeringen lyckas så returneras 0.
*
*                  - self    : Pekare till vektorn vars storlek ska ändras.
*                  - new_size: Vektorns nya storlek.
********************************************************************************/
int led_vector_resize(struct led_vector* self,
const size_t new_size)
{
	if (new_size == 0)
	{
		led_vector_clear(self);
		return 0;
	}
	else
	{
		struct led* copy = (struct led*)realloc(self->leds, sizeof(struct led) * new_size);
		if (!copy) return 1;
		self->leds = copy;
		self->size = new_size;
		return 0;
	}
}

/********************************************************************************
* led_vector_push: Lägger till ett nytt led-objekt längst bak i angiven vektor.
*                  Vid misslyckad minnesallokering returneras felkod 1.
*                  Annars om push-operationen lyckas returneras 0.
*
*                  - self   : Pekare till vektorn som ska tilldelas.
*                  - new_led: Det nya led-objekt som ska läggas till.
********************************************************************************/
int led_vector_push(struct led_vector* self,
const struct led* new_led)
{
	struct led* copy = (struct led*)realloc(self->leds, sizeof(struct led) * (self->size + 1));
	if (!copy) return 1;
	copy[self->size++] = *new_led;
	self->leds = copy;
	return 0;
}

/********************************************************************************
* led_vector_pop: Tar bort eventuellt sista led-objekt i angiven vektor genom
*                 att minska dess storlek med ett. Vid misslyckad omallokering
*                 returneras felkod 1, annars 0.
*
*                 - self: Pekare till vektorn vars sista element ska tas bort.
********************************************************************************/
int led_vector_pop(struct led_vector* self)
{
	if (self->size <= 1)
	{
		led_vector_clear(self);
		return 0;
	}
	else
	{
		struct led* copy = (struct led*)realloc(self->leds, sizeof(struct led) * (self->size - 1));
		if (!copy) return 1;
		self->leds = copy;
		self->size--;
		return 0;
	}
}

/********************************************************************************
* led_vector_on: Tänder samtliga lysdioder lagrade i angiven vektor.
*
*                - self: Pekare till vektorn vars lysdioder ska tändas.
********************************************************************************/
void led_vector_on(struct led_vector* self)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_on(i);
	}
	return;
}


/********************************************************************************
* led_vector_off: Släcker samtliga lysdioder lagrade i angiven vektor.
*
*                 - self: Pekare till vektorn vars lysdioder ska släckas.
********************************************************************************/
void led_vector_off(struct led_vector* self)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_off(i);
	}
	return;
}

/********************************************************************************
* led_vector_toggle: Togglar samtliga lysdioder lagrade i angiven vektor.
*
*                    - self: Pekare till vektorn vars lysdioder ska togglas.
********************************************************************************/
void led_vector_toggle(struct led_vector* self)
{
	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_toggle(i);
	}
	return;
}

/********************************************************************************
* led_vector_blink_collectively: Genomför kollektiv (synkroniserad) blinkning
*                                av samtliga lysdioder lagrade i angiven vektor.
*
*                                - self          : Pekare till vektorn vars
*                                                  lysdioder ska blinkas.
*                                - blink_speed_ms: Lysdiodernas blinkhastighet
*                                                  mätt i millisekunder.
********************************************************************************/
void led_vector_blink_colletively(struct led_vector* self,
const uint16_t blink_speed_ms)
{
	led_vector_on(self);
	delay_ms(blink_speed_ms);
	led_vector_off(self);
	delay_ms(blink_speed_ms);
	return;
}

/********************************************************************************
* led_vector_blink_sequentially: Genomför sekventiell blinkning av samtliga
*                                lysdioder lagrade i angiven vektor. Därmed
*                                blinkar lysdioderna i en sekvens en efter en.
*
*                                - self          : Pekare till vektorn vars
*                                                  lysdioder ska blinkas.
*                                - blink_speed_ms: Lysdiodernas blinkhastighet
*                                                  mätt i millisekunder.
********************************************************************************/
void led_vector_blink_sequentially(struct led_vector* self,
const uint16_t blink_speed_ms)
{
	led_vector_off(self);

	for (struct led* i = self->leds; i < self->leds + self->size; ++i)
	{
		led_on(i);
		delay_ms(blink_speed_ms);
		led_off(i);
	}

	return;
}