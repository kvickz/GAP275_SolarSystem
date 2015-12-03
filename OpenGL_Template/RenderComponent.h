//RenderComponent.h

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameObjectComponent.h"

#include "Enums.h"
#include "Vector3.h"

#include <cml/cml.h>

class Mesh;
class Material;

typedef unsigned int GLuint;
typedef int GLint;
typedef std::pair<cml::matrix44f_c, GLint> TransformMatrixPair;

class RenderComponent : public GameObjectComponent
{
    Mesh* m_pMesh;
    Material* m_pMaterial;

    Vector3* m_translationReference;
    Vector3* m_rotationReference;
    Vector3* m_pScaleReference;

    TransformMatrixPair m_transformMatrixPair;
    GLint m_viewMatrixUniform;
    GLint m_projectionMatrixUniform;

    GLuint m_shaderProgram;

public:
    RenderComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform);
    ~RenderComponent();

    virtual void Init() override;
    virtual void Update() override;

    Mesh* Init(const char* fileName, Material* pMaterial);
    void Init(Mesh* pMesh, Material* pMaterial);
    void LoadMeshFromFile(const char* const fileName);
    void SetMesh(Mesh* pMesh);
    void LoadMaterial(Material* const pMaterial);
    void CreateProgram();
    void Draw();

    Material* const GetMaterial() { return m_pMaterial; }

    //Getters, still not 100% sure about this structure
    GLuint GetVBO();
    GLuint GetEBO();
    GLuint GetVAO();
    GLuint GetShaderProgram() { return m_shaderProgram; }

    //Matrices
    cml::matrix44f_c GetTransformMatrix() { return m_transformMatrixPair.first; }
    GLint GetTransformMatrixUniform() { return m_transformMatrixPair.second; }
    GLint GetProjectionMatrixUniform() { return m_projectionMatrixUniform; }
    GLint GetViewMatrixUniform() { return m_viewMatrixUniform; }

    std::vector<unsigned int> GetIndices();
};

#endif // !RENDERCOMPONENT_H