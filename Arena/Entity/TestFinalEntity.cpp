#include <iostream>

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/Entity/TestFinalEntity.h"

#include "Arena/World.h"

TestFinalEntity::TestFinalEntity() :
    _lookingDirection(Direction::left)
{
    setEventCallback(spawnEvent, CALLBACK_METHOD(onSpawn));
    setEventCallback(deathEvent, CALLBACK_METHOD(onDeath));
    setEventCallback(livingTickEvent, CALLBACK_METHOD(onLivingUpdate));

    setMaxHealth(50.0f);
    setCurrentHealth(maxHealth());
}

void TestFinalEntity::onSpawn()
{
    std::cout << "I was born!" << std::endl;
}

void TestFinalEntity::onDeath()
{
    std::cout << "Rust in peace TestFinalEntity..." << std::endl;
}

void TestFinalEntity::onLivingUpdate()
{
    std::cout << "I'm alive! I have " << currentHealth() << "hp." << std::endl;
    makeDamage(0.1f);
}

void TestFinalEntity::onGroundHit(float speed)
{
    makeDamage(speed);
    std::cout << "Hit!" << std::endl;
}
