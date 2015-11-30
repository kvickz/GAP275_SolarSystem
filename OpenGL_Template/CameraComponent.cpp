//CameraComponent.cpp

#include "CameraComponent.h"

#include "TransformComponent.h"

#include <SDL.h>
#include "cml\cml.h"

CameraComponent::CameraComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(id, pGameObject, pTransform)
    , m_fieldOfView(70.f)
    , m_aspectRatio(800.f / 600.f) //TODO: Get this data from the Renderer class
    , m_nearClippingPlane(0.1f)
    , m_farClippingPlane(1000.f)
{
    m_viewMatrix.identity();
    m_projectionMatrix.identity();
}

CameraComponent::~CameraComponent()
{
    //
}

void CameraComponent::Init()
{
    //Setting camera position
    m_pTransform->SetPosition(0.f, 0.5f, 0.f);

    //Draw in perspective
    cml::matrix_perspective_xfov_RH(m_projectionMatrix
                                    , m_fieldOfView
                                    , m_aspectRatio
                                    , m_nearClippingPlane
                                    , m_farClippingPlane
                                    , cml::z_clip_neg_one);
}

void CameraComponent::Update()
{
    float x = sinf(SDL_GetTicks() * 0.001f) * 5.f;
    float y = cosf(SDL_GetTicks() * 0.001f) * 5.f;
    float z = 0;
    m_pTransform->SetPosition(x, y, z);

    //Set camera position and target
    cml::vector3f cameraDirection(0.f, 0.f, -1.f);
    cml::vector3f cameraPosition(m_pTransform->GetPosition().x
                                 , m_pTransform->GetPosition().y
                                 , m_pTransform->GetPosition().z);

    /*m_cameraPosition[0] = m_pTransform->GetPosition().x;
    m_cameraPosition[1] = m_pTransform->GetPosition().y;
    m_cameraPosition[2] = m_pTransform->GetPosition().z;*/

    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                       //Origin
                           , cameraPosition + cameraDirection     //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));         //Up-Direction, Y is up
}