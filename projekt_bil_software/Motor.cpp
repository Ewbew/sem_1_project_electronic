/*
 * Motor.cpp
 *
 * Created: 6/17/2024 12:23:36 PM
 *  Author: ottosejrskildsantess
 */ 
#include "Motor.h"


// TO-DO � change the variable type for speed from int to uint_8


// Every class object starts with having its member values set to the following initial values:
Motor::Motor():speed_(0), forward_direction_(true) {
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
	
	
	// TO-DO: initialize the output pin that controls the H-bridge (that controls the direction)
	
}

Motor::set_speed(int speed){
	
}
	
Motor::set_forward_direction()

/*
class Motor{
	private:
	int speed_;
	bool forward_direction_;
	// B�r motoren have previous_speed_, s� at den gradvist kan komme op p� nuv�rende speed?
	public:
	void set_speed(int speed);
	void set_forward_direction(bool forward_direction);
};

*/