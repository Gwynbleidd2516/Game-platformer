#include <SFML/Graphics.hpp>
#include<iostream>
#include"SpriteSet.hpp"
#include"Object.hpp"
using namespace std;
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1440, 800), "SFML works!",Style::Close);
	window.setFramerateLimit(60);
	sf::CircleShape shape(50.f);

	SpriteSet Player;
	Player.setSprites("DemonWalking.png", IntRect(0, 0, 32, 32), 8);
	Player.setScale(3, 3);

	Object ObPlayer;
	ObPlayer.setObject(Vector2f(32, 32), Color::Transparent);
	ObPlayer.setScale(3, 3);
	
	Texture txBackGround;
	txBackGround.loadFromFile("BackGround.png");
	Sprite spBackGround(txBackGround);

	while (window.isOpen())
	{
		ObPlayer.setSprite(Player.getSprite());
		ObPlayer.setGravitation(false);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				cout << event.key.code << endl;

				if (Keyboard::isKeyPressed(Keyboard::D)) {
					Player.setScale(3, 3);
					ObPlayer.setScale(3, 3);

					if (ObPlayer.getPosition().x < window.getSize().x-ObPlayer.getSize().x*3) {
						Player.spritesActivation(100, true);
						ObPlayer.move(+5, 0);
						
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					Player.setScale(-3, 3);
					ObPlayer.setScale(-3, 3);

					if (ObPlayer.getPosition().x > ObPlayer.getSize().x*3) {
						Player.spritesActivation(100, true);
						ObPlayer.move(-5, 0);
						
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::W)) ObPlayer.move(0, -5);
				if (Keyboard::isKeyPressed(Keyboard::S)) ObPlayer.move(0, 5);
			}
		}

		window.clear();
		window.draw(spBackGround);
		ObPlayer.render(window, true);
		window.display();
	}

	return 0;
}