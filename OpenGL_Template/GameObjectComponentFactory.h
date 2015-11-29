//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

typedef unsigned int ComponentID;

const ComponentID k_transformComponentID = 1;
const ComponentID k_renderComponentID = 2;

class GameObjectComponentFactory
{
public:
    TransformComponent* CreateTransformComponent();
    RenderComponent* CreateRenderComponent();
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H
