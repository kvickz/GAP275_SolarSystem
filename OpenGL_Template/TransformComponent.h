//TransformComponent.h

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GameObjectComponent.h"

#include "Vector3.h"

class TransformComponent : public GameObjectComponent
{
private:
    Vector3 m_position;
    Vector3 m_eulerRotation;
    Vector3 m_scale;

public:
    TransformComponent(const ComponentID id, GameObject* pGameObject);
    ~TransformComponent();

    virtual void Update() override;

    //Position
    Vector3 GetPosition() { return m_position; }
    Vector3* GetPositionRef() { return &m_position; }
    void SetPosition(float x, float y, float z);
    void Translate(float x, float y, float z);

    //Rotation
    Vector3 GetRotation() { return m_eulerRotation; }
    Vector3* GetRotationRef() { return &m_eulerRotation; }
    void SetEulerRotation(float x, float y, float z);
    void Rotate(float x, float y, float z);

    //Scale
    Vector3 GetScale() { return m_scale; }
    Vector3* GetScalePointer() { return &m_scale; }
    void SetScale(float x, float y, float z);
    void Scale(float x, float y, float z);
};

#endif // !TRANSFORMCOMPONENT_H