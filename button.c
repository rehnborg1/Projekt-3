/********************************************************************************
* button.h: Inneh�ller funktionsdefinitioner f�r enkel implementering av
*           tryckknappar samt andra digitala inportar via strukten button.
********************************************************************************/
#include "button.h"

/********************************************************************************
* button_init: Initierar ny tryckknapp p� angiven pin.
*
*              - self: Pekare till tryckknappen som ska initieras.
*              - pin : Tryckknappens pin-nummer p� Arduino Uno, exempelvis 13.
*                      Alternativt kan motsvarande port-nummer p� ATmega328P
*                      anges, exempelvis B5 f�r pin 13 eller D3 f�r pin 3.
********************************************************************************/
void button_init(struct button* self,
const uint8_t pin)
{
	if (pin >= 0 && pin <= 7)
	{
		self->io_port = IO_PORTD;
		self->pin = pin;
		PORTD |= (1 << self->pin);
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->io_port = IO_PORTB;
		self->pin = pin - 8;
		PORTB |= (1 << self->pin);
	}
	else if (pin >= 14 && pin <= 19)
	{
		self->io_port = IO_PORTC;
		self->pin = pin - 14;
		PORTC |= (1 << self->pin);
	}
	else
	{
		self->io_port = IO_PORT_NONE;
		self->pin = 0;
	}

	self->interrupt_enabled = false;
	return;
}

/********************************************************************************
* button_clear: Nollst�ller tryckknapp samt motsvarande pin.
*
*               - self: Pekare till tryckknappen som ska nollst�llas.
********************************************************************************/
void button_clear(struct button* self)
{
	button_disable_interrupt(self);

	if (self->io_port == IO_PORTB)
	{
		PORTB &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PORTC &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PORTD &= ~(1 << self->pin);
	}

	self->io_port = IO_PORT_NONE;
	self->pin = 0;
	return;
}

/********************************************************************************
* button_is_pressed: L�ser av tryckknappens pin och indikerar ifall denna �r
*                    nedtryckt. I s� fall returneras true, annars false.
*
*                    - self: Pekare till tryckknappen som ska l�sas av.
********************************************************************************/
bool button_is_pressed(const struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		return (PINB & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTC)
	{
		return (PINC & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTD)
	{
		return (PIND & (1 << self->pin));
	}
	else
	{
		return false;
	}
}

/********************************************************************************
* button_enable_interrupt: Aktiverar PCI-avbrott p� angiven tryckknapp s� att
*                          event p� tryckknappens pin medf�r avbrott, b�de p�
*                          stigande och fallande flank. Kontroll av flank m�ste
*                          sk�tas av anv�ndaren, f�rslagsvis via avl�sning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan anv�nd I/O-port samt
*                          avbrottsvektorn f�r motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras p�.
********************************************************************************/
void button_enable_interrupt(struct button* self)
{
	asm("SEI");

	if (self->io_port == IO_PORTB)
	{
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << self->pin);
	}

	self->interrupt_enabled = true;
	return;
}

/********************************************************************************
* button_disable_interrupt: Inaktiverar PCI-avbrott p� angiven tryckknapp.
*
*                           - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska inaktiveras p�.
********************************************************************************/
void button_disable_interrupt(struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		PCMSK0 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCMSK1 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCMSK2 &= ~(1 << self->pin);
	}

	self->interrupt_enabled = false;
	return;
}

/********************************************************************************
* button_togglar_interrupt: Togglar aktivering av PCI-avbrott p� angiven
*                           tryckknapp. Om avbrott �r aktiverat vid anrop
*                           s� sker inaktivering. P� samma s�tt g�ller att om
*                           avbrott �r inaktiverat vid anrop s� sker aktivering.
*
*                           - self: Pekare till tryckknappen som aktivering av
*                                   PCI-avbrott ska inaktiveras p�.
********************************************************************************/
void button_toggle_interrupt(struct button* self)
{
	if (self->interrupt_enabled)
	{
		button_disable_interrupt(self);
	}
	else
	{
		button_enable_interrupt(self);
	}

	return;
}