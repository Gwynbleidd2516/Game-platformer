#ifndef OBJECT
#define OBJECT

#include<SFML/Graphics.hpp>
#include<math.h>
#include<vector>
using namespace sf;
using namespace std;

enum class Point{ Default, Centre};

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
	Point mPoint;

public:

	void setObject(Vector2f aVector, Color aColor, Point aPoint);

	void setPosition(float x, float y);

	void setSprite(Sprite aSprite);

	void setGravitation(bool Gr);

	void collision(FloatRect rect, bool col);

	void move(float x, float y);

	void setScale(float x, float y);

	void render(RenderWindow& wn, bool g);

	Vector2f getPosition();

	Vector2f getSize();

	FloatRect getGlobalBounds();

	bool isCollision(FloatRect aRect);

	float getDistanceTo(Vector2f aObject);

	void pursue(Vector2f aVector, float aSpeed);

	bool isCollisionLine(Object aObject);
};
#endif // !OBJECT