#include"Object.h"

void Object::setObject(Vector2f aVector, Color aColor) {
	mRectang.setSize(aVector);
	mRectang.setFillColor(aColor);
}

void Object::setPosition(float x, float y) {
	mRectang.setPosition(x, y);
}

void Object::setSprite(Sprite aSprite) {
	mSprite = aSprite;
	mSprite.setPosition(mRectang.getPosition().x, mRectang.getPosition().y);
}

void Object::setGravitation(bool Gr) {
	if (Gr) {
		mRectang.move(0, GravitationSize);
		for (int i = 0; i < collRect.size(); i++) {
			if (mRectang.getGlobalBounds().intersects(collRect[i]) && coll == true) {
				mRectang.move(0, -GravitationSize);
				iscollision = true;
			}
			else iscollision = false;
		}
	}
}

void Object::collision(FloatRect rect, bool col) {
	coll = col;
	collRect.push_back(rect);

}

void Object::move(float x, float y) {
	mRectang.move(x, y);
	for (int i = 0; i < collRect.size(); i++) {
		if (mRectang.getGlobalBounds().intersects(collRect[i]) && coll == true) {
			mRectang.move(-x, -y);
		}
		else iscollision = false;
	}
}

void Object::setScale(float x, float y) {
	mRectang.setScale(x, y);
}

void Object::render(RenderWindow& wn, bool g) {
	wn.draw(mRectang);
	if (g)
		wn.draw(mSprite);
}

Vector2f Object::getPosition() {
	return mRectang.getPosition();
}

Vector2f Object::getSize() {
	return mRectang.getSize();
}

FloatRect Object::getGlobalBounds() {
	return mRectang.getGlobalBounds();
}

bool Object::isCollision(FloatRect aRect) {
	if (mRectang.getGlobalBounds().intersects(aRect))
		iscollision = true;
	else
		iscollision = false;
	return iscollision;
}

float Object::getDistanceTo(Vector2f aObject) {
	float x;
	float y;
	float distance;
	x = pow((aObject.x - mRectang.getPosition().x), 2);
	y = pow((aObject.y - mRectang.getPosition().y), 2);
	
	distance = x + y;
	return sqrt(distance);
}

void Object::pursue(Vector2f aVector, float aSpeed) {
	float x;
	float y;
	x = aVector.x - mRectang.getPosition().x;
	y = aVector.y - mRectang.getPosition().y;
	float distance = sqrt(pow(x, 2) + pow(y, 2));
	if (distance > 1) {
		mRectang.move((x * aSpeed) / distance, (y * aSpeed) / distance);
		for (int i = 0; i < collRect.size(); i++) {
			if (coll && mRectang.getGlobalBounds().intersects(collRect[i]))
				mRectang.move(-((x * aSpeed) / distance), -((y * aSpeed) / distance));
		}
	}
}

bool Object::isCollisionLine(Object aObject) {
	bool collision = false;
	ToTheObject.setPointCount(4);
	ToTheObject.setPoint(0, mRectang.getPosition());
	ToTheObject.setPoint(1, Vector2f(mRectang.getPosition().x + 1, mRectang.getPosition().y));
	ToTheObject.setPoint(2, aObject.getPosition());
	ToTheObject.setPoint(3, Vector2f(aObject.getPosition().x, aObject.getPosition().y + 1));
	
	for (int i = 0; i < collRect.size(); i++) {
		if (ToTheObject.getGlobalBounds().intersects(collRect[i])) return true;
		else collision = false;
	}
	return collision;
}