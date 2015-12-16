//TransformComponent.h

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GameObjectComponent.h"

#include "Vector3.h"
#include <cml/cml.h>
#include <vector>

typedef int GLint;

class TransformComponent : public GameObjectComponent
{
private:
    TransformComponent* m_pParent;
    std::vector<TransformComponent*> m_children;

    cml::matrix44f_c m_transformMatrix;

    Vector3 m_position;
    Vector3 m_eulerRotation;
    Vector3 m_scale;

public:
    TransformComponent(const ComponentID id, GameObject* pGameObject);
    ~TransformComponent();

    virtual void Update() override;

    void SetParent(TransformComponent* const pTransform);
    void AddChild(TransformComponent* const pTransform);
    TransformComponent* GetChild(const unsigned int index);

    //Position
    Vector3 GetPosition() { return m_position; }
    Vector3 GetWorldPosition();
    Vector3* GetPositionPointer() { return &m_position; }
    void SetPosition(float x, float y, float z);
    void Translate(float x, float y, float z);

    //Rotation
    Vector3 GetRotation() { return m_eulerRotation; }
    Vector3 GetWorldRotation();
    Vector3* GetRotationPointer() { return &m_eulerRotation; }
    void SetEulerRotation(float x, float y, float z);
    void Rotate(float x, float y, float z);

    //Scale
    Vector3 GetScale() { return m_scale; }
    Vector3* GetScalePointer() { return &m_scale; }
    void SetScale(float x, float y, float z);
    void Scale(float x, float y, float z);

    //Transform Matrix
    cml::matrix44f_c GetTransformMatrix() const { return m_transformMatrix; }
    cml::matrix44f_c GetWorldTransformMatrix() const;

private:
    void CalculateTransforMatrix();
};

#endif // !TRANSFORMCOMPONENT_H