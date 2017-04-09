#include <iostream>

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/Entity/TestFinalEntity.h"

#include "Arena/World.h"

TestFinalEntity::TestFinalEntity()
{
    setEventCallback(spawnEvent, METHOD_CALLBACK(onSpawn));
    setEventCallback(deathEvent, METHOD_CALLBACK(onDeath));
    setEventCallback(updateEvent, METHOD_CALLBACK(onLivingUpdate));

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
//    std::cout << "I'm alive! I have " << currentHealth() << "hp." << std::endl;
    makeDamage(0.1f);
}

void TestFinalEntity::onGroundHit(float speed)
{
    makeDamage(speed);
    std::cout << "Hit!" << std::endl;
}
