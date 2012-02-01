#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t value;
volatile uint8_t upPressed = 0;
volatile uint8_t downPressed = 0;

int main () {
	
  // Set Pin 6 (PD2) as the pin to use for this example
  PCMSK |= (1<<PIND2);

  // interrupt on INT0 pin falling edge (sensor triggered) 
  MCUCR = (1<<ISC01) | (1<<ISC00) | (1<<ISC11) | (1<<ISC10);

  // turn on interrupts!
  GIMSK  |= (1<<INT0) | (1<<INT1);

  sei();

  DDRB = 0xff;

  value = 0;

  while (1) {
  	if (upPressed)
		value ++;
  	if (downPressed)
		value ++;
	

	PORTB = ~value;
  }

  //DDRB |= (1<<PB3); // Port OC1A mit angeschlossener LED als Ausgang
  //TCCR1A = (1<<WGM10) | (1<<COM1A1); // PWM, phase correct, 8 bit.
  //TCCR1B = (1<<CS10); // Prescaler 1 = Enable counter
  //OCR1A = value; // Duty cycle 50% (Anm. ob 128 oder 127 bitte prüfen)
}

SIGNAL (SIG_INT0)
{ 
	upPressed = !upPressed;
	
    // Do some stuff
}

SIGNAL (SIG_INT1)
{ 
	downPressed = !downPressed;

    // Do some stuff
}


