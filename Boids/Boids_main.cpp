/*
taskkill /F /IM Boids.exe
*/

#include <list>
#include "Boids_Classes.h"
#include <SFML/Audio.hpp>

/*
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
) {
//*/
//int wmain(int argc, wchar_t** argv) {
//int main( int argc, char* argv[] ) {
//int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {

int main() {
	//RenderWindow app(VideoMode(W, H), "Boids", Style::Fullscreen, ContextSettings(0));
	sf::ContextSettings settings; settings.antialiasingLevel = 8;
	RenderWindow app(VideoMode(W, H), "Boids (Please Press Tab)", Style::Default, settings);
	app.setVerticalSyncEnabled(1);

	Image logo;
	logo.loadFromFile("Images/Logo.png");
	app.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());

	W = app.getSize().x; H = app.getSize().y;
	app.setFramerateLimit(60);
	srand(time(NULL));
	time_t frame = clock();
	bool pressBool = 0, scroolBool = 0, nBoolDebug = 0;

	//Font menuFont;cout << "Hi ..\t" << c << endl;
	////menuFont.loadFromFile("Fonts/FUTURA21.ttf");

	//wcout << "pl";

	Shader Bloom;
	//cout << Bloom.loadFromFile("Bloom.frag", sf::Shader::Fragment) << " : :: rfvtgb\n";
	Clock _t_clock;
	float sec = _t_clock.getElapsedTime().asSeconds();
	
	Bloom.setUniform("u_time", sec);
	Bloom.setUniform("u_resolution", sf::Vector2f(200.0f, 200.0f));
	Bloom.setUniform("texture", sf::Shader::CurrentTexture);

	//Bloom.setUniform("offset", 2.f);
	//Bloom.setUniform("point", sf::Vector3f(0.5f, 0.8f, 0.3f));
	//Bloom.setUniform("color", sf::Glsl::Vec4(color));          // color is a sf::Color
	//Bloom.setUniform("matrix", sf::Glsl::Mat4(transform));     // transform is a sf::Transform
	//Bloom.setUniform("overlay", example);                      // texture is a sf::Texture
	//Bloom.setUniform("current", sf::Shader::CurrentTexture);

	//if (!menuFont.loadFromFile("Fonts/FRUTIGEA.ttf"))

	//Text _1("Rule 1 1", menuFont, 20);
	////_1.setColor(Color::Red);
	//_1.setPosition(300, 200);


	Music bgSong;
	//bgSong.openFromFile("Audio/In This Shirt.ogg");
	bgSong.openFromFile("Audio/Onceagain.ogg");
	bgSong.setVolume(10);
	bgSong.setLoop(1);
	//bgSong.play();

	int cRadius = 10, cSides = 10;
	CircleShape circle(cRadius);
	circle.setFillColor(Color(41, 126, 74));
	circle.setOrigin(cRadius, cRadius);
	circle.setPosition(W / 2, H / 2);

	int A = 50, B = 33, C = 490, D = 10;

	Texture b1, b2, b3, ruleTexArr[2][3], tot, t, tt, h0, h1, fov[3];
	b1.loadFromFile("Images/Boid-Grey.png");
	b2.loadFromFile("Images/Boid-Red.png");
	b3.loadFromFile("Images/Boid-Yellow.png");

	h0.loadFromFile("Images/Handle_Off.png");
	h1.loadFromFile("Images/Handle_On.png");

	string m_string; // Rules
	for (int c = 0; c < 3; c++) {
		m_string = "Images/Rule-" + to_string(1 + c) + ".png";
		ruleTexArr[0][c].loadFromFile(m_string);

		m_string = "Images/Rule-" + to_string(1 + c) + "-Off.png";
		ruleTexArr[1][c].loadFromFile(m_string);
	}

	fov[0].loadFromFile("Images/Boid-Red.png");

	//t.loadFromFile("Images/Tab1.png");
	//t.loadFromFile("Images/Tab2.png");
	//t.loadFromFile("Images/Tab12.png");
	//t.loadFromFile("Images/Newest.png");
	t.loadFromFile("Images/Tab_Back.png");
	tt.loadFromFile("Images/Tab_Type.png");
	
	Sprite tab[2];
	tab[0].setTexture(t);
	tab[0].setOrigin(1158 / 2, 859 / 2);
	tab[0].setPosition(W / 2, H / 2);
	tab[1].setTexture(tt);
	tab[1].setOrigin(1158 / 2, 859 / 2);
	tab[1].setPosition(W / 2, H / 2);

	Sprite sectorBird(fov[0]);
	sectorBird.setOrigin(17 / 2, 22 / 2);
	sectorBird.setPosition(sectorPosition.x, sectorPosition.y);
	sectorBird.setRotation(90);

	Sprite ruleArr[2][3];

	for (int c = 0; c < 2; c++) {
		for (int cc = 0; cc < 3; cc++) {
			ruleArr[c][cc].setTexture(ruleTexArr[c][cc]);
			ruleArr[c][cc].setPosition(10.0, 10.0 + cc * 17.0);
		}
	}

	list<Entity*> entities;

while(!End) {
	
	//Boids
	for (int c = 0; c < NoOfBoids; c++) {
		Texture temp_Texture;
		Boid* b = new Boid();
		
		//entities.emplace_back(sBoid, rand() % W, rand() % H, rand() % 361, 8);

		b->setAll(b1, 17, 22, rand() % W, rand() % H, rand() % 361, 8);
		//if (c != 0) b->setAll(sBoid, rand() % 100 + 250, rand() % 100 + 300, 90, 8);
		//else b->setAll(sBoid, 400, 400, 90, 8);
		
		Boid1_3 = rand() % 3 + 1;
		//Boid1_3 = 1 + (c == 0);
		switch (Boid1_3) {
		case 1:	 b->sprite.setTexture(b1); break;
		case 2:	 b->sprite.setTexture(b2); break;
		case 3:	 b->sprite.setTexture(b3); break;
		default: b->sprite.setTexture(b1); break;
		}

		b->serial += Boid1_3;
		entities.push_back(b);
	}

	//Animation sHandle(h0, 0, 0, 9, 24, 1, 0.2f);
	Handle h[4], FOV[3];
	for (int c = 0; c < 4; c++) {//32--337
		//h[c].lowLimit = app.getSize().x / 2 + 32 + h[c].w / 2; h[c].upLimit = app.getSize().x / 2 + 32 + 352 - h[c].w / 2; //mid_point + displacement + handle_width
		h[c].lowLimit = W / 2 + 32 + h[c].w / 2; h[c].upLimit = W / 2 + 32 + 353 - h[c].w / 2; //mid_point + displacement + handle_width

		
		//h[c].setAll(sHandle, h[c].lowLimit + (c == 3) * 80, 67 * c + (app.getSize().y / 2 - 337) + (c == 3) * 67, 0, 4.5);
		h[c].setAll(h0, h[c].w, h[c].h, h[c].lowLimit + (c == 3) * 80, 67 * c + (H / 2 - 337) + (c == 3) * 67, 0, 4.5);
		//for three boxes set Intensity to ~0,~33,~66
		h[c].serial = c + 1;
	}

	while (app.isOpen()&&!End) {
		Event evnt;
		while (app.pollEvent(evnt)) {
			if (evnt.type == evnt.Closed) {
				app.close();
				End = 1;
				entities.clear();
			}
			if (evnt.type == evnt.Resized) {
				app.setView(sf::View(sf::FloatRect(0, 0, evnt.size.width, evnt.size.height)));
			}

			if (evnt.type == evnt.KeyPressed) {
				if (evnt.key.code == Keyboard::M) { if (bgSong.getStatus() == bgSong.Playing) bgSong.pause(); else bgSong.play(); }

				if (evnt.key.code == Keyboard::Num1 || evnt.key.code == Keyboard::Numpad1) { h[0].setIntensity(((int)(h[0].getIntensity()) == 0) * 100.0f); cout << "\t------------------1-----------------\n"; }
				if (evnt.key.code == Keyboard::Num2 || evnt.key.code == Keyboard::Numpad2) { h[1].setIntensity(((int)(h[1].getIntensity()) == 0) * 100.0f); cout << "\t------------------2-----------------\n"; }
				if (evnt.key.code == Keyboard::Num3 || evnt.key.code == Keyboard::Numpad3) { h[2].setIntensity(((int)(h[2].getIntensity()) == 0) * 100.0f); cout << "\t------------------3-----------------\n"; }

				if (evnt.key.code == Keyboard::R) { cout << "\n------------------RESET-----------------\n"; goto End; }
				if (evnt.key.code == Keyboard::Escape) { app.close(); End = 1; cout << "\n------------------ESC Pressed-----------------\n"; goto End; }
				if (evnt.key.code == Keyboard::Tab) {
					if (Menu) { Menu = 0; Pause = 0; bgSong.setVolume(bgSong.getVolume() + 35); }
					else { Menu = 1; Pause = 1; bgSong.setVolume(bgSong.getVolume() - 35 * (bgSong.getVolume() - 35 >= 0)); }
				}
				if (evnt.key.code == Keyboard::Space) {
					if (Pause) { Pause = 0; cout << "\n------------------RESUMED-----------------\n"; float offset = bgSong.getPlayingOffset().asSeconds(); bgSong.play(); bgSong.setPlayingOffset(seconds(offset)); }
					else { Pause = 1;  cout << "\n------------------PAUSED-----------------\n"; bgSong.pause(); }
				}

				if (evnt.key.code == Keyboard::N) { nBoolDebug = !nBoolDebug; cout << "nBoolDebug: " << nBoolDebug; }
				if (evnt.key.code == Keyboard::F) { FollowCursor = !FollowCursor; Predator = 0; cout << "F: " << FollowCursor << "P: " << Predator << "\n"; }
				if (evnt.key.code == Keyboard::P) { Predator = !Predator; FollowCursor = 0;		cout << "F: " << FollowCursor << "P: " << Predator << "\n"; }

				if (evnt.key.code == Keyboard::Add) {
					for (int c = 0; c < 5; c++) {
						Boid* b = new Boid();
						b->setAll(b1, 17, 22, rand() % W, rand() % H, rand() % 361, 8);

						Boid1_3 = rand() % 3 + 1;
						//Boid1_3 = 2;
						switch (Boid1_3) {
						case 1: b->sprite.setTexture(b1); break;
						case 2: b->sprite.setTexture(b2); break;
						case 3: b->sprite.setTexture(b3); break;
						default:b->sprite.setTexture(b1); break;
						}
						//b->sprite.setScale(0.4, 0.4);
						b->serial += Boid1_3;
						entities.push_back(b);
					}
				}
				if (evnt.key.code == Keyboard::Subtract && entities.size() != 0) {
					for (int cc = 0; cc < 4 && entities.size() != 0; cc++) {
						auto c = entities.begin();
						Entity* e = *c;

						e->life = 0;

						c = entities.erase(c);
						delete e;
					}
				}
			}

			// ----------------------------------------	Mouse
			/*
			if (evnt.type == evnt.MouseWheelScrolled) {
				if (-15 < (int)evnt.mouseWheelScroll.delta && (int)evnt.mouseWheelScroll.delta < 15 && ((int)evnt.mouseWheelScroll.delta + cSides) > 2) cSides += (int)evnt.mouseWheelScroll.delta;
				cout << (int)evnt.mouseWheelScroll.delta << "\n";
				if (cSides > 2)circle.setPointCount(cSides);
			}//*/
		}
		
		// ----------------------------------------	Mouse

		if (Menu) {
			float m_PosX = (float)W / (float)app.getSize().x, m_PosY = (float)H / (float)app.getSize().y;
			int mouseX = (float)Mouse::getPosition(app).x / m_PosX, mouseY = (float)Mouse::getPosition(app).y / m_PosY, serialNum = 0;
			float d = 1 + h[0].h / 2, dist = 0.0f, _initialY = (((float)app.getSize().y/ m_PosY) / 2 - 337 / m_PosY);
			
			/*cout << "\t\t" << _initialY - d << "\t\t" << _initialY << "\n";
			cout << 932 / m_PosX << "\t" << 1283 / m_PosX << "\n";
			cout << "\t\t" << 633 / m_PosY + d + 2 << "\n\n";*/

			if ((932 / m_PosX <= mouseX && _initialY - d <= mouseY && mouseX <= 1283 / m_PosX && mouseY <= 633 / m_PosY + d + 2)) {
				circle.setPosition(mouseX, mouseY);
				int temp = mouseY - _initialY + d;
				temp /= 67 / m_PosY;
				serialNum = (temp < 3) * (temp + 1) + (3 < temp && temp < 6) * (temp)+(6 < temp) * (temp - 1);

				temp = (mouseY - _initialY + d);
				for (int c = 0; c < 6; c++) {
					if (2 * d + 67 / m_PosY * c < temp && temp < (c + 1) * 67 / m_PosY) serialNum = 0;
				}
				//cout << temp << "  " << serialNum << "\n";

				for (int c = 0; c < 4; c++) {
					h[c].sprite.setTexture(h0);
					h[c].sprite.setScale(1, 1);
					if (c != serialNum - 1) continue;
					h[c].sprite.setTexture(h1);
					h[c].sprite.setScale(1.1, 1.3);
				}

				if (-10 <= evnt.mouseWheelScroll.delta && !!(evnt.mouseWheelScroll.delta)&& evnt.mouseWheelScroll.delta <= 10) {
					dist += evnt.mouseWheelScroll.delta;
					h[serialNum - 1].x += 2 * dist;
				}
				pressBool = (Mouse::isButtonPressed(Mouse::Left));
			}
			else {
				circle.setPosition(100, 100);
				if (Mouse::isButtonPressed(Mouse::Left)) extend = 1; else extend = 0;
				for (int c = 0; c < 4; c++) {
					h[c].sprite.setTexture(h0);
					h[c].sprite.setScale(1, 1);
				}
			}
			//cout << (extend)*NoOfHandle + (!extend) * serialNum - 1 << "\n";
			if (pressBool && !!Mouse::isButtonPressed(Mouse::Left)) { h[(extend)*NoOfHandle + (!extend) * serialNum - 1].x = mouseX; NoOfHandle = (extend)*NoOfHandle + (!extend) * serialNum; }

			if (Keyboard::isKeyPressed(Keyboard::Right)) { h[serialNum - 1].x += 5; cout << "\n------------------RIGHT-----------------\n"; }
			if (Keyboard::isKeyPressed(Keyboard::Left)) { h[serialNum - 1].x -= 5; cout << "\n------------------LEFT------------------\n"; }
			Far = distance(sectorPosition.x, sectorPosition.y, (float)Mouse::getPosition(app).x, (float)Mouse::getPosition(app).y); angleFOV = abs(atan2((sectorPosition.y - (float)Mouse::getPosition(app).y), ((float)Mouse::getPosition(app).x - sectorPosition.x)) * RadToDeg);
		}
		update3Bools(h);

		//cout << Separation << "\t" << Alignment << "\t" << Cohesion << "\n";
		A = -10; B = -11; C = -12; D = -13;
		unsigned int mo = 0, sFar = 35;

		if ((Separation + Alignment + Cohesion + (FollowCursor != Predator)) && !Pause) {
			for (auto e : entities) {///////////
				
				float angleS = 0.0f, angleA = 0.0f, angleC = 0.0f;
				float dxS = 0.0f, dxA = 0.0f, dxC = 0.0f;
				float dyS = 0.0f, dyA = 0.0f, dyC = 0.0f;
				unsigned int n = 0, sn = 0;
				//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
				float mAngle = 0.0f;
				float mX = 0, mY = 0.0f, mag = 0.0f;
				//float mX = Mouse::getPosition(app).x, mY = Mouse::getPosition(app).y, mag = 0.0f;
				float nX = 0, nY = 0.0f, nMag = 1.0f;
				float efDist = 0.0f;

				if (e == *entities.begin()) {
					e->sprite.setTexture(b2);
					A = e->x; B = e->y;
				}

				if (FollowCursor == Predator) {
					for (auto f : entities) {
						if (e == f || (abs(e->x - f->x) >= Far || abs(e->y - f->y) >= Far) || (abs(sfmlToPrinciple(atan2((e->y - f->y), (f->x - e->x)) * RadToDeg + e->angle)) >= angleFOV) || (distance(e->x, e->y, f->x, f->y) >= Far))
						{
							if (e == *entities.cbegin() && e != f) f->sprite.setTexture(b1);

							continue;
						}

						efDist = distance(e->x, e->y, f->x, f->y);
						if (efDist <= sFar) {
							sn++;
							nMag = 1 / (abs(efDist) + 1);
							//nMag = 1;

							nX += (e->x - f->x) * nMag;
							nY += (e->y - f->y) * nMag;

						}

						n++;
						mX += f->x;
						mY += f->y;
						mAngle += f->angle;

						if (e == *entities.cbegin()) {
							f->sprite.setTexture(b3);
							//if (!mo) { C = f->x; D = f->y; }
						}
					}

					//cout << sn << "\t";
					if (n > 0) {
						mX /= n; mY /= n;
						mAngle = validAngle(mAngle / n);
						e->angle = validAngle(e->angle);
						float ad = validAngle(abs(e->angle - mAngle) * 0.1);
						if (mo == 0) { circle.setPosition(mX, mY); C = mX; D = mY; }

						if (Separation != 0 && sn != 0) {
							nX /= sn; nY /= sn;
							nX += e->x; nY += e->y;
							//cout << nX << "\t" << nY << "\n";
							float xcxc = atan2((e->y - nY), (nX - e->x)) * RadToDeg;
							mag = sqrtf((e->y - nY) * (e->y - nY) + (nY - e->x) * (nY - e->x));
							//if (mo == 0) { circle.setPosition(nX, nY); C = nX; D = nY; }
							/*/----------
							int sign = 1;
							//if (abs(xcxc) > 90) sign = -1; else sign = 1;

							dxS += sin(e->angle * DegToRad) * mag * sign;
							dyS += -cos(e->angle * DegToRad) * mag * sign;

							e->dx += (dxS * Separation) * 0.003f;
							e->dy += (dyS * Separation) * 0.003f;
							//----------*/


							xcxc = principleToSfml(xcxc);
							//cout << mX - e->x << "   \t " << e->y - mY << "   \t" << xcxc << "\n";

							float a = abs(validAngle(e->angle - xcxc)), b = abs(validAngle(xcxc - e->angle));
							float ad = ((a <= b) * a + (b < a) * b) * 0.6;
							//cout << a << "\t" << b << "\t" << ad << "\n";

							if (e->angle > xcxc)
								angleS = e->angle - xcxc <= 180 ? -ad : ad;
							else
								angleS = xcxc - e->angle < 180 ? ad : -ad;

							angleS *= 0.08f;
						}

						if (Alignment != 0 && e->angle != mAngle) {

							////* 
							//if (e->angle > mAngle)
							//	angleA = e->angle - mAngle <= 180 ? -ad : ad;
							//else
							//	angleA = mAngle - e->angle <= 180 ? ad : -ad;//*/

							float ad = abs(e->angle - mAngle) * 0.6;

							if (e->angle > mAngle)
								angleA = e->angle - mAngle <= 180 ? -ad : ad;
							else
								angleA = mAngle - e->angle < 180 ? ad : -ad;

							/*
							float evilTwin = validAngle(mAngle + 180);
							if (e->angle > mAngle && e->angle >= evilTwin) {
								angleA += 1.0;
							}
							else if (e->angle < mAngle && e->angle <= evilTwin) {
								angleA += 1.0;
							}
							else if (e->angle > mAngle && e->angle <= evilTwin) {
								angleA -= 1.0;
							}
							else if (e->angle > mAngle && e->angle <= evilTwin) {
								angleA += 1.0;
							}//*/

							angleA *= 0.11f;
						}

						if (Cohesion != 0 && efDist >= sFar) {
							float xcxc = atan2((e->y - mY), (mX - e->x)) * RadToDeg;

							//----------
							int sign = 1;
							//if (abs(xcxc) > 90) sign = -1; else sign = 1;

							mag = sqrtf((e->y - mY) * (e->y - mY) + (mX - e->x) * (mX - e->x));
							dxC += sin(e->angle * DegToRad) * mag * sign;
							dyC += -cos(e->angle * DegToRad) * mag * sign;

							e->dx += (dxC * Cohesion) * 0.003f;
							e->dy += (dyC * Cohesion) * 0.003f;
							//----------


							xcxc = principleToSfml(xcxc);
							//cout << mX - e->x << "   \t " << e->y - mY << "   \t" << xcxc << "\n";

							float a = abs(validAngle(e->angle - xcxc)), b = abs(validAngle(xcxc - e->angle));
							float ad = ((a <= b) * a + (b < a) * b) * 0.6;
							//cout << a << "\t" << b << "\t" << ad << "\n";

							if (e->angle > xcxc)
								angleC = e->angle - xcxc <= 180 ? -ad : ad;
							else
								angleC = xcxc - e->angle < 180 ? ad : -ad;

							angleC *= 0.06f;
						}

					}
				}

				if ((Separation + Alignment + Cohesion) != 0) {

					e->angle += ((angleS * 0.77f * Separation) + (angleA * Alignment) + (angleC * 0.5f * Cohesion)) / ((Separation != 0) + (Alignment != 0) + (Cohesion != 0));
					e->angle = validAngle(e->angle); //do validAngle separately because above is adding (355+=valid(10) no(356)) :: valid(365) yes(5)
				}

				if (FollowCursor&& (distance(e->x, e->y, Mouse::getPosition(app).x, Mouse::getPosition(app).y) <= Far)) {
					
					//----------
					int sign = 1;
					//if (abs(xcxc) > 90) sign = -1; else sign = 1;

					mag = sqrtf((e->y - Mouse::getPosition(app).y) * (e->y - Mouse::getPosition(app).y) + (Mouse::getPosition(app).x - e->x) * (Mouse::getPosition(app).x - e->x));

					e->dx += (sin(e->angle * DegToRad) * mag * sign) * 0.003f;
					e->dy += (-cos(e->angle * DegToRad) * mag * sign) * 0.003f;
					//----------

					float xcxc = principleToSfml(atan2((e->y - Mouse::getPosition(app).y), (Mouse::getPosition(app).x - e->x)) * RadToDeg);

					float a = abs(validAngle(e->angle - xcxc)), b = abs(validAngle(xcxc - e->angle));
					float ad = ((a <= b) * a + (b < a) * b) * 0.6;

					if (e->angle > xcxc)
						e->angle += validAngle((e->angle - xcxc <= 180 ? -ad : ad) * 0.4f);
					else
						e->angle += validAngle((xcxc - e->angle <  180 ? ad : -ad) * 0.4f);
				}
				else if (Predator && (distance(e->x, e->y, Mouse::getPosition(app).x, Mouse::getPosition(app).y) <= Far)) {

					nMag = 1 / (distance(e->x, e->y, Mouse::getPosition(app).x, Mouse::getPosition(app).y) + 1);


					nX = (e->x - Mouse::getPosition(app).x) * nMag;
					nY = (e->y - Mouse::getPosition(app).y) * nMag;

					nX += e->x; nY += e->y;
					//cout << nX << "\t" << nY << "\n";
					float xcxc = atan2((e->y - nY), (nX - e->x)) * RadToDeg;
					mag = sqrtf((e->y - nY) * (e->y - nY) + (nY - e->x) * (nY - e->x));
					//if (mo == 0) { circle.setPosition(nX, nY); C = nX; D = nY; }
					/*/----------
					int sign = 1;
					//if (abs(xcxc) > 90) sign = -1; else sign = 1;

					dxS += sin(e->angle * DegToRad) * mag * sign;
					dyS += -cos(e->angle * DegToRad) * mag * sign;

					e->dx += (dxS * Separation) * 0.003f;
					e->dy += (dyS * Separation) * 0.003f;
					//----------*/

					xcxc = principleToSfml(xcxc);
					//cout << mX - e->x << "   \t " << e->y - mY << "   \t" << xcxc << "\n";

					float a = abs(validAngle(e->angle - xcxc)), b = abs(validAngle(xcxc - e->angle));
					float ad = ((a <= b) * a + (b < a) * b) * 0.6;
					//cout << a << "\t" << b << "\t" << ad << "\n";

					if (e->angle > xcxc)
						e->angle += validAngle((e->angle - xcxc <= 180 ? -ad : ad) * 0.4f);
					else
						e->angle += validAngle((xcxc - e->angle < 180 ? ad : -ad) * 0.4f);
				}

				mo++;
				//cout << n << " ";
				//break;

				if (nBoolDebug) break;
			}///////////


			//cout << mo << " ";
			//cout << "\n\n";
		}

		// ----------------------------------------	Update
		for (auto c = entities.begin(); !Pause && c != entities.end();) {
			Entity* e = *c;

			e->update();
			
			if (e->life <= 0) {
				c = entities.erase(c);
				delete e;
			}
			else c++;

			if (nBoolDebug) break;
		}

		Vertex line[] = {
		Vertex(Vector2f(A,B)),
		Vertex(Vector2f(C,D))
		};

		//if (nBoolDebug) {nBoolDebug = 0;
		//cout << 1.0f / ((float)((float)clock() - (float)frame) / CLOCKS_PER_SEC) << "\n\n";
			app.clear(Color(37, 37, 38));

			//app.draw(line, 2, Lines);

			for (auto d : entities) d->draw(app);

			for (int c = 0; c < 3; c++) { //-------------------- 3 bools

				switch (c) {
				case 0: app.draw(ruleArr[Separation == 0][c]);	break;
				case 1: app.draw(ruleArr[Alignment == 0][c]);	break;
				case 2: app.draw(ruleArr[Cohesion == 0][c]);	break;
				default:app.draw(ruleArr[1][c]);	break;
				}

			}

			//app.draw(_1);
			//app.draw(line, 2, Lines);
			//app.draw(circle, &Bloom);
			//app.draw(circle);

			if (Menu) {
				app.draw(tab[0]);
				float m_MouseX = (float)Mouse::getPosition(app).x / (float)app.getSize().x * W, m_MouseY = (float)Mouse::getPosition(app).y / (float)app.getSize().y * H;
				//cout << m_MouseX << "\t" << m_MouseY << "\n";
				app.draw(coolSector(distance(sectorPosition.x, sectorPosition.y, (float)m_MouseX, (float)m_MouseY), abs(atan2((sectorPosition.y - (float)m_MouseY), ((float)m_MouseX - sectorPosition.x))* RadToDeg)));

				app.draw(sectorBird);
				app.draw(tab[1]);

				for (int c = 0; c < 4; c++) {
					/*Handle* hh = &h[c];

					Entity* e = hh;
					e->update();
					e->anim.update();*/
					h[c].update();

					//app.draw(h[c].anim.sprite);
					h[c].draw(app);

					//e->draw(app);
				}
				//cout << Mouse::getPosition(app).x << "\t" << Mouse::getPosition(app).y << "\n";
			}

			app.display();
		//}

		//app.setTitle("Boids   " + to_string(1.0f / ((float)((float)clock() - (float)frame) / CLOCKS_PER_SEC)));
		frame = clock();

	}
End:
	;
	while (!entities.empty()) {
		for (auto c = entities.begin(); c != entities.end();) {
			Entity* e = *c;
			c = entities.erase(c);
			delete e;
		}
	}
}

	//vector<string> const args(argv, argv + argc);
	system("pause");

}
