/*
 * DrivingControl.h
 *
 * Created: 6/14/2024 12:53:05 PM
 *  Author: ottosejrskildsantess
 */ 

#pragma once

class DrivingControl{
	private:
		int* counter_pointer_;

	public:
		DrivingControl(int* counter_pointer);

		// Klassemetoderne tager ikke noget input; de henter blot v�rdien for counter fra klasse instansen

		// Returv�rdi bruges til; Motor
		int get_speed();
	
		// Returv�rdi bruges til; Motor
		bool is_forward_direction();
	
		// Returv�rdi bruges til; Light
		bool get_lights_state();
	
		// Returv�rdi bruges til; Light
		bool get_brake_state();
	
};