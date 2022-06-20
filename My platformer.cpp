#include <SFML/Graphics.hpp>
#include<iostream>
#include"Object.h"
#include"SpriteSet.h"
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
	Wall2.setObject(Vector2f(20, 800), Color::Red);
	Wall2.setPosition(1000, 20);

	Object Cube;
	Cube.setObject(Vector2f(100, 100), Color::Red);
	Cube.collision(Wall.getGlobalBounds(), true);
	Cube.collision(Wall2.getGlobalBounds(), true);

	SpriteSet Player;
	Player.setSprites("Textures/DemonWalking.png", IntRect(0, 0, 32, 32), 8, StyleOfSet::cycle);
	Player.setScale(3, 3);
	float PlayerSpeed = 10;

	Object ObPlayer;
	ObPlayer.setObject(Vector2f(32, 32), Color::Transparent);
	ObPlayer.setScale(3, 3);
	ObPlayer.collision(Wall.getGlobalBounds(), true);
	ObPlayer.collision(Wall2.getGlobalBounds(), true);
	ObPlayer.setPosition(500, 400);
	int scale = 1;

	Texture txBackGround;
	txBackGround.loadFromFile("Textures/BackGround.png");
	Sprite spBackGround(txBackGround);


	while (window.isOpen())
	{
		ObPlayer.setSprite(Player.getSprite());
		ObPlayer.setGravitation(false);
		Cube.setGravitation(false);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			if (event.type == Event::MouseButtonPressed) {

				if (Mouse::isButtonPressed(Mouse::Button::Left)) {
					//cout << event.key.code << endl;
					if (Mouse::getPosition().x >= Cube.getPosition().x && Mouse::getPosition().y >= Cube.getPosition().y && Mouse::getPosition().x <= Cube.getSize().x && Mouse::getPosition().y <= Cube.getSize().y) {
						Cube.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);

					}

				}
			}
			
			if (event.type == Event::KeyPressed) {
				//cout << event.key.code << endl;

				if (Keyboard::isKeyPressed(Keyboard::D)) {
					scale = 1;

					if (ObPlayer.getPosition().x < window.getSize().x - ObPlayer.getSize().x * 3) {
						Player.spritesActivation(100, true);
						ObPlayer.move(+PlayerSpeed, 0);

					}
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					scale = -1;

					if (ObPlayer.getPosition().x > ObPlayer.getSize().x * 3) {
						Player.spritesActivation(100, true);
						ObPlayer.move(-PlayerSpeed, 0);

					}
				}
				if (Keyboard::isKeyPressed(Keyboard::W)) ObPlayer.move(0, -PlayerSpeed);
				if (Keyboard::isKeyPressed(Keyboard::S)) ObPlayer.move(0, PlayerSpeed);
			}
		}

		ObPlayer.setScale(scale * 3, 3);
		Player.setScale(scale * 3, 3);

		//cout << ObPlayer.isCollision(Cube.getGlobalBounds()) << endl;
		Cube.pursue(ObPlayer.getPosition(), 2);

		cout << Cube.isCollisionLine(ObPlayer) << endl;

		window.clear();
		window.draw(spBackGround);
		Wall.render(window, false);
		Wall2.render(window, false);
		Cube.render(window, false);
		ObPlayer.render(window, true);
		window.display();
	}

	return 0;
}
