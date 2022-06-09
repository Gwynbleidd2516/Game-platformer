#ifndef SPRITESET_HPP
#define SPRITESET_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

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

public:
	void setSprites(std::string aTexturePath, IntRect aRect, int aNumberTales) {
		mRect = aRect;
		mSize = mRect.width;
		mTexture.loadFromFile(aTexturePath);
		mSprite.setTexture(mTexture);
		mSprite.setTextureRect(mRect);
		mNumberTale = aNumberTales-1;
		
	}

	void spritesActivation(int aTimer, bool act) {
		if (mClock.getElapsedTime().asMilliseconds() > aTimer && act==true) {
			if (i >= mNumberTale) {
				i = 0;
				mRect.left = 0;
				FrameEnd = true;
			}
			else {
				mRect.left += mSize;
				i++;
				FrameEnd = false;
			}
			mSprite.setTextureRect(mRect);
			mClock.restart();
		}
	}

	bool isOverSet() {
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
};

#endif // !SPRITESET_HPP
