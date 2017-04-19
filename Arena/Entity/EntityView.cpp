#include "Arena/ObjectCounter.h"

#include "Arena/Entity/EntityView.h"

EntityView::EntityView()
{
    ObjectCounter<EntityView>::addObject(this);
}

EntityView::~EntityView()
{
    ObjectCounter<EntityView>::removeObject(this);
}
