//RenderComponent.h

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameObjectComponent.h"

#include "Enums.h"

#include <vector>

class Mesh;
class Material;

typedef unsigned int GLuint;

class RenderComponent : public GameObjectComponent
{
    Mesh* m_pMesh;
    Material* m_pMaterial;

    GLuint m_shaderProgram;

public:
    RenderComponent(ComponentID id);
    ~RenderComponent();

    virtual void Update() override;

    void LoadMeshFromFile(const char* const fileName);
    void LoadMaterial(Material* const pMaterial);

    Material* const GetMaterial() { return m_pMaterial; }

    GLuint GetVBO();
    GLuint GetEBO();
    GLuint GetVAO();

    std::vector<unsigned int> GetIndices();
};

#endif // !RENDERCOMPONENT_H