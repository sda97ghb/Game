#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Box2D/Dynamics/b2Body.h"

#include "Arena/Updatable.h"
#include "Arena/Entity/Evented.h"

class Entity : public Evented, public Updatable
{
public:
    EVENT(spawn)
    EVENT(death)
    EVENT(update)

    Entity();
    virtual ~Entity();

    const b2Vec2& position() const;
    void setPosition(float x, float y);

    virtual void update();

    b2Body* body() const;
    void setBody(b2Body* body);

    void markAsDeleted();
    bool inMarkedAsDeleted() const;

private:
    b2Body* _body;

    bool _isMarkedAsDeleted;
};

#endif // LIVINGENTITY_H
