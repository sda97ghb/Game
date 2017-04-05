#include "Box2D/Box2D.h"

#include "Arena/Entity/Enemy.h"
#include "Arena/Entity/Player.h"

bool Enemy::inaction()
{
    return false;
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

    b2Vec2 v = player.body().GetPosition() - body().GetPosition();
    v.Normalize();
    v *= 17.0f;

    b2RayCastInput input;
    input.p1 = body().GetPosition();
    input.p2 = input.p1 + v;
    input.maxFraction = 1.0f;
    int32 childIndex = 0;
    b2RayCastOutput output;

    float minFraction = 1000.0f; // Random big number
    b2Body* minBody = nullptr;
    for (b2Body* b = body().GetWorld()->GetBodyList();
         b != nullptr; b = b->GetNext())
    {
        if (b == &body())
            continue;
        for (b2Fixture* fixture = b->GetFixtureList();
             fixture != nullptr; fixture = fixture->GetNext())
        {
            if (fixture->RayCast(&output, input, childIndex))
                if (minFraction > output.fraction)
                {
                    minFraction = output.fraction;
                    minBody = b;
                }
        }
    }

    return minBody == &(player.body());
}

bool Enemy::isAbyssAhead()
{
    b2RayCastInput input;
    input.p1 = body().GetPosition();
    float dx = 0.0f;
    if (goingDirection() == GoingDirection::left)
        dx = -1.0f;
    else if (goingDirection() == GoingDirection::right)
        dx = 1.0f;
    input.p2 = input.p1 + b2Vec2(dx, -height() / 2.0 - 0.2);
    input.maxFraction = 1.0f;
    int32 childIndex = 0;
    b2RayCastOutput output;

    for (b2Body* b = body().GetWorld()->GetBodyList();
         b != nullptr; b = b->GetNext())
    {
        if (b == &body())
            continue;
        for (b2Fixture* fixture = b->GetFixtureList();
             fixture != nullptr; fixture = fixture->GetNext())
        {
            if (fixture->RayCast(&output, input, childIndex))
                return false;
        }
    }

    return true;
}

bool Enemy::isPlayerToLeft()
{
    return Player::instance().body().GetPosition().x < body().GetPosition().x;
}

void Enemy::lookForPlayer()
{
    if (canSeePlayer())
    {
        _lastSeenPosition = Player::instance().body().GetPosition();
        if (isPlayerToLeft())
            _goingDirection = GoingDirection::left;
        else
            _goingDirection = GoingDirection::right;
    }
}
