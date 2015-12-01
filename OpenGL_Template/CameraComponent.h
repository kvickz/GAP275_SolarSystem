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

    float m_fieldOfView;
    float m_aspectRatio;
    float m_nearClippingPlane;
    float m_farClippingPlane;

    Vector3 m_velocity;
    Vector3 m_moveScale;
    float m_moveSpeed;

    Renderer* m_pRenderer;
    Time* m_pTime;

public:
    CameraComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform, Renderer* pRenderer, Time* pTime);
    ~CameraComponent();

    virtual void Init() override;
    virtual void Update() override;

    cml::matrix44f_c GetViewMatrix() { return m_viewMatrix; }
    cml::matrix44f_c GetProjectionMatrix() { return m_projectionMatrix; }

    void SetMovementScaleX(float value);
    void SetMovementScaleY(float value);
    void SetMovementScaleZ(float value);
};

#endif // !CAMERACOMPONENT_H
