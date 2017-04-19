#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/EntityDestroyer.h"

EntityDestroyer::EntityDestroyer(Entity* entity) :
    _entity(entity),
    _isPhysicalBodyDestroyed(false),
    _isViewDestroyed(false),
    _isLogicDestroyed(false)
{
    _body = entity->body();

    for (EntityView* view : ObjectCounter<EntityView>::objects())
        if (view->entity() == entity)
            _view = view;

    ObjectCounter<EntityDestroyer>::addObject(this);
}

EntityDestroyer::~EntityDestroyer()
{
    ObjectCounter<EntityDestroyer>::removeObject(this);
}

bool EntityDestroyer::isPhysicalBodyDestroyed() const
{
    return _isPhysicalBodyDestroyed;
}

void EntityDestroyer::setPhysicalDestroyed()
{
    _isPhysicalBodyDestroyed = true;
}

bool EntityDestroyer::isViewDestroyed() const
{
    return _isViewDestroyed;
}

void EntityDestroyer::setViewDestroyed()
{
    _isViewDestroyed = true;
}

bool EntityDestroyer::isLogicDestroyed() const
{
    return _isLogicDestroyed;
}

void EntityDestroyer::setLogicDestroyed()
{
    _isLogicDestroyed = true;
}

Entity* EntityDestroyer::entity() const
{
    return _entity;
}

b2Body* EntityDestroyer::body() const
{
    return _body;
}

EntityView* EntityDestroyer::view() const
{
    return _view;
}

void EntityDestroyer::destroyEntity()
{
    delete _entity;
    setLogicDestroyed();
}

void EntityDestroyer::destroyBody()
{
    World::physical().DestroyBody(_body);
    setPhysicalDestroyed();
}

void EntityDestroyer::destroyView()
{
    delete _view;
    setViewDestroyed();
}

void EntityDestroyer::destroy()
{
    destroyView();
    destroyEntity();
    destroyBody();
}
