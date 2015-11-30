//CameraComponent.h

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "GameObjectComponent.h"

#include "Constants.h"

#include <cml/cml.h>

class CameraComponent : public GameObjectComponent
{
private:
    cml::matrix44f_c m_viewMatrix;
    cml::matrix44f_c m_projectionMatrix;

    float m_fieldOfView;
    float m_aspectRatio;
    float m_nearClippingPlane;
    float m_farClippingPlane;

public:
    CameraComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform);
    ~CameraComponent();

    virtual void Init() override;
    virtual void Update() override;

    cml::matrix44f_c GetViewMatrix() { return m_viewMatrix; }
    cml::matrix44f_c GetProjectionMatrix() { return m_projectionMatrix; }
};

#endif // !CAMERACOMPONENT_H
