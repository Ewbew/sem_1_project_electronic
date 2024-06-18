/*
 * projekt_bil_software.cpp
 *
 * Created: 6/14/2024 11:33:03 AM
 * Author : ottosejrskildsantess
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "DrivingControl.h"
#include "SoundDriver.h"
#include "Motor.h"

#define DEBOUNCE_DELAY_MS 150

// Start variable sættes til at være false til at starte med; skiftes til true i ISR for INT0, 
// som aktiveres ved et tryk på en eksterne knap på bilen
volatile bool start = false;

DrivingControl control;
SoundDriver sound(15);

void handle_interrupt() {
	control.increment_counter();
	sound.PlaySound(1);

	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at være sikker på,
	//at der kun bliver talt op én gang per reflekspar på banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne værdi skal findes gennem tests. Prøvede værdier: 150
	
	// For at være på den sikre side, så nulstiller vi interruptsflagene for INT1 & INT2, i tilfælde af, at de var blevet sat.
	// Man nulstiller dem ved at skrive 1 til de tilsvarende bit pladser i flag registret:
	if(EIFR != 0){
		EIFR |= 0b00000011;
	}
	
	// Vi enabler de to interrupts for INT1 og INT2 igen
	EIMSK |= 0b00000011;
}


// Interrupt rutine for start af bil:
ISR(INT0_vect){
	start = true;
	reti();
}


ISR(INT1_vect){
	handle_interrupt();
	reti();
}


ISR(INT2_vect){
	handle_interrupt();
	reti();
}

int main(void)
{
	
	// Opsætning af ISR'er; alle sættes til at aktivere korresponderende ISR ved rising edge
	EICRA = 0b00111111;
	
	// Vi enabler de tre interrupts
	EIMSK |= 0b00000111;
	
	// Enable global interrupt flag:
	sei();

	while (!start);
	{}
	
    // Her skal vi konstant køre
    while (1) 
    {
		
    }
}

