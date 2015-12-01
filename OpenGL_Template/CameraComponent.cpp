//CameraComponent.cpp

#include "CameraComponent.h"

#include "Time.h"
#include "TransformComponent.h"
#include "Renderer.h"

#include <SDL.h>
#include "cml\cml.h"

CameraComponent::CameraComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform, Renderer* pRenderer, Time* pTime)
    :GameObjectComponent(id, pGameObject, pTransform)
    , m_pRenderer(pRenderer)
    , m_pTime(pTime)
    , m_farClippingPlane(1000.f)
    , m_nearClippingPlane(0.1f)
    , m_fieldOfView(70.f)
    , m_moveSpeed(0.1f)
{
    m_viewMatrix.identity();
    m_projectionMatrix.identity();

    m_aspectRatio = pRenderer->GetAspectRatio();
}

CameraComponent::~CameraComponent()
{
    //
}

void CameraComponent::Init()
{
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
    //Reset Movement Scale
    //m_moveScale.Zero();

    //Get Delta time
    int deltaTime = m_pTime->GetDeltaTime();

    //Update Velocity
    m_velocity.SetValue(m_moveSpeed * m_moveScale.x * deltaTime
                   , m_moveSpeed * m_moveScale.y * deltaTime
                   , m_moveSpeed * m_moveScale.z * deltaTime);

    //Update Position
    m_pTransform->Translate(m_velocity.x, m_velocity.y, m_velocity.z);

    //Set camera position and target
    cml::vector3f cameraDirection(0.f, 0.f, -1.f);
    cml::vector3f cameraPosition(m_pTransform->GetPosition().x
                                 , m_pTransform->GetPosition().y
                                 , m_pTransform->GetPosition().z);

    //Setting Rotation
    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                       //Origin
                           , cameraPosition + cameraDirection     //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));         //Up-Direction, Y is up
}

void CameraComponent::SetMovementScaleX(float value)
{
    m_moveScale.x = value;
}

void CameraComponent::SetMovementScaleY(float value)
{
    m_moveScale.y = value;
}

void CameraComponent::SetMovementScaleZ(float value)
{
    m_moveScale.z = value;
}