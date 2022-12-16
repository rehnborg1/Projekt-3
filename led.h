/********************************************************************************
* led.h: Inneh�ller funktionalitet f�r enkel implementering av lysdioder via
*        strukten led samt associerade funktioner. Denna strukt fungerar ocks�
*        utm�rkt f�r andra digitala utportar.
********************************************************************************/
#ifndef LED_H_
#define LED_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/********************************************************************************
* led: Strukt f�r implementering av lysdioder och andra digitala utportar.
********************************************************************************/
struct led
{
	uint8_t pin;          /* Lysdiodens pin-nummer p� aktuell I/O-port. */
	enum io_port io_port; /* I/O-port som lysdioden �r ansluten till. */
	bool enabled;         /* Indikerar ifall lysdioden �r t�nd. */
};

/********************************************************************************
* led_init: Initierar ny lysdiod p� angiven pin.
*
*           - self: Pekare till lysdioden som ska initieras.
*           - pin : Lysdiodens pin-nummer p� Arduino Uno, exempelvis 8.
*                   Alternativt kan motsvarande port-nummer p� ATmega328P
*                   anges, exempelvis B0 f�r pin 8 eller D2 f�r pin 2.
********************************************************************************/
void led_init(struct led* self,
const uint8_t pin);

/********************************************************************************
* led_clear: Nollst�ller lysdiod samt motsvarande pin.
*
*            - self: Pekare till lysdioden som ska nollst�llas.
********************************************************************************/
void led_clear(struct led* self);

/********************************************************************************
* led_on: T�nder angiven lysdiod.
*
*         - self: Pekare till lysdioden som ska t�ndas.
********************************************************************************/
void led_on(struct led* self);

/********************************************************************************
* led_off: Sl�cker angiven lysdiod.
*
*          - self: Pekare till lysdioden som ska sl�ckas.
********************************************************************************/
void led_off(struct led* self);

/********************************************************************************
* led_toggle: Togglar utsignalen p� angiven lysdiod. Om lysdioden �r sl�ckt vid
*             anropet s� t�nds den. P� samma s�tt g�ller att om lysdioden �r
*             t�nd vid anropet s� sl�cks den.
*
*             - self: Pekare till lysdioden vars utsignal ska togglas.
********************************************************************************/
void led_toggle(struct led* self);

/********************************************************************************
* led_blink: Blinkar lysdiod en g�ng med angiven blinkhastighet.
*
*            - self          : Pekare till lysdioden som ska blinkas.
*            - blink_speed_ms: Blinkhastigheten m�tt i millisekunder.
********************************************************************************/
void led_blink(struct led* self,
			   const uint16_t blink_speed_ms);

#endif /* LED_H_ */