#ifndef ENTITYDESTROYER_H
#define ENTITYDESTROYER_H

#include "Arena/Entity/Entity.h"
#include "Arena/Entity/EntityView.h"

class EntityDestroyer
{
public:
    EntityDestroyer(Entity* entity);
    ~EntityDestroyer();

    bool isPhysicalBodyDestroyed() const;
    void setPhysicalDestroyed();

    bool isViewDestroyed() const;
    void setViewDestroyed();

    bool isLogicDestroyed() const;
    void setLogicDestroyed();

    bool isDestroyed() const;

    Entity* entity() const;
    b2Body* body() const;
    EntityView* view() const;

    void destroyEntity();
    void destroyBody();
    void destroyView();

    void destroy();

private:
    Entity* _entity;
    b2Body* _body;
    EntityView* _view;

    bool _isPhysicalBodyDestroyed;
    bool _isViewDestroyed;
    bool _isLogicDestroyed;
};

#endif // ENTITYDESTROYER_H
