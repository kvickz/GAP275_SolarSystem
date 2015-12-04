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
    , m_moveSpeed(0.02f)
    , m_rotationSpeed(0.02f)
{
    m_viewMatrix.identity();
    m_projectionMatrix.identity();

    m_aspectRatio = pRenderer->GetAspectRatio();

    m_pTransformPosition = m_pTransform->GetPositionPointer();
    m_pTransformRotation = m_pTransform->GetRotationPointer();
}

CameraComponent::~CameraComponent()
{
    m_pTransformPosition = nullptr;
    m_pTransformRotation = nullptr;
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

    //---------------------------------------------------------------------------------- -
    //  Modifying m_pTransform
    //---------------------------------------------------------------------------------- -
    //Update Velocity
    m_velocity.SetValue(m_moveSpeed * m_moveScale.x * deltaTime
                        , m_moveSpeed * m_moveScale.y * deltaTime
                        , m_moveSpeed * m_moveScale.z * deltaTime);

    //Update Rotational Velocity
    m_rotationalVelocity.SetValue(m_rotationSpeed * m_rotationScale.x * deltaTime
                                  , m_rotationSpeed* m_rotationScale.y * deltaTime
                                  , m_rotationSpeed * m_rotationScale.z * deltaTime);

    //Update Position & Rotation inside transform component
    m_pTransform->Translate(m_velocity.x, m_velocity.y, m_velocity.z);
    m_pTransform->Rotate(m_rotationalVelocity.x, m_rotationalVelocity.y, m_rotationalVelocity.z);

    //---------------------------------------------------------------------------------- -
    //  Modifying the camera with modified transform component
    //---------------------------------------------------------------------------------- -

    //Set camera position and target
    cml::matrix44f_c cameraRotationMatrix;
    cml::matrix_rotation_euler(cameraRotationMatrix
                               , m_pTransformRotation->x
                               , m_pTransformRotation->y
                               , m_pTransformRotation->z
                               , cml::EulerOrder::euler_order_xyz);

    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraRotationMatrix * cameraForward).subvector(3);

    //Setting Camera Position
    cml::vector3f cameraPosition(m_pTransformPosition->x
                                 , m_pTransformPosition->y
                                 , m_pTransformPosition->z);

    //Setting Rotation
    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                       //Origin
                           , cameraPosition + cameraDirection     //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));         //Up-Direction, Y is up
}

//-------------------------------------------------------------------------------- -
// Setting Movement Scale
//-------------------------------------------------------------------------------- -
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

//-------------------------------------------------------------------------------- -
// Setting Rotation Scale
//-------------------------------------------------------------------------------- -
void CameraComponent::SetRotationScaleX(float value)
{
    m_rotationScale.x = value;
}

void CameraComponent::SetRotationScaleY(float value)
{
    m_rotationScale.y = value;
}

void CameraComponent::SetRotationScaleZ(float value)
{
    m_rotationScale.z = value;
}