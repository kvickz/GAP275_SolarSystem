//RenderComponent.cpp

#include "RenderComponent.h"

#include "Mesh.h"
#include "Material.h"

RenderComponent::RenderComponent(ComponentID id)
    :GameObjectComponent(id)
    , m_pMesh(nullptr)
    , m_pMaterial(nullptr)
{
    //
}

RenderComponent::~RenderComponent()
{
    //TODO: Safe delete
    delete m_pMesh;
    m_pMesh = nullptr;

    delete m_pMaterial;
    m_pMaterial = nullptr;
}

void RenderComponent::Update()
{
    //Draw
}

void RenderComponent::LoadMeshFromFile(const char* const fileName)
{
    m_pMesh = new Mesh(fileName);
}

void RenderComponent::LoadMaterial(Material* const pMaterial)
{
    m_pMaterial = pMaterial;
}

void LoadShaderFromFile(const char* const fileName, const ShaderType type);

GLuint RenderComponent::GetVBO() { return m_pMesh->GetVBO(); }
GLuint RenderComponent::GetEBO() { return m_pMesh->GetEBO(); }
GLuint RenderComponent::GetVAO() { return m_pMesh->GetVAO(); }
std::vector<unsigned int> RenderComponent::GetIndices() { return m_pMesh->GetIndices(); }
