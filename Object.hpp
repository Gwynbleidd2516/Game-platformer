#ifndef OBJECT
#define OBJECT

#include<SFML/Graphics.hpp>
using namespace sf;

class Object {

private:
	RectangleShape mRectang;
	Sprite mSprite;
	FloatRect collRect;
	bool Gravitation = false;
	float GravitationSize = 10;
	bool coll = false;

public:

	void setObject(Vector2f aVector, Color aColor) {
		mRectang.setSize(aVector);
		mRectang.setFillColor(aColor);
	}

	void setPosition(float x, float y) {
		mRectang.setPosition(x, y);
	}

	void setSprite(Sprite aSprite) {
		mSprite = aSprite;
		mSprite.setPosition(mRectang.getPosition().x, mRectang.getPosition().y);
	}

	void setGravitation(bool Gr) {
		if (Gr) {
			mRectang.move(0, GravitationSize);
			if (mRectang.getGlobalBounds().intersects(collRect) && coll == true) {
				mRectang.move(0, -GravitationSize);
			}
		}
	}

	bool collision(FloatRect rect,bool col) {
		coll = col;
		collRect = rect;
		return coll;
	}

	void move(float x, float y) {
		mRectang.move(x, y);
		if (mRectang.getGlobalBounds().intersects(collRect)&&coll==true) {
			mRectang.move(-x, -y);
		}
		
	}

	void setScale(float x, float y) {
		mRectang.setScale(x, y);

	}

	void render(RenderWindow& wn, bool g) {
		wn.draw(mRectang);
		if (g)
			wn.draw(mSprite);
	}

	Vector2f getPosition() {
		return mRectang.getPosition();
	}

	Vector2f getSize() {
		return mRectang.getSize();
	}

	FloatRect getGlobalBounds() {
		return mRectang.getGlobalBounds();
	}

};
#endif // !OBJECT