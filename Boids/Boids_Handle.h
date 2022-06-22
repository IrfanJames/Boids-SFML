#pragma once
#include "Boids_Entity.h"

class Handle : public Entity {
public:

	int w = 9, h = 24;//352
	int lowLimit, upLimit; //992   //1344  -203
	//int lowLimit = 932 + w / 2, upLimit = 1284 - w / 2; //992   //1344  -201

	Handle() {//1.7777778-1763.55555555555776 //1.8-
		name = "Handle";
		serial = 1;
	}

	void update() {

		if (x < lowLimit) x = lowLimit;
		if (x > upLimit)  x = upLimit;
	}

	float getIntensity() {
		//0-1
		return (x - lowLimit) / (upLimit - lowLimit);
	}

	void setIntensity(float Intensity0_100) {
		//0-100
		// << "\nBefore: " << getIntensity() << "\n";
		x = lowLimit + (upLimit - lowLimit) * Intensity0_100 / 100.0f;
		//x = lowLimit + (upLimit - lowLimit) * bool3[(int)Intensity0_100] / 100.0f;
		//cout << "After: " << getIntensity() << "\n";

	}

};