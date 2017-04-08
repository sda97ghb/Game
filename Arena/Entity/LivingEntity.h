#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "Box2D/Dynamics/b2Body.h"

#include "Arena/Entity/Evented.h"

class LivingEntity : public Evented
{
public:
    EVENT(spawn)
    EVENT(death)
    EVENT(livingTick)

    LivingEntity();

    virtual float width() const;
    virtual float height() const;

    const b2Vec2& position() const;
    void setPosition(float x, float y);

    void spawn();

    void kill();

    void makeDamage(float damage);
    void heal(float health);

    bool isAlive() const;

    float maxHealth() const;
    void setMaxHealth(float maxHealth);

    float currentHealth() const;
    void setCurrentHealth(float currentHealth);

    virtual void update();

    b2Body* body() const;
    void setBody(b2Body* body);

private:
    float _maxHealth;
    float _currentHealth;

    b2Body* _body;
};

#endif // LIVINGENTITY_H
