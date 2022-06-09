#ifndef OBJECT
#define OBJECT

#include<SFML/Graphics.hpp>
using namespace sf;

class Object {

private:
	RectangleShape mRectang;
	Sprite mSprite;
	bool Gravitation = false;
	float GravitationSize = 7;

public:

	void setObject(Vector2f aVector, Color aColor) {
		mRectang.setSize(aVector);
		mRectang.setFillColor(aColor);
	}
	
	void setSprite(Sprite aSprite) {
		mSprite = aSprite;
		mSprite.setPosition(mRectang.getPosition().x, mRectang.getPosition().y);
	}

	void setGravitation(bool Gr) {
		if (Gr) mRectang.move(0, GravitationSize);
	}

	void move(float x, float y) {
		mRectang.move(x, y);
		
	}

	void setScale(float x, float y) {
		mRectang.setScale(x, y);
		
	}

	void render(RenderWindow& wn,bool g) {
		wn.draw(mRectang);
		if(g)
		wn.draw(mSprite);
	}

	Vector2f getPosition() {
		return mRectang.getPosition();
	}

	Vector2f getSize() {
		return mRectang.getSize();
	}
};
#endif // !OBJECT
