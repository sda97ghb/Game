#include "Arena/Audio.h"

#include "Arena/Attacks/BowAttack.h"

#include "Arena/Entity/Animalia.h"

BowAttack& BowAttack::setDamage(float damage)
{
    _arrowBuilderSpawner.setDamage(damage);
    return *this;
}

BowAttack& BowAttack::setDirection(float angle)
{
    _arrowBuilderSpawner.setDirection(angle);
    return *this;
}

BowAttack& BowAttack::setPosition(const b2Vec2& position)
{
    _arrowBuilderSpawner.setPosition(position);
    return *this;
}

BowAttack& BowAttack::setPosition(float x, float y)
{
    _arrowBuilderSpawner.setPosition(x, y);
    return *this;
}

BowAttack& BowAttack::setSpeed(float speed)
{
    _arrowBuilderSpawner.setSpeed(speed);
    return *this;
}

BowAttack&BowAttack::setTarget(const b2Vec2& position)
{
    _arrowBuilderSpawner.setTarget(position);
    return *this;
}

BowAttack& BowAttack::setActor(Animalia* actor)
{
    Attack::setActor(actor);

    b2Vec2 actorPos = actor->body()->GetPosition();

    if (actor->lookingDirection() == Direction::left)
        setPosition(actorPos.x - 1.0f, actorPos.y);
    else // looking direction is at right
        setPosition(actorPos.x + 1.0f, actorPos.y);

    return *this;
}

BowAttack& BowAttack::setActor(Animalia& actor)
{
    return setActor(&actor);
}

BowAttack& BowAttack::setTarget(Animalia* target)
{
    _arrowBuilderSpawner.setTarget(target->body()->GetPosition());
    return *this;
}

BowAttack& BowAttack::setTarget(Animalia& target)
{
    return setTarget(&target);
}

void BowAttack::perform()
{
    _arrowBuilderSpawner.spawn();
    Audio::instance().playSound("Audio/bowAttack.ogg");
}
