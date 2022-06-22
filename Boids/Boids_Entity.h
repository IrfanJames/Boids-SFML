#pragma once

#include "Boids_Global.h"

using namespace sf;
using namespace std;

class Entity {
public:
	int serial;
	float x, y, dx, dy, radius, angle, life;
	string name;
	Sprite sprite;

	Entity() { life = 20.0f; x = W / 2; y = H / 2; dx = 0.0f; dy = 0.0f; angle = 0.0f; radius = 1.0f; serial = 0; }

	void setAll(Texture t, float w, float h, float X, float Y, float Angle = 0.0f, float Radius = 1.0f) {
		x = X; y = Y; angle = Angle; radius = Radius;
		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
	}

	virtual void update() {};
	//virtual void hit() {};

	void draw(RenderWindow& app) {
		sprite.setPosition(x, y);
		sprite.setRotation(angle);
		app.draw(sprite);
	}
	~Entity() {
		;
	}

};