/*
 * Motor.cpp
 *
 * Created: 6/17/2024 12:23:36 PM
 *  Author: ottosejrskildsantess
 */ 
#include "Motor.h"
#include <avr/io.h>


// TO-DO – change the variable type for speed from int to uint_8


// Every class object starts with having its member values set to the following initial values:
Motor::Motor():speed_(0), forward_direction_(true) {
	
// SPEED //
	// Motor PWM signalet bliver genereret af Timer 1:
	// Bit 7 & 6: Setting when upcounting, clearing when down counting (compare match); output pin is OC1A (PB, ben 5)
	// Bit 1 & 0: PWM, Phase correct, 10-bit (TOP = 1024)
	TCCR1A = 0b11000011;
	// Bit 2, 1 & 0: Prescaler = 8
	TCCR1B = 0b00000010;
	// With the above settings, the frequency will be ~977.5 Hz
	// I think we should aim for a PWM frequency of about 1 kHz, since this seemed like an okay value for the motor. 
	// Otherwise, we will have to test out which frequency works the best
	
	
	// When setting OCR1A to be equal TOP (2^10), then duty cycle is:
	// Duty cycle = 1 - (OCRn/TOP) = 0 (1 - 1 = 0)
	OCR1A = 1024-((1024/100)*speed_);	
	
// DIRECTION //
	// Setting PINC0 to be output, to control the motor direction (pin #37, marked on the Mega Shield 2560)
	DDRC = 0x01;
	
	// Setting the bit to be 1 (forward_direction = true), meaning that the output from PC0 will be 5 V:
	PORTC |= forward_direction_;
}

void Motor::set_speed(int speed){
	OCR1A = 1024 - ((1024/100)*speed);
}
	
void Motor::set_forward_direction(bool forward_direction){
	if(forward_direction){ // LSB is being set (the output pin)
		PORTC |= forward_direction_;
	} else { // This just keep all of the other bits in PORTC the same, while the LSB is being cleared (the output pin)
		PORTC &= ~(!forward_direction_ << 0 );
	}
}