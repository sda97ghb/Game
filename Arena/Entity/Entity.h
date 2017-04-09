#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Box2D/Dynamics/b2Body.h"

#include "Arena/Entity/Evented.h"

class Entity : public Evented
{
public:
    EVENT(spawn)
    EVENT(death)
    EVENT(update)

    Entity();
    virtual ~Entity() = default;

    const b2Vec2& position() const;
    void setPosition(float x, float y);

    virtual void update();

    b2Body* body() const;
    void setBody(b2Body* body);

private:
    b2Body* _body;
};

#endif // LIVINGENTITY_H
