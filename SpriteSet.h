#ifndef SPRITESET
#define SPRITESET

#include <SFML/Graphics.hpp>
#include<vector>
using namespace sf;

enum class StyleOfSet { cycle, withEnd, OnlySprite };

class SpriteSet {

private:
	Sprite mSprite;
	Texture mTexture;
	IntRect mRect;
	Clock mClock;
	int mNumberTale;
	int mSize;
	int i = 0;
	bool FrameEnd = false;
	std::vector<IntRect> Frames;
	StyleOfSet mStyle;

public:
	void setSprites(std::string aTexturePath, IntRect aRect, int aNumberTales, StyleOfSet aStyle);

	void spritesActivation(int aTimer, bool act);

	bool isOverSpriteSet();

	void setPosition(float x, float y);

	Vector2f getPosition();

	void move(float x, float y);

	void setScale(float x, float y);

	Sprite getSprite();

	void getSpriteNumber(int aNumber);
};

#endif // !SPRITESET