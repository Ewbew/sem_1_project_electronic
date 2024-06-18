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
#include "Motor.h"

#define DEBOUNCE_DELAY_MS 150

// Start variable sættes til at være false til at starte med; skiftes til true i ISR for INT0, 
// som aktiveres ved et tryk på en eksterne knap på bilen
volatile bool start = false;

DrivingControl control;

// Interrupt rutine for start af bil:
ISR(INT0_vect){
	start = true;
	reti();
}


// TO-DO - brug en metode i driving control til at increment counter
// TO-DO – send afspilningslyd for hver gang en refleksbrik passeres – bør kunne laves med en klassemetode, e.g. sound.play_sound()
ISR(INT1_vect){
	// Vi tæller counter op med 1
	control.increment_counter();
	
	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at være sikker på, 
	//at der kun bliver talt op én gang per reflekspar på banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne værdi skal findes gennem tests. Prøvede værdier: 150
	
	// For at være på den sikre side, så nulstiller vi interruptsflagene for INT1 & INT2, i tilfælde af, at de var blevet sat.
	// Man nulstiller dem ved at skrive 1 til de tilsvarende bit pladser i flag registret:
	if(EIFR!=0){
		EIFR |= 0b00000011;
	}
	
	// Vi enabler de to interrupts for INT1 og INT2 igen
	EIMSK |= 0b00000011;	
	reti();
}


// TO-DO - brug en metode i driving control til at increment counter
ISR(INT2_vect){
	//(Kopi af ISR for INT1)
	
	// Vi tæller counter op med 1
	control.increment_counter();
		
	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at være sikker på,
	//at der kun bliver talt op én gang per reflekspar på banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne værdi skal findes gennem tests. Prøvede værdier: 150
	// Til ovenstående kan det også være nødvendigt, at vi bruger en timer med en ISR, så vi ikke bremser programudførslen.
		
	// For at være på den sikre side, så nulstiller vi interruptsflagene for INT1 & INT2, i tilfælde af, at de var blevet sat.
	// Man nulstiller dem ved at skrive 1 til de tilsvarende bit pladser i flag registret:
	if(EIFR!=0){
		EIFR |= 0b00000011;
	}
		
	// Vi enabler de to interrupts for INT1 og INT2 igen
	EIMSK |= 0b00000011;
	reti();
}

int main(void)
{
	
	control = DrivingControl();
	
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

