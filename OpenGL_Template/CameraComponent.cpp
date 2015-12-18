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
    , m_farClippingPlane(100000.f)
    , m_nearClippingPlane(0.1f)
    , m_fieldOfView(70.f)
    , m_moveSpeed(0.3f)
    , m_rotationSpeed(8000.f)
{
    m_viewMatrix.identity();
    m_projectionMatrix.identity();

    m_aspectRatio = pRenderer->GetAspectRatio();

    m_pTransformPosition = m_pTransform->GetPositionPointer();
    m_pTransformRotation = m_pTransform->GetRotationPointer();

    //josh's camera settings:
    m_cameraForward.set(0.0, 0.0, -1.0);
    m_cameraUp.set(0.0, 1.0, 0.0);
    m_cameraRight = cml::cross(m_cameraForward, m_cameraUp);    //Perpendicular to forward & up, right handed-coordinate
    m_cameraPosition.zero();
    m_cameraTransform.identity();
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
    //Get Delta time
    int deltaTime = m_pTime->GetDeltaTime();
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

//-------------------------------------------------------------------------------- -
// Yaw Pitch & Roll
//-------------------------------------------------------------------------------- -

void CameraComponent::Yaw(float degrees)
{
    //Creating yaw rotation marix from camUp & deltaDegrees
    cml::matrix44f_c yawMatrix;
    cml::matrix_rotation_axis_angle(yawMatrix, m_cameraUp, cml::rad(degrees * m_rotationSpeed));  

    //Concatenating camForward with the rotated matrix
    m_cameraForward = (yawMatrix * cml::vector4f(m_cameraForward, 0.0)).subvector(3);

    //Getting forward unit vector
    m_cameraForward.normalize();

    //Getting the perpendicular angle with cross product
    m_cameraRight = cml::cross(m_cameraForward, m_cameraUp);

    //Getting right unit vector
    m_cameraRight.normalize();


    UpdateTransform();
}

void CameraComponent::Pitch(float degrees)
{
    //Creating pitch rotation matrix from m_camRight
    cml::matrix44f_c pitchMatrix;
    cml::matrix_rotation_axis_angle(pitchMatrix, m_cameraRight, cml::rad(degrees * m_rotationSpeed));

    //The direction that the rotation turns in is in the direction of the inserted camera direction.
    //Yaw is rotation on    Y axis    cameraUP
    //Pitch is rotation on  X axis    cameraRIGHT
    //Roll is rotation on   Z axis    cameraFORWARD

    //Concatenating camForward with the rotated matrix
    m_cameraForward = (pitchMatrix * cml::vector4f(m_cameraForward, 0.0)).subvector(3);

    //Getting forward unit vector
    m_cameraForward.normalize();

    UpdateTransform();
}

void CameraComponent::Roll(float degrees)
{
    cml::matrix44f_c rollMatrix;
    cml::matrix_rotation_axis_angle(rollMatrix, m_cameraForward, cml::rad(degrees * m_rotationSpeed));

    //[???] This part is what im confused by, on the others as well
    m_cameraRight = (rollMatrix * cml::vector4f(m_cameraRight, 0.0)).subvector(3);  //I dont really understand what determines this direction

    //Get the right unit vector
    m_cameraRight.normalize();

    //Getting up direction from cross product or right & forward
    m_cameraUp = cml::cross(m_cameraRight, m_cameraForward);
    m_cameraUp.normalize();


    UpdateTransform();
}

void CameraComponent::MoveForward(float distance)
{
    distance *= m_moveSpeed;
    float x = m_cameraForward[0] * distance;
    float y = m_cameraForward[1] * distance;
    float z = m_cameraForward[2] * distance;

    m_pTransformPosition->Add(x, y, z);

    UpdateTransform();
}

void CameraComponent::MoveRight(float distance)
{
    distance *= m_moveSpeed;
    float x = m_cameraRight[0] * distance;
    float y = m_cameraRight[1] * distance;
    float z = m_cameraRight[2] * distance;

    m_pTransformPosition->Add(x, y, z);

    UpdateTransform();
}

void CameraComponent::MoveUp(float distance)
{
    distance *= m_moveSpeed;
    float x = m_cameraUp[0] * distance;
    float y = m_cameraUp[1] * distance;
    float z = m_cameraUp[2] * distance;

    m_pTransformPosition->Add(x, y, z);

    UpdateTransform();
}

void CameraComponent::UpdateTransform()
{
    cml::vector3f camPosition(m_pTransformPosition->x, m_pTransformPosition->y, m_pTransformPosition->z);
    cml::matrix_look_at_RH(m_viewMatrix, camPosition, camPosition + m_cameraForward, m_cameraUp);
}