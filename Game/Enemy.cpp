#include "Game/Enemy.h"

#include "Game/Player.h"
#include "Box2D/Box2D.h"

void Enemy::update()
{
	if(canSeePlayer) aggression();
	else inaction();
}

bool Enemy::inaction()
{

}

void Enemy::going()
{

}

bool Enemy::aggression()
{
	Player& player = Player::instance();
	
		body().SetTransform(player.body().GetPosition(),body().GetAngle());
		return true;
	

}

bool Enemy::canSeePlayer()
{
	Player& player = Player::instance();
	
	b2Transform transform;
	transform.SetIdentity();
	b2RayCastInput input;
	input.p1 = body().GetPosition();
	input.p2 = player.body().GetPosition();
	input.maxFraction = 1.0f;
	int32 childIndex = 0;
	b2RayCastOutput output;
	b2Fixture& fixture = player.body().GetFixtureList()[0];
	bool hit = fixture.GetShape()->RayCast(&output, input, transform, childIndex);
	
	return hit;
}

