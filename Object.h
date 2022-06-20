#ifndef OBJECT
#define OBJECT

#include<SFML/Graphics.hpp>
#include<math.h>
#include<vector>
using namespace sf;
using namespace std;

class Object {

private:
	RectangleShape mRectang;
	ConvexShape ToTheObject;
	Sprite mSprite;
	bool Gravitation = false;
	float GravitationSize = 10;
	bool coll = false;
	bool iscollision = false;
	float mObjectx = mRectang.getPosition().x;
	float mObjecty = mRectang.getPosition().y;
	vector<FloatRect> collRect;
	

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
			for (int i = 0; i < collRect.size(); i++) {
				if (mRectang.getGlobalBounds().intersects(collRect[i]) && coll == true) {
					mRectang.move(0, -GravitationSize);
					iscollision = true;
				}
				else iscollision = false;
			}
		}
	}

	void collision(FloatRect rect, bool col) {
		coll = col;
		collRect.push_back(rect);
		
	}

	void move(float x, float y) {
		mRectang.move(x, y);
		for (int i = 0; i < collRect.size(); i++) {
			if (mRectang.getGlobalBounds().intersects(collRect[i]) && coll == true) {
				mRectang.move(-x, -y);
			}
			else iscollision = false;
		}
	}

	void setScale(float x, float y) {
		mRectang.setScale(x, y);
		//if (x < 0)
			//mRectang.move(mRectang.getSize().x, 0);
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

	bool isCollision(FloatRect aRect) {
		if (mRectang.getGlobalBounds().intersects(aRect))
			iscollision = true;
		else
			iscollision = false;
		return iscollision;
	}

	float getDistanceTo(Vector2f aObject) {
		float x;
		float y;
		float distance;
		x = pow((aObject.x - mRectang.getPosition().x), 2);
		y = pow((aObject.y - mRectang.getPosition().y), 2);
		distance = x + y;
		return sqrt(distance);
	}

	void pursue(Vector2f aVector,float aSpeed) {
		float x = aVector.x - mRectang.getPosition().x;
		float y = aVector.y - mRectang.getPosition().y;
		float distance = sqrt(pow(x, 2) + pow(y, 2));
		if (distance > 1) {
			mRectang.move((x*aSpeed) / distance, (y*aSpeed) / distance);
			for (int i = 0; i < collRect.size(); i++) {
				if (coll && mRectang.getGlobalBounds().intersects(collRect[i]))
					mRectang.move(-((x*aSpeed) / distance), -((y*aSpeed) / distance));
			}
		}
	}

	bool isCollisionLine(Object aObject) {
		bool collision = false;
		float x = aObject.getPosition().x - mRectang.getPosition().x;
		float y = aObject.getPosition().y - mRectang.getPosition().y;
		float distance = sqrt(pow(x, 2) + pow(y, 2));
		ToTheObject.setPointCount(4);
		ToTheObject.setPoint(0, mRectang.getPosition());
		ToTheObject.setPoint(1, aObject.getPosition());
		ToTheObject.setPoint(2, Vector2f(aObject.getPosition().x, aObject.getPosition().y + 1));
		ToTheObject.setPoint(3, Vector2f(mRectang.getPosition().x + 1, mRectang.getPosition().y));
		for (int i = 0; i < collRect.size(); i++) {
			if (ToTheObject.getGlobalBounds().intersects(collRect[i])) return true;
			else collision = false;
		}
		return collision;
	}
};
#endif // !OBJECT
