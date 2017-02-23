#include "SensorContactListener.h"

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Game/World.h"

void SensorContactListener::BeginContact(b2Contact* contact)
{   
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureA()->GetBody(), true);

    if (bSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureB()->GetBody(), true);
}

void SensorContactListener::EndContact(b2Contact* contact)
{
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureA()->GetBody(), false);

    if (bSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureB()->GetBody(), false);
}

void SensorContactListener::setOnGround(b2Body* body, bool value)
{
    World& world = World::instance();
    if (&world.player().body() == body)
    {
        world.player().setOnGround(value);
        return;
    }
    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        if (&archer.body() == body)
        {
            archer.setOnGround(value);
            return;
        }
    }
}
