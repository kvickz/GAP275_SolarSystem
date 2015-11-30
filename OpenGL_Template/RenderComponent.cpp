//RenderComponent.cpp

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Mesh.h"
#include "Material.h"

#include <SDL.h>

RenderComponent::RenderComponent(ComponentID id, GameObject* pGameObject)
    :GameObjectComponent(id, pGameObject)
    , m_pMesh(nullptr)
    , m_pMaterial(nullptr)
    , m_elapsedTime(0)
{
    //Initialize to 1, 1, 1
    m_transformMatrixPair.first.identity();
}

RenderComponent::~RenderComponent()
{
    //TODO: Safe delete
    delete m_pMesh;
    m_pMesh = nullptr;

    //TODO: This shouldn't be deleted by the render component
    //      I need some kind of separate manager to handle shared materials
    delete m_pMaterial;
    m_pMaterial = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Render Component Initialization Function
//      -Default initialization, call the overloaded function for more functionality 
//-------------------------------------------------------------------------------------- -
void RenderComponent::Init()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Render Component Initialization Function
//      -Allows you to set the mesh and material of this component
//-------------------------------------------------------------------------------------- -
void RenderComponent::Init(const char* fileName, Material* pMaterial)
{
    LoadMeshFromFile(fileName);
    LoadMaterial(pMaterial);
    CreateProgram();
}

//-------------------------------------------------------------------------------------- -
//  Load Mesh From File Function
//      -Will load a mesh from a given file path
//-------------------------------------------------------------------------------------- -
void RenderComponent::Update()
{
    float sinVal = sinf(SDL_GetTicks() * 0.001f);

    //Rotation and translation of the object
    cml::matrix44f_c objectRotation;
    cml::matrix44f_c objectTranslation;

    objectRotation.identity();
    cml::matrix_rotate_about_local_y(objectRotation, (SDL_GetTicks() * 0.001f));
    //cml::matrix_translation(objectTranslation, 0.f, (sinVal * 0.05f), -2.f);
    //TODO: Modify this based on transform's position

    float x = m_pGameObject->GetTransformComponent()->GetPosition().x;
    float y = m_pGameObject->GetTransformComponent()->GetPosition().y;
    float z = m_pGameObject->GetTransformComponent()->GetPosition().z;

    cml::matrix_translation(objectTranslation, x, y, z);

    m_transformMatrixPair.first = (objectTranslation * objectRotation);
}

//-------------------------------------------------------------------------------------- -
//  Load Mesh From File Function
//      -Will load a mesh from a given file path
//-------------------------------------------------------------------------------------- -
void RenderComponent::LoadMeshFromFile(const char* const fileName)
{
    m_pMesh = new Mesh(fileName);
}

//-------------------------------------------------------------------------------------- -
//  Load Material Function
//      -Loads a given material
//-------------------------------------------------------------------------------------- -
void RenderComponent::LoadMaterial(Material* const pMaterial)
{
    m_pMaterial = pMaterial;
}

//-------------------------------------------------------------------------------------- -
//  Create Program Function
//      -Will create a program and link shaders to it
//      -Also handles late-phase of buffer binding
//-------------------------------------------------------------------------------------- -
void RenderComponent::CreateProgram()
{
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_pMaterial->GetShaderGLPointer(ShaderType::k_vertex));
    glAttachShader(m_shaderProgram, m_pMaterial->GetShaderGLPointer(ShaderType::k_fragment));
    glLinkProgram(m_shaderProgram);
    glBindFragDataLocation(m_shaderProgram, 0, "outColor");
    glUseProgram(m_shaderProgram);

    //Will set attributes for the currently bound VBO
    GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    //TODO: Not sure where to put this just yet
    m_transformMatrixPair.second = glGetUniformLocation(m_shaderProgram, "transformMatrix");
    m_viewMatrixUniform = glGetUniformLocation(m_shaderProgram, "viewMatrix");
    m_projectionMatrixUniform = glGetUniformLocation(m_shaderProgram, "projectionMatrix");

    glBindVertexArray(0);
}

GLuint RenderComponent::GetVBO() { return m_pMesh->GetVBO(); }
GLuint RenderComponent::GetEBO() { return m_pMesh->GetEBO(); }
GLuint RenderComponent::GetVAO() { return m_pMesh->GetVAO(); }
std::vector<unsigned int> RenderComponent::GetIndices() { return m_pMesh->GetIndices(); }
