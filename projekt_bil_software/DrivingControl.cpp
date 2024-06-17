/*
 * DrivingControl.cpp
 *
 * Created: 6/14/2024 1:45:37 PM
 *  Author: ottosejrskildsantess
 */ 

#include "DrivingControl.h"

const uint8_t SPEED_LEVELS[] = {100, 90, 65, 50, 90, 50, 50, 50, 80, 80, 50, 0};
const uint8_t MAX_COUNTER = sizeof(SPEED_LEVELS) / sizeof(SPEED_LEVELS[0]);

DrivingControl::DrivingControl(int* counter_pointer):counter_pointer_(counter_pointer){}


// OBS: Disse v�rdier skal �ndres indtil at bilen k�rer igennem uden for mange fejl; de bestemmes gennem testk�rlser.
// OBS: Det kan v�re, at bilen bliver n�dt til at f� sat speed til 0, i stedet for bare at skifte retning.
int DrivingControl::get_speed() {
	if (*counter_pointer_ >= 0 && *counter_pointer_ < MAX_COUNTER) {
		return SPEED_LEVELS[*counter_pointer_];
		} else {
		return -1;
	}
}

bool DrivingControl::is_forward_direction() {
	return *counter_pointer_ < 6 || *counter_pointer_ >= 8;
}

// if-statements f�lger samme logik som get_speed()
bool DrivingControl::get_lights_state() {
	return *counter_pointer_ < 6 || (*counter_pointer_ >= 7 && *counter_pointer_ < 11);
}

bool DrivingControl::get_brake_state(){
	(*counter_pointer_)--;
	int previous_speed = get_speed();
	bool previous_direction = is_forward_direction();
	(*counter_pointer_)++;
	// Hvis nuv�rende fart end lavere end tidligere fart, skal der returneres true;
	// Derudover, hvis der er skiftet retning siden sidste refleksbrik, m� bilen ogs� skulle bremse/standse
    return get_speed() < previous_speed || is_forward_direction() != previous_direction;
	// Man kan specificere at den bremser ud fra counter_pointer
	// Ellers kan man have en privat variabel, der husker tidligere speed, 
	// og ud fra den og nuv�rende speed afg�re, om der bliver bremset eller ej.
}