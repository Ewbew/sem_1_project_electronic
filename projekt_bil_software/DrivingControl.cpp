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


// OBS: Disse værdier skal ændres indtil at bilen kører igennem uden for mange fejl; de bestemmes gennem testkørlser.
// OBS: Det kan være, at bilen bliver nødt til at få sat speed til 0, i stedet for bare at skifte retning.
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

// if-statements følger samme logik som get_speed()
bool DrivingControl::get_lights_state() {
	return *counter_pointer_ < 6 || (*counter_pointer_ >= 7 && *counter_pointer_ < 11);
}

bool DrivingControl::get_brake_state(){
	int current_speed = get_speed();
	bool current_direction = is_forward_direction();
	// Hvis nuværende fart end lavere end tidligere fart, skal der returneres true;
	// Derudover, hvis der er skiftet retning siden sidste refleksbrik, må bilen også skulle bremse/standse
	bool should_brake = current_speed < previous_speed_ || current_direction != previous_direction_;

	previous_speed_ = current_speed;
	previous_direction_ = current_direction;

	return should_brake;
	// Man kan specificere at den bremser ud fra counter_pointer
	// Ellers kan man have en privat variabel, der husker tidligere speed, 
	// og ud fra den og nuværende speed afgøre, om der bliver bremset eller ej.

}