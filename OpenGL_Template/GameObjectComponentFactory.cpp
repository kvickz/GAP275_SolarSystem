//GameObjectComponentFactory.cpp

#include "GameObjectComponentFactory.h"

TransformComponent* GameObjectComponentFactory::CreateTransformComponent()
{
    TransformComponent* pComponent = new TransformComponent(k_transformComponentID);

    return pComponent;
}

RenderComponent* GameObjectComponentFactory::CreateRenderComponent()
{
    RenderComponent* pComponent = new RenderComponent(k_renderComponentID);
    //pComponent->LoadMeshFromFile("Sphere.obj");

    return pComponent;
}