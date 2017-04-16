#ifndef ANIMALIA_H
#define ANIMALIA_H

#include "Arena/Direction.h"

#include "Arena/Entity/Entity.h"

class Animalia : public Entity
{
public:
    Animalia();
    virtual ~Animalia();

    void kill();

    void makeDamage(float damage);
    void heal(float health);

    bool isAlive() const;

    float maxHealth() const;
    void setMaxHealth(float maxHealth);

    float currentHealth() const;
    void setCurrentHealth(float currentHealth);

    virtual void update();

    Direction lookingDirection() const;
    void setLookingDirection(const Direction& lookingDirection);

private:
    float _maxHealth;
    float _currentHealth;

    Direction _lookingDirection;
};

#endif // ANIMALIA_H
