#include "Arena/World.h"

#include "Arena/Entity/Player.h"

#include "Arena/Furniture/Lava.h"

void Lava::testPlayerOnIt()
{
    try
    {
        {
            Player* player1 = World::instance().player1();
            b2Transform transform;
            transform.SetIdentity();
            if (_shapeB2.TestPoint(transform, player1->body()->GetPosition()))
                player1->makeDamage(player1->maxHealth() * 0.005);
        }
        {
            Player* player2 = World::instance().player2();
            b2Transform transform;
            transform.SetIdentity();
            if (_shapeB2.TestPoint(transform, player2->body()->GetPosition()))
                player2->makeDamage(player2->maxHealth() * 0.005);
        }
    }
    catch (...)
    {
    }
}
