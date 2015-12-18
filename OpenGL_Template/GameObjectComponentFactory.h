//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "PlanetController.h"
#include "PointLightComponent.h"

#include "Constants.h"

class GameObject;
class Renderer;
class Time;

class GameObjectComponentFactory
{
public:
    TransformComponent* CreateTransformComponent(GameObject* pGameObject);
    RenderComponent* CreateRenderComponent(GameObject* pGameObject, TransformComponent* pTransform);
    CameraComponent* CreateCameraComponent(GameObject* pGameObject, TransformComponent* pTransform, Renderer* const pRenderer, Time* const pTime);
    PlanetController* CreatePlanetController(GameObject* pGameObject, TransformComponent* pTransform);
    PointLightComponent* CreatePointLightComponent(GameObject* pGameObject, TransformComponent* pTransform);
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H