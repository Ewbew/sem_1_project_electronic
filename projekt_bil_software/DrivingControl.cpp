/*
 * DrivingControl.cpp
 *
 * Created: 6/14/2024 1:45:37 PM
 *  Author: ottosejrskildsantess
 */ 

#include "DrivingControl.h"

DrivingControl::DrivingControl(int* counter_pointer):counter_pointer_(counter_pointer){}


// OBS: Disse værdier skal ændres indtil at bilen kører igennem uden for mange fejl; de bestemmes gennem testkørlser.
// OBS: Det kan være, at bilen bliver nødt til at få sat speed til 0, i stedet for bare at skifte retning.
int DrivingControl::get_speed(){
	if(*counter_pointer_==0){
		return 100;
	} else if(*counter_pointer_==1){
		return 90;
	} else if(*counter_pointer_==2){
		return 65;
	} else if(*counter_pointer_==3){
		return 50;
	} else if(*counter_pointer_==4){
		return 90;
	
	// Her skal vi være opmærksomme på, at bilen skal standes efter at have passeret refleksbrik #6, og så derefter køre baglæns-
	// det skal evt. implementeres i get
	} else if (*counter_pointer_==5){
		return 50;
	} else if (*counter_pointer_==6){
		// Baglæns
		return 50;
	} else if (*counter_pointer_==7){
		// Baglæns
		return 50;
	} else if (*counter_pointer_==8){
		// Forlæns igen
		return 80;
	} else if (*counter_pointer_==9){
		return 80;
	} else if(*counter_pointer_==10){
		return 50;
	} else if(*counter_pointer_==11){
		// Slutposition
		return 0;
	} else {
		// Error hvis andet
		return -1;
	}
}

bool DrivingControl::is_forward_direction(){
	if(*counter_pointer_<6){
		return true;
	} else if(*counter_pointer_<8 ){
		return false;
	} else {
		return true;
	}
}

// if-statements følger samme logik som get_speed()
bool DrivingControl::get_lights_state(){
	if(*counter_pointer_<6){
		return true;
	} else if (*counter_pointer_==6){
		return false;
	} else if(*counter_pointer_<11){
		return true;
	} else {
		return false;
	}
}

bool DrivingControl::get_brake_state(){
	(*counter_pointer_)--;
	int previous_speed = get_speed();
	bool previous_direction = is_forward_direction();
	(*counter_pointer_)++;
	// Hvis nuværende fart end lavere end tidligere fart, skal der returneres true;
	// Derudover, hvis der er skiftet retning siden sidste refleksbrik, må bilen også skulle bremse/standse
	if (get_speed() < previous_speed || is_forward_direction() != previous_direction){
		return true;
	} else {
		return false;
	}
		
	// Man kan specificere at den bremser ud fra counter_pointer
	// Ellers kan man have en privat variabel, der husker tidligere speed, 
	// og ud fra den og nuværende speed afgøre, om der bliver bremset eller ej.
}