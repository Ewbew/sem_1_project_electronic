/*
 * DrivingControl.cpp
 *
 * Created: 6/14/2024 1:45:37 PM
 *  Author: ottosejrskildsantess
 */ 

#include "DrivingControl.h"


const int DrivingControl::SPEED_LEVELS[] = {100, 90, 65, 50, 90, 50, 50, 50, 80, 80, 50, 0};
const int DrivingControl::MAX_COUNTER = sizeof(SPEED_LEVELS) / sizeof(SPEED_LEVELS[0]);


DrivingControl::DrivingControl(): counter_(0) {}


// OBS: Disse v�rdier skal �ndres indtil at bilen k�rer igennem uden for mange fejl; de bestemmes gennem testk�rlser.
// OBS: Det kan v�re, at bilen bliver n�dt til at f� sat speed til 0, i stedet for bare at skifte retning.
int DrivingControl::get_speed() {
	if (counter_ >= 0 && counter_ < MAX_COUNTER) {
		return SPEED_LEVELS[counter_];
		} else {
		return -1;
	}
}

void DrivingControl::increment_counter(){
	counter_++;
}

int DrivingControl::get_counter(){
	return counter_;
}

bool DrivingControl::is_forward_direction() {
	return counter_ < 6 || counter_ >= 8;
}

bool DrivingControl::get_lights_state() {
	return counter_ < 6 || (counter_ >= 7 && counter_ < 11);
}

bool DrivingControl::get_brake_state(){
	int current_speed = get_speed();
	bool current_direction = is_forward_direction();
	// Hvis nuv�rende fart end lavere end tidligere fart, skal der returneres true;
	// Derudover, hvis der er skiftet retning siden sidste refleksbrik, m� bilen ogs� skulle bremse/standse
	bool should_brake = current_speed < previous_speed_ || current_direction != previous_direction_;

	previous_speed_ = current_speed;
	previous_direction_ = current_direction;

	return should_brake;
}