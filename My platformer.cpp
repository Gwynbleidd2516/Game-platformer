#include <SFML/Graphics.hpp>
#include<iostream>
#include"Vyaz/Object.h"
#include"Vyaz/SpriteSet.h"
using namespace std;
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1440, 800), "SFML works!", Style::Close);
	window.setFramerateLimit(60);
	sf::CircleShape shape(50.f);

	Object Wall;
	Wall.setObject(Vector2f(800, 20), Color::Red);
	Wall.setPosition(200, 600);

	Object Wall2;
	Wall2.setObject(Vector2f(20, 600), Color::Red);
	Wall2.setPosition(1000, 20);

	Object Cube;
	Cube.setObject(Vector2f(100, 100), Color::Blue);
	Cube.collision(Wall.getGlobalBounds(), true);
	Cube.collision(Wall2.getGlobalBounds(), true);

	SpriteSet PlayerRight;
	PlayerRight.setSprites("Textures/DemonWalking.png", IntRect(0, 0, 32, 32), 8, StyleOfSet::cycle);
	PlayerRight.setScale(3, 3);

	SpriteSet PlayerLeft;
	PlayerLeft.setSprites("Textures/DemonWalking2.png", IntRect(0, 0, 32, 32), 8, StyleOfSet::cycle);
	PlayerLeft.setScale(3, 3);

	SpriteSet PlayerRightNow;
	PlayerRightNow.setSprites("Textures/DemonWalking.png", IntRect(0, 0, 32, 32), 8, StyleOfSet::OnlySprite);
	PlayerRightNow.setScale(3, 3);

	Object ObPlayer;
	ObPlayer.setObject(Vector2f(32, 32), Color::Transparent);
	ObPlayer.setScale(3, 3);
	ObPlayer.collision(Wall.getGlobalBounds(), true);
	ObPlayer.collision(Wall2.getGlobalBounds(), true);
	ObPlayer.setPosition(500, 400);
	float PlayerSpeed = 10;

	Texture txBackGround;
	txBackGround.loadFromFile("Textures/BackGround.png");
	Sprite spBackGround(txBackGround);

	View Camera;

	//////////////////////////////////////////////////
	SpriteSet ZombeStand;
	ZombeStand.setSprites("Textures/ZombeStand.png", IntRect(0, 0, 32, 32), 2, StyleOfSet::OnlySprite);
	ZombeStand.setScale(3, 3);

	SpriteSet ZombeWalkingLeft;
	ZombeWalkingLeft.setSprites("Textures/ZombeWalkingLeft.png", IntRect(0, 0, 32, 32), 4, StyleOfSet::cycle);
	ZombeWalkingLeft.setScale(3, 3);

	SpriteSet ZombeWalkingRight;
	ZombeWalkingRight.setSprites("Textures/ZombeWalkingRight.png", IntRect(0, 0, 32, 32), 4, StyleOfSet::cycle);
	ZombeWalkingRight.setScale(3, 3);

	Object Zombe;
	Zombe.setObject(Vector2f(32, 32), Color::Transparent);
	Zombe.setScale(3, 3);
	Zombe.collision(Wall.getGlobalBounds(), true);
	Zombe.collision(Wall2.getGlobalBounds(), true);
	Zombe.setSprite(ZombeStand.getSprite());
	bool purse = false;

	while (window.isOpen())
	{
		Camera.setCenter(ObPlayer.getPosition());
		Camera.setSize(720, 400);
		
		ObPlayer.setGravitation(false);
		Cube.setGravitation(false);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

			if (event.type == Event::KeyPressed) {
				//cout << event.key.code << endl;

				if (Keyboard::isKeyPressed(Keyboard::D)) {
					

					if (ObPlayer.getPosition().x < window.getSize().x - ObPlayer.getSize().x * 3) {
						ObPlayer.setSprite(PlayerRight.getSprite());
						PlayerRight.spritesActivation(100, true);
						PlayerRight.setScale(3, 3);
						ObPlayer.move(+PlayerSpeed, 0);

					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::A)) {
					

					if (ObPlayer.getPosition().x > 0) {
						ObPlayer.setSprite(PlayerLeft.getSprite());
						PlayerLeft.spritesActivation(100, true);
						PlayerLeft.setScale(3, 3);
						ObPlayer.move(-PlayerSpeed, 0);

					}
				}

				if (Keyboard::isKeyPressed(Keyboard::W)) {
					ObPlayer.setSprite(PlayerRight.getSprite());
					PlayerRight.spritesActivation(100, false);
					PlayerRight.setScale(3, 3);
					ObPlayer.move(0, -PlayerSpeed);
				}
				else if (Keyboard::isKeyPressed(Keyboard::S)) {
					ObPlayer.setSprite(PlayerLeft.getSprite());
					PlayerLeft.spritesActivation(100, false);
					PlayerLeft.setScale(3, 3);
					ObPlayer.move(0, PlayerSpeed);
				}
				
			}
			
		}

		ObPlayer.setScale(3, 3);

//////////////////////////////////////////////////////////////////////////////////////////////////////		

		if (ObPlayer.getDistanceTo(Zombe.getPosition()) >= 40 &&ObPlayer.getDistanceTo(Zombe.getPosition()) <= 400 && ObPlayer.isCollisionLine(Zombe) == false) {
			Zombe.pursue(ObPlayer.getPosition(), 2);
			if (Zombe.getPosition().x > ObPlayer.getPosition().x) {
				Zombe.setSprite(ZombeWalkingLeft.getSprite());
				ZombeWalkingLeft.spritesActivation(150, true);
			}
			else {
				Zombe.setSprite(ZombeWalkingRight.getSprite());
				ZombeWalkingRight.spritesActivation(150, true);
			}
			purse = true;
		}
		else {
			Zombe.setSprite(ZombeStand.getSprite());
			if (Zombe.getPosition().x > ObPlayer.getPosition().x) {
				ZombeStand.setSpriteNumber(0);
			}
			else {
				ZombeStand.setSpriteNumber(1);
			}
			purse = false;
		}
		cout << purse << endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		window.setView(Camera);
		window.clear();
		window.draw(spBackGround);
		Wall.render(window, false);
		Wall2.render(window, false);
		//Cube.render(window, false);
		ObPlayer.render(window, true);
		Zombe.render(window, true);
		window.display();
	}

	return 0;
}