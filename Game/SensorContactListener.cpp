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

    if (aSensorType == LEFT_SENSOR_TYPE)
        setLeftContact(contact->GetFixtureA()->GetBody(), true);

    if (bSensorType == LEFT_SENSOR_TYPE)
        setLeftContact(contact->GetFixtureB()->GetBody(), true);

    if (aSensorType == RIGHT_SENSOR_TYPE)
        setRightContact(contact->GetFixtureA()->GetBody(), true);

    if (bSensorType == RIGHT_SENSOR_TYPE)
        setRightContact(contact->GetFixtureB()->GetBody(), true);
}

void SensorContactListener::EndContact(b2Contact* contact)
{
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureA()->GetBody(), false);

    if (bSensorType == GROUND_SENSOR_TYPE)
        setOnGround(contact->GetFixtureB()->GetBody(), false);

    if (aSensorType == LEFT_SENSOR_TYPE)
        setLeftContact(contact->GetFixtureA()->GetBody(), false);

    if (bSensorType == LEFT_SENSOR_TYPE)
        setLeftContact(contact->GetFixtureB()->GetBody(), false);

    if (aSensorType == RIGHT_SENSOR_TYPE)
        setRightContact(contact->GetFixtureA()->GetBody(), false);

    if (bSensorType == RIGHT_SENSOR_TYPE)
        setRightContact(contact->GetFixtureB()->GetBody(), false);
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

void SensorContactListener::setLeftContact(b2Body* body, bool value)
{
    World& world = World::instance();
    if (&world.player().body() == body)
    {
        world.player().setLeftContact(value);
        return;
    }
    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        if (&archer.body() == body)
        {
            archer.setLeftContact(value);
            return;
        }
    }
}

void SensorContactListener::setRightContact(b2Body* body, bool value)
{
    World& world = World::instance();
    if (&world.player().body() == body)
    {
        world.player().setRightContact(value);
        return;
    }
    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        if (&archer.body() == body)
        {
            archer.setRightContact(value);
            return;
        }
    }
}
