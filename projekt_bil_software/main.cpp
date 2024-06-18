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

// Start variable s�ttes til at v�re false til at starte med; skiftes til true i ISR for INT0, 
// som aktiveres ved et tryk p� en eksterne knap p� bilen
volatile bool start = false;

DrivingControl control;
SoundDriver sound(15);

void handle_interrupt() {
	control.increment_counter();
	sound.PlaySound(1);

	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at v�re sikker p�,
	//at der kun bliver talt op �n gang per reflekspar p� banen:
	EIMSK &= 0b11111100;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne v�rdi skal findes gennem tests. Pr�vede v�rdier: 150
	
	// For at v�re p� den sikre side, s� nulstiller vi interruptsflagene for INT1 & INT2, i tilf�lde af, at de var blevet sat.
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

