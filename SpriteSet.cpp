#include"SpriteSet.h"

void SpriteSet::setSprites(std::string aTexturePath, IntRect aRect, int aNumberTales, StyleOfSet aStyle) {
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
	mNumberTale = aNumberTales - 1;
}

void SpriteSet::spritesActivation(int aTimer, bool act) {
	if (mClock.getElapsedTime().asMilliseconds() > aTimer && act == true && (mStyle == StyleOfSet::cycle || mStyle == StyleOfSet::withEnd)) {
		if (i >= mNumberTale && mStyle == StyleOfSet::cycle) {
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

bool SpriteSet::isOverSpriteSet() {
	return FrameEnd;
}

void SpriteSet::setPosition(float x, float y) {
	mSprite.setPosition(x, y);
}

Vector2f SpriteSet::getPosition() {
	return mSprite.getPosition();
}

void SpriteSet::move(float x, float y) {
	mSprite.move(x, y);
}

void SpriteSet::setScale(float x, float y) {
	mSprite.setScale(x, y);

}

Sprite SpriteSet::getSprite() {
	return mSprite;
}

void SpriteSet::setSpriteNumber(int aNumber) {
	mSprite.setTextureRect(Frames[aNumber]);
}