#include <math.h>

#include "SFML/Window/Keyboard.hpp"

#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/Log.h"
#include "Game/Spikes.h"
#include "Game/Player.h"

Spikes::Spikes() :
_x1(0.0f),
_y1(0.0f),
_x2(1.0f),
_y2(0.0f),
_height(0.5f)
{
}

void Spikes::setCoordinates(float x1, float y1, float x2, float y2)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
	setShape();
}

void Spikes::setHeight(float height)
{
	_height = height;
	setShape();
}

void Spikes::testPlayerOnIt()
{
	try 
	{
		Player& player = Player::instance();
		b2Body& body = player.body();
		b2Transform transform;
		transform.SetIdentity();
		if (_shapeB2.TestPoint(transform, player.footPosition()))
		{
			static int n = 0;
			Log::instance().push(std::to_string(n++));
		}
	}
	catch (Player::NoBodyException&)
	{
	}

}

float Spikes::x1() const
{
    return _x1;
}

float Spikes::x2() const
{
    return _x2;
}

float Spikes::y1() const
{
    return _y1;
}

float Spikes::y2() const
{
    return _y2;
}

float Spikes::height() const
{
	return _height;
}
float Spikes::lenght() const
{
	return b2Vec2(_x2 - _x1, _y2 - _y1).Length();
}

float Spikes::sign(float sign) const
{
	return 0 < sign ? 1.0f : -1.0f;
}

float Spikes::angle() const
{
	float w = _x2 - _x1;
	float h = _y2 - _y1;
	return std::acosf(w / lenght()) *
		   sign(std::asinf(h / lenght()));
}

b2PolygonShape& Spikes::shapeB2()
{
	return _shapeB2;
}

const b2PolygonShape& Spikes::shapeB2() const
{
	return _shapeB2;
}

sf::RectangleShape& Spikes::shapeSF()
{
	return _shapeSF;
}

const sf::RectangleShape& Spikes::shapeSF() const
{
	return _shapeSF;
}

void Spikes::setShape()
{
	b2Vec2 vertexes[4] = { b2Vec2(_x1, _y1),
						   b2Vec2(_x2, _y2),
						   b2Vec2(-std::sin(angle()) * _height + _x2,
								   std::cos(angle()) * _height + _y2),
						   b2Vec2(-std::sin(angle()) * _height + _x1, 
								   std::cos(angle()) * _height + _y1) };


	_shapeB2.Set(vertexes, 4);
}