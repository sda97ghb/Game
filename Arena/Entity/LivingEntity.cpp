#include <iostream>
#include "LivingEntity.h"

LivingEntity::LivingEntity() :
    _maxHealth(100.0f),
    _currentHealth(_maxHealth),
    _body(nullptr)
{}

float LivingEntity::width() const
{
    return 1.0f;
}

float LivingEntity::height() const
{
    return 1.0f;
}

const b2Vec2& LivingEntity::position() const
{
    return _body->GetPosition();
}

void LivingEntity::setPosition(float x, float y)
{
    body()->SetTransform(b2Vec2(x, y), body()->GetAngle());
}

void LivingEntity::spawn()
{
    callEventCallback(spawnEvent);
}

void LivingEntity::kill()
{
    _currentHealth = 0.0f;
    callEventCallback(deathEvent);
}

void LivingEntity::makeDamage(float damage)
{
    _currentHealth -= damage;
    if (_currentHealth <= 0.0f)
        kill();
}

void LivingEntity::heal(float health)
{
    _currentHealth += health;
}

bool LivingEntity::isAlive() const
{
    return _currentHealth > 0.0f;
}

float LivingEntity::currentHealth() const
{
    return _currentHealth;
}

void LivingEntity::setCurrentHealth(float currentHealth)
{
    _currentHealth = currentHealth;
}

float LivingEntity::maxHealth() const
{
    return _maxHealth;
}

void LivingEntity::setMaxHealth(float maxHealth)
{
    _maxHealth = maxHealth;
}

void LivingEntity::update()
{
    if (isAlive())
        callEventCallback(livingTickEvent);
}

b2Body* LivingEntity::body() const
{
    return _body;
}

void LivingEntity::setBody(b2Body* body)
{
    _body = body;
}
