#pragma once
#include "Boids_Entity.h"

class Boid : public Entity {
public:

	float speed = 0;

	Boid() {
		name = "Boid";
		serial = 10;
	}
	
	void update() {

		angle = validAngle(angle);

		if (speed >= maxSpeed) {
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		dx += sin(angle * DegToRad) * 0.3f;
		dy += -cos(angle * DegToRad) * 0.3f;

		x += dx;
		y += dy;

		speed = sqrt(dx * dx + dy * dy);

		/*
		int border = 200;
		float turn = 4.0f, mul = 0.0f;
		if (x <= border)			{ if (angle <= 0 || angle >= 180)  { mul = 0.01 * (x);					if (270 <= angle) angle += turn * mul;	else angle -= turn / mul; } }
		else if ((W - border) <= x) { if (angle >= 0 || angle <= 180)  { mul = 0.01 * (x - (W - border));	if (90 <= angle)  angle += turn * mul;	else angle -= turn / mul; } }
		else if (y <= border)		{ if (angle <= 90 || angle >= 270) { mul = 0.01 * (y);					if (180 <= angle) angle -= turn * mul;	else angle += turn / mul; } }
		else if ((H - border) <= y) { if (angle >= 90 || angle <= 270) { mul = 0.01 * (y - (H - border));	if (180 <= angle) angle += turn * mul;	else angle -= turn / mul; } }
		
		//*
		if (x <= 0) x = 0;
		else if (W <= x) x = W;
		else if (y <= 0) y = 0;
		else if (H <= y) y = H;//*/

		//*
		if (x <= 0) x = W;
		else if (W <= x) x = 0;
		else if (y <= 0) y = H;
		else if (H <= y) y = 0;//*/
	}

};

/*
if (x <= border)			{ if (angle < 0 || angle >= 180)  { if (270 < angle) angle += turn;	else angle -= turn; } }
		else if ((W - border) <= x) { if (angle > 0 || angle <= 180)  { if (90 < angle)  angle += turn;	else angle -= turn; } }
		else if (y <= border)		{ if (angle < 90 || angle >= 270) { if (180 < angle) angle += turn;	else angle -= turn; } }
		else if ((H - border) <= y) { if (angle > 90 || angle <= 270) { if (180 < angle) angle += turn;	else angle -= turn; } }
*/

//if (x <= border) { x = border;		if (270 < angle) angle += turn;		else angle -= turn;  /* }//*/angle *= (-0.4 * amp / s * x + amp); }
//else if ((W - border) <= x) { x = W - border;	if (90 < angle)  angle += turn;		else angle -= turn; /* }//*/angle *= (-0.4 * amp / s * (x - W - border) + amp); }
//else if (y <= border) { y = border;		if (180 < angle) angle += turn;		else angle -= turn;/*  }//*/angle *= (-0.4 * amp / s * y + amp); }
//else if ((H - border) <= y) { y = H - border;	if (180 < angle) angle += turn;		else angle -= turn;  /*}//*/angle *= (-0.4 * amp / s * (y - H - border) + amp); }


/*
		if (x <= 20)		{ x = 20;		if (270 <= angle) angle += 0.01f; else angle -= 0.01f; }
		if ((W - 20) <= x)	{ x = W - 20;	if (90 <= angle) angle += 0.01f; else angle -= 0.01f; }
		if (y <= 20)		{ y = 20;		if (180 >= angle) angle += 0.01f; else angle -= 0.01f; }
		if ((H - 20) <= y)	{ y = H - 20;	if (180 >= angle) angle += 0.01f; else angle -= 0.01f; }
//*/

/*if (direction < -11 || 11 < direction) {
			direction *= 11 / direction;
		}

		angle += direction*0.4;

		angle = (int)angle % 361;*/