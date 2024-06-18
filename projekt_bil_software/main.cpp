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

// Start variable s�ttes til at v�re false til at starte med; skiftes til true i ISR for INT0, 
// som aktiveres ved et tryk p� en eksterne knap p� bilen
volatile bool start = false;

DrivingControl control;

// Interrupt rutine for start af bil:
ISR(INT0_vect){
	start = true;
	reti();
}


// TO-DO - brug en metode i driving control til at increment counter
// TO-DO � send afspilningslyd for hver gang en refleksbrik passeres � b�r kunne laves med en klassemetode, e.g. sound.play_sound()
ISR(INT1_vect){
	// Vi t�ller counter op med 1
	control.increment_counter();
	
	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at v�re sikker p�, 
	//at der kun bliver talt op �n gang per reflekspar p� banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne v�rdi skal findes gennem tests. Pr�vede v�rdier: 150
	
	// For at v�re p� den sikre side, s� nulstiller vi interruptsflagene for INT1 & INT2, i tilf�lde af, at de var blevet sat.
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
	
	// Vi t�ller counter op med 1
	control.increment_counter();
		
	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at v�re sikker p�,
	//at der kun bliver talt op �n gang per reflekspar p� banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne v�rdi skal findes gennem tests. Pr�vede v�rdier: 150
	// Til ovenst�ende kan det ogs� v�re n�dvendigt, at vi bruger en timer med en ISR, s� vi ikke bremser programudf�rslen.
		
	// For at v�re p� den sikre side, s� nulstiller vi interruptsflagene for INT1 & INT2, i tilf�lde af, at de var blevet sat.
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
	
	// Ops�tning af ISR'er; alle s�ttes til at aktivere korresponderende ISR ved rising edge
	EICRA = 0b00111111;
	
	// Vi enabler de tre interrupts
	EIMSK |= 0b00000111;
	
	// Enable global interrupt flag:
	sei();

	while (!start);
	{}
	
    // Her skal vi konstant k�re
    while (1) 
    {
		
		
    }
}

