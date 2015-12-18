//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"
#include "Macros.h"

GameObjectFactory::GameObjectFactory(Renderer* const pRenderer, Time* const pTime)
    :k_pRenderer(pRenderer)
    , k_pTime(pTime)
{
    m_pComponentFactory = new GameObjectComponentFactory();
}

GameObjectFactory::~GameObjectFactory()
{
    SAFE_DELETE(m_pComponentFactory);
}

GameObject* GameObjectFactory::CreateEmptyGameObject(Game* pGame)
{
    GameObject* pObject = new GameObject(k_emptyObjectID, pGame);
    
    //Add Transform Component
    TransformComponent* pTransform = m_pComponentFactory->CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    return pObject;
}

GameObject* GameObjectFactory::CreatePlanet(Game* pGame)
{
    GameObject* pObject = new GameObject(k_planetID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = m_pComponentFactory->CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = m_pComponentFactory->CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    //Add Planet Controller
    PlanetController* pPlanetController = m_pComponentFactory->CreatePlanetController(pObject, pTransform);
    pObject->AddComponent(k_planetComponentID, pPlanetController);

    return pObject;
}

GameObject* GameObjectFactory::CreateCamera(Game* pGame)
{
    GameObject* pObject = new GameObject(k_cameraID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = m_pComponentFactory->CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Camera Component
    CameraComponent* pCameraComponent = m_pComponentFactory->CreateCameraComponent(pObject, pTransform, k_pRenderer, k_pTime);
    pObject->AddComponent(k_cameraComponentID, pCameraComponent);

    return pObject;
}

GameObject* GameObjectFactory::CreatePointLight(Game* pGame)
{
    GameObject* pObject = new GameObject(k_pointLightID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = m_pComponentFactory->CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Point Light Component
    PointLightComponent* pPointLightComponent = m_pComponentFactory->CreatePointLightComponent(pObject, pTransform);
    pObject->AddComponent(k_pointLightComponentID, pPointLightComponent);

    return pObject;
}