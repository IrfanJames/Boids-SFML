#pragma once

#include "Boid.h"
#include "Boids_Handle.h"

//float distance(Entity* a, Entity* b) {
//
//	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
//}

float distance(float Ax, float Ay, float Bx, float By) {

	return sqrt((Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By));
}
//Separation = 0, Alignment = 0, Cohesion = 0;

void update3Bools(Handle arr[6]) {
	float d = arr[0].w / 2, lL = arr[0].lowLimit, tot = arr[0].upLimit - arr[0].lowLimit, _scale = 1.3f;
	
	Separation	= arr[0].getIntensity() * _scale;
	Alignment	= arr[1].getIntensity() * _scale;
	Cohesion	= arr[2].getIntensity() * _scale;
	maxSpeed	= arr[3].getIntensity() * 10.5f;

	/*bool3[0] = Separation;
	bool3[1] = Alignment;
	bool3[2] = Cohesion;*/
}

ConvexShape coolSector(float Radius , float HalfAngle) {
	int _Points = (20 + Radius / 7) / 360 * 2 * HalfAngle + 3; //cout << _Points << "\n";
	ConvexShape _Sector(abs(_Points) + 3);
	float _theeta = -HalfAngle;

	_Sector.setPoint(0, sf::Vector2f(0, 0));
	for (int c = 1; c <= _Points + 1; c++) {
		_Sector.setPoint(c, sf::Vector2f(Radius * cos(_theeta * DegToRad), Radius * sin(_theeta * DegToRad)));

		_theeta += ((2 * HalfAngle) / _Points);
	}
	_Sector.setPoint(_Points + 2, sf::Vector2f(0, 0));

	_Sector.setFillColor(Color(41, 126, 74, 80));
	_Sector.setPosition(sectorPosition.x, sectorPosition.y);

	return _Sector;
}

/*
if (0.2f <= (float)((float)(clock() - resetTime) / CLOCKS_PER_SEC)) {
			if (Keyboard::isKeyPressed(Keyboard::R)) { cout << "\n------------------RESET-----------------\n"; resetTime = clock(); goto RESET; }
		}
*/

/*

	Image exImage, exWeb;
	cout << "exImage loaded: " << exImage.loadFromFile("Images/2022-04-03-(3).png") << endl;
	cout << "exWeb loaded: " << exWeb.loadFromFile("Images/image.png") << endl;

	for (int c = 0; c < 1920; c++)
		for (int cc = 0; cc < 1080; cc++) {
			//int exAverage = (int)exImage.getPixel(c, cc).r / 3 + (int)exImage.getPixel(c, cc).g / 3 + (int)exImage.getPixel(c, cc).b / 3;
			int exAverage = (int)exImage.getPixel(c, cc).r * 0.299 + (int)exImage.getPixel(c, cc).g * 0.587 + (int)exImage.getPixel(c, cc).b * 0.114;
			exImage.setPixel(c, cc, Color(exAverage, exAverage, exAverage));


			//if (((c / 20) % 2) && ((cc / 20) % 2)) exampleImage.setPixel(c % 20 + c, cc % 20 + cc, Color(41, 126, 74, 80));

			cout << (int)exImage.getPixel(c, cc).r << " " << (int)exWeb.getPixel(c, cc).r << ". " << c << " : " << cc << "\n";
			cout << (int)exImage.getPixel(c, cc).g << " " << (int)exWeb.getPixel(c, cc).g << ". " << c << " : " << cc << "\n";
			cout << (int)exImage.getPixel(c, cc).b << " " << (int)exWeb.getPixel(c, cc).b << ". " << c << " : " << cc << "\n\n";

			if ((int)exImage.getPixel(c, cc).r != (int)exWeb.getPixel(c, cc).r) cout << "RRRR. " << c << " : " << cc << "\n";
			if ((int)exImage.getPixel(c, cc).g != (int)exWeb.getPixel(c, cc).g) cout << "GGGG. " << c << " : " << cc << "\n";
			if ((int)exImage.getPixel(c, cc).b != (int)exWeb.getPixel(c, cc).b) cout << "BBBB. " << c << " : " << cc << "\n\n\n";
		}
		Texture exText;
		exText.loadFromImage(exImage);
		Sprite exSprite(exText);

*/