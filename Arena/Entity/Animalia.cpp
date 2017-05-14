#include "Arena/ObjectCounter.h"
#include "Arena/Log.h"

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
//    return_if_deleted

    _currentHealth = 0.0f;
    callEventCallbacks(deathEvent);

    Log::instance().addMessage("Entity died.");
}

void Animalia::makeDamage(float damage)
{
//    return_if_deleted

    _currentHealth -= damage;
    if (_currentHealth <= 0.0f)
        kill();

    Log::instance().addMessage("Make damage: " + std::to_string(damage));
}

void Animalia::heal(float health)
{
//    return_if_deleted

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
//    return_if_deleted

    _currentHealth = currentHealth;
}

void Animalia::update()
{
//    return_if_deleted

    if (isAlive())
        callEventCallbacks(updateEvent);
}

Direction Animalia::lookingDirection() const
{
    return _lookingDirection;
}

void Animalia::setLookingDirection(const Direction& lookingDirection)
{
//    return_if_deleted

    _lookingDirection = lookingDirection;
}

float Animalia::maxHealth() const
{
    return _maxHealth;
}

void Animalia::setMaxHealth(float maxHealth)
{
//    return_if_deleted

    _maxHealth = maxHealth;
}
