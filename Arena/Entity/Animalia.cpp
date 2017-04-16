#include "Arena/ObjectCounter.h"

#include "Arena/Entity/Animalia.h"

Animalia::Animalia() :
    _maxHealth(100.0f),
    _currentHealth(_maxHealth),
    _lookingDirection(Direction::left)
{
    ObjectCounter<Animalia>::addObject(this);
}

Animalia::~Animalia()
{
    ObjectCounter<Animalia>::removeObject(this);
}

void Animalia::kill()
{
    _currentHealth = 0.0f;
    callEventCallback(deathEvent);
}

void Animalia::makeDamage(float damage)
{
    _currentHealth -= damage;
    if (_currentHealth <= 0.0f)
        kill();
}

void Animalia::heal(float health)
{
    _currentHealth += health;
}

bool Animalia::isAlive() const
{
    return _currentHealth > 0.0f;
}

float Animalia::currentHealth() const
{
    return _currentHealth;
}

void Animalia::setCurrentHealth(float currentHealth)
{
    _currentHealth = currentHealth;
}

void Animalia::update()
{
    if (isAlive())
        callEventCallback(updateEvent);
}

Direction Animalia::lookingDirection() const
{
    return _lookingDirection;
}

void Animalia::setLookingDirection(const Direction& lookingDirection)
{
    _lookingDirection = lookingDirection;
}

float Animalia::maxHealth() const
{
    return _maxHealth;
}

void Animalia::setMaxHealth(float maxHealth)
{
    _maxHealth = maxHealth;
}
