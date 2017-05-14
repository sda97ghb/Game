#include "Stream.h"

#include "Arena/Audio.h"

#include "Arena/ObjectCounter.h"

#include "Arena/Attacks/SwordAttack.h"

#include "Arena/Entity/Animalia.h"

SwordAttack::SwordAttack() :
    _damage{0.0f},
    _distance{1.0f}
{
}

SwordAttack& SwordAttack::setActor(Animalia* animalia)
{
    Attack::setActor(animalia);
    return *this;
}

SwordAttack& SwordAttack::setActor(Animalia& animalia)
{
    return setActor(&animalia);
}

SwordAttack& SwordAttack::setDamage(float damage)
{
    _damage = damage;
    return *this;
}

SwordAttack& SwordAttack::setDistance(float distance)
{
    _distance = distance;
    return *this;
}

void SwordAttack::perform()
{
    using namespace stream;
    using namespace stream::op;

    auto isOnProperSide = [&](Animalia* animalia)
    {
        bool isOnLeftSide = animalia->body()->GetPosition().x <
                            _actor->body()->GetPosition().x;
        return (_actor->lookingDirection() == Direction::left  &&  isOnLeftSide) ||
               (_actor->lookingDirection() == Direction::right && !isOnLeftSide);
    };

    auto isOnProperDistance = [&](Animalia* animalia)
    {
        float d = animalia->body()->GetPosition().x -
                  _actor->body()->GetPosition().x;
        if (d < 0)
            d *= -1.0f;
        return d <= _distance;
    };

    auto isNotActor = [&](Animalia* animalia)
    {
        return animalia != _actor;
    };

    MakeStream::from(ObjectCounter<Animalia>::objects()) |
        filter(isOnProperSide) |
        filter(isOnProperDistance) |
        filter(isNotActor) |
        for_each([&](Animalia* animalia)
        {
            animalia->makeDamage(_damage);
        });

    Audio::instance().playSound("Audio/swordAttack.ogg");
}
