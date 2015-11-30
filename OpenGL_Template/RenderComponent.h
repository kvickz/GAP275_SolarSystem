//RenderComponent.h

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameObjectComponent.h"

#include "Enums.h"

#include <cml/cml.h>
#include <vector>

class Mesh;
class Material;

typedef unsigned int GLuint;
typedef int GLint;
typedef std::pair<cml::matrix44f_c, GLint> TransformMatrixPair;
typedef std::pair<cml::matrix44f_c, GLint> MatrixUniformPair;

class RenderComponent : public GameObjectComponent
{
    Mesh* m_pMesh;
    Material* m_pMaterial;

    TransformMatrixPair m_transformMatrixPair;
    GLint m_viewMatrixUniform;
    GLint m_projectionMatrixUniform;

    GLuint m_shaderProgram;

    //TODO: Refactor, get a handle to Game's elapsed time var
    int m_elapsedTime = 0;

public:
    RenderComponent(const ComponentID id, GameObject* pGameObject);
    ~RenderComponent();

    virtual void Init() override;
    virtual void Update() override;

    void Init(const char* fileName, Material* pMaterial);
    void LoadMeshFromFile(const char* const fileName);
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