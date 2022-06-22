#pragma once

#include <iostream>
#include "sfml/Graphics.hpp"

using namespace std;
using namespace sf;

float DegToRad = 0.01745329f;
float RadToDeg = 57.295779f;

int W = 1800;// They were unsigned once
int H = 1000;// They were unsigned once

unsigned int NoOfBoids = 75;
unsigned int Boid1_3 = 1;
float maxSpeed = 4;
float Far = 130, angleFOV = 120.0f;

/*int Rules[2][3][3] = {
	{{0,113,188}, {0,169,157}, {121,61,173}},
	{{87,87,87}, {117,117,117}, {91,91,91,}}
};*/

float Separation = 0, Alignment = 0, Cohesion = 0, bool3[3] = { 0,0,0 };
bool FollowCursor = 0, Predator = 0;
bool End = 0, Menu = 0, Pause = 0;

int NoOfHandle = 0;
bool extend = 0;

sf::Vector2f sectorPosition(1102, 645);


float validAngle(float angle) {//------Begging for Optimization
	//cout << "\n----Fun----" << angle << endl;

	for (int c = 0; (0 > angle || angle >= 360) && c < 100; c++) {
		angle -= (int)(angle / 360) * 360;                                                   
		while (angle < 0)
			angle += 360;
	}
	//cout << "\n----Fun----" << angle << endl;
	return angle;
}

float sfmlToPrinciple(float angleSfml) {

	angleSfml = validAngle(angleSfml);
	float temp = atan2(cos(angleSfml * DegToRad), sin(angleSfml * DegToRad)) * RadToDeg;
	
	
	return temp;
}

float principleToSfml(float angle) {

	angle -= 90;
	angle = 360 - angle;

	return validAngle(angle);

}