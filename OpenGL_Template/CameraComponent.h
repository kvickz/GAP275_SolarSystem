//CameraComponent.h

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "GameObjectComponent.h"

#include "Constants.h"
#include "Vector3.h"

#include <cml/cml.h>

class Renderer;
class Time;

class CameraComponent : public GameObjectComponent
{
private:
    cml::matrix44f_c m_viewMatrix;
    cml::matrix44f_c m_projectionMatrix;

    bool m_boosting;

    float m_fieldOfView;
    float m_aspectRatio;
    float m_nearClippingPlane;
    float m_farClippingPlane;

    Vector3* m_pTransformPosition;
    Vector3* m_pTransformRotation;
    Vector3 m_velocity;
    Vector3 m_rotationalVelocity;
    float m_moveSpeed;
    float m_rotationSpeed;

    Renderer* m_pRenderer;
    Time* m_pTime;

    //From josh's camera:
    cml::vector3f m_cameraForward;
    cml::vector3f m_cameraRight;
    cml::vector3f m_cameraUp;
    cml::vector3f m_cameraPosition;
    cml::matrix44f_c m_cameraTransform;

public:
    CameraComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform, Renderer* pRenderer, Time* pTime);
    ~CameraComponent();

    virtual void Init() override;
    virtual void Update() override;

    cml::matrix44f_c GetViewMatrix() { return m_viewMatrix; }
    cml::matrix44f_c GetProjectionMatrix() { return m_projectionMatrix; }

    void MoveForward(float distance);
    void MoveRight(float distance);
    void MoveUp(float distance);

    void Yaw(float degrees);
    void Pitch(float degrees);
    void Roll(float degrees);

    void Boost();

private:
    void UpdateTransform();

};

#endif // !CAMERACOMPONENT_H
