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