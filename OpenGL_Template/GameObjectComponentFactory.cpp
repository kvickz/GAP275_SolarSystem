//GameObjectComponentFactory.cpp

#include "GameObjectComponentFactory.h"

TransformComponent* GameObjectComponentFactory::CreateTransformComponent(GameObject* pGameObject)
{
    TransformComponent* pComponent = new TransformComponent(k_transformComponentID, pGameObject);

    return pComponent;
}

RenderComponent* GameObjectComponentFactory::CreateRenderComponent(GameObject* pGameObject)
{
    RenderComponent* pComponent = new RenderComponent(k_renderComponentID, pGameObject);
    //pComponent->LoadMeshFromFile("Sphere.obj");

    return pComponent;
}

CameraComponent* GameObjectComponentFactory::CreateCameraComponent(GameObject* pGameObject)
{
    CameraComponent* pComponent = new CameraComponent(k_cameraComponentID, pGameObject);

    return pComponent;
}