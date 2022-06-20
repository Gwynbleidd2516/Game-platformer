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
	void setSprites(std::string aTexturePath, IntRect aRect, int aNumberTales, StyleOfSet aStyle) {
		mStyle = aStyle;
		mSize = aRect.width;
		Frames.push_back(aRect);
		for (int i = 1; i < aNumberTales; i++) {
			Frames.push_back(Frames[i - 1]);
			Frames[i].left += mSize;
		}
		mRect = aRect;
		mTexture.loadFromFile(aTexturePath);
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(Frames[0]);
		mNumberTale = aNumberTales-1;
	}

	void spritesActivation(int aTimer, bool act) {
		if (mClock.getElapsedTime().asMilliseconds() > aTimer && act==true && (mStyle==StyleOfSet::cycle|| mStyle == StyleOfSet::withEnd)) {
			if (i >= mNumberTale && mStyle==StyleOfSet::cycle) {
				i = 0;
				FrameEnd = true;
			}
			else {
				i++;
				FrameEnd = false;
			}
			mSprite.setTextureRect(Frames[i]);
			mClock.restart();
		}
	}

	bool isOverSpriteSet() {
		return FrameEnd;
	}

	void setPosition(float x, float y) {
		mSprite.setPosition(x, y);
	}

	Vector2f getPosition() {
		return mSprite.getPosition();
	}

	void move(float x, float y) {
		mSprite.move(x, y);
	}

	void setScale(float x, float y) {
		mSprite.setScale(x, y);
		
	}

	Sprite getSprite() {
		return mSprite;
	}

	void getSpriteNumber(int aNumber) {
		mSprite.setTextureRect(Frames[aNumber]);
	}
};

#endif // !SPRITESET
