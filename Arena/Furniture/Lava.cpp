#include "Arena/Entity/Player.h"

#include "Arena/Furniture/Lava.h"

void Lava::testPlayerOnIt()
{
    try {
        b2Transform transform;
        transform.SetIdentity();
        if (_shapeB2.TestPoint(transform, Player::instance().body().GetPosition()))
            Player::instance().makeDamage(Player::instance().maxHealth()*0.005);
    }
    catch (Player::NoBodyException&)
    {
    }
}
