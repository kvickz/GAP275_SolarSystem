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

class RenderComponent : public GameObjectComponent
{
    Mesh* m_pMesh;
    Material* m_pMaterial;

    TransformMatrixPair m_transformMatrixPair;
    GLuint m_shaderProgram;

    //TODO: Refactor, get a handle to Game's elapsed time var
    int m_elapsedTime = 0;

public:
    RenderComponent(ComponentID id);
    ~RenderComponent();

    virtual void Init() override;
    virtual void Update() override;

    void LoadMeshFromFile(const char* const fileName);
    void LoadMaterial(Material* const pMaterial);
    void CreateProgram();

    Material* const GetMaterial() { return m_pMaterial; }

    GLuint GetVBO();
    GLuint GetEBO();
    GLuint GetVAO();
    GLuint GetShaderProgram() { return m_shaderProgram; }
    cml::matrix44f_c GetTransformMatrix() { return m_transformMatrixPair.first; }
    GLint GetTransformMatrixUniform() { return m_transformMatrixPair.second; }

    std::vector<unsigned int> GetIndices();
};

#endif // !RENDERCOMPONENT_H