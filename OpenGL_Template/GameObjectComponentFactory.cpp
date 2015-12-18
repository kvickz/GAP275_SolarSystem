//GameObjectComponentFactory.cpp

#include "GameObjectComponentFactory.h"

TransformComponent* GameObjectComponentFactory::CreateTransformComponent(GameObject* pGameObject)
{
    TransformComponent* pComponent = new TransformComponent(k_transformComponentID, pGameObject);

    return pComponent;
}

RenderComponent* GameObjectComponentFactory::CreateRenderComponent(GameObject* pGameObject, TransformComponent* pTransform)
{
    RenderComponent* pComponent = new RenderComponent(k_renderComponentID, pGameObject, pTransform);
    //pComponent->LoadMeshFromFile("Sphere.obj");

    return pComponent;
}

CameraComponent* GameObjectComponentFactory::CreateCameraComponent(GameObject* pGameObject, TransformComponent* pTransform, Renderer* const pRenderer, Time* const pTime)
{
    CameraComponent* pComponent = new CameraComponent(k_cameraComponentID, pGameObject, pTransform, pRenderer, pTime);

    return pComponent;
}

PlanetController* GameObjectComponentFactory::CreatePlanetController(GameObject* pGameObject, TransformComponent* pTransform)
{
    PlanetController* pComponent = new PlanetController(pGameObject, pTransform);

    return pComponent;
}

PointLightComponent* GameObjectComponentFactory::CreatePointLightComponent(GameObject* pGameObject, TransformComponent* pTransform)
{
    PointLightComponent* pComponent = new PointLightComponent(pGameObject, pTransform);

    return pComponent;
}