//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include "Constants.h"

class GameObject;

class GameObjectComponentFactory
{
public:
    TransformComponent* CreateTransformComponent(GameObject* pGameObject);
    RenderComponent* CreateRenderComponent(GameObject* pGameObject);
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H