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
#include "Lights.h"

#define DEBOUNCE_DELAY_MS 150

// Start variable s�ttes til at v�re false til at starte med; skiftes til true i ISR for INT0, 
// som aktiveres ved et tryk p� en eksterne knap p� bilen
volatile bool start = false;

DrivingControl control;
SoundDriver sound(15);
Motor motor;
Lights lights;

void handle_interrupt() {
	control.increment_counter();
	sound.PlaySound(control.get_counter() == 11 ? 2 : 3);
	motor.set_forward_direction(control.is_forward_direction());
	motor.set_speed(control.get_speed());
	lights.set_lights(control.get_lights_state());
	if(control.get_brake_state()) lights.activate_brake_state();
	// Vi dissabler de to ISR for refleksbrikkerne kortvarigt, for at v�re sikker p�,
	//at der kun bliver talt op �n gang per reflekspar p� banen:
	EIMSK &= 0b11111001;
	_delay_ms(DEBOUNCE_DELAY_MS); // OBS; denne v�rdi skal findes gennem tests. Pr�vede v�rdier: 150
	
	// For at v�re p� den sikre side, s� nulstiller vi interruptsflagene for INT1 & INT2, i tilf�lde af, at de var blevet sat.
	// Man nulstiller dem ved at skrive 1 til de tilsvarende bit pladser i flag registret:
	if(EIFR != 0){
		EIFR |= 0b00000110;
	}
	
	// Vi enabler de to interrupts for INT1 og INT2 igen
	EIMSK |= 0b00000110;
}


// Interrupt rutine for start af bil:
ISR(INT0_vect){
	start = true;
	sound.PlaySound(1);
	lights.set_lights(control.get_lights_state());
	motor.set_speed(control.get_speed());
}


ISR(INT1_vect){
	handle_interrupt();
}


ISR(INT2_vect){
	handle_interrupt();
}

int main(void)
{

	// Vi s�tter de relevante porte (forskellige outputs fra programmet, bl.a. PWM signal) til at v�re udgange:
	// Motor PWM (pin 11):
	DDRB = 0b00100000;

	// bool is_forward_direction (pin 37):
	DDRC = 0b00000001;
	
	// Interrupts input
	DDRD &= 0b11111000;
	
	// Making sure that the PORTD is not high
	PORTD = 0x00;

	// For- og bag LED
	DDRE = 0b00011000;
	
	// Ops�tning af ISR'er; alle s�ttes til at aktivere korresponderende ISR ved falling edge
	EICRA = 0b00101010;
		
	// Vi enabler de tre interrupts
	EIMSK |= 0b00000111;
	// Enable global interrupt flag:
	sei();

	while (!start);
	{}
		
	EIMSK &= 0b11111110;
	
    // Her skal vi konstant k�re
    while (1) 
    {
		
    }
}

