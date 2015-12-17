//RenderComponent.cpp

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "Game.h"

#include "Mesh.h"
#include "Material.h"

#include <SDL.h>

RenderComponent::RenderComponent(ComponentID id, GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(id, pGameObject, pTransform)
    , m_pMesh(nullptr)
    , m_pMaterial(nullptr)
{
    //Initialize to 1, 1, 1
    m_transformMatrixPair.first.identity();

    m_pScaleReference = m_pGameObject->GetTransformComponent()->GetScalePointer();
    m_translationReference = m_pGameObject->GetTransformComponent()->GetPositionPointer();
    m_rotationReference = m_pGameObject->GetTransformComponent()->GetRotationPointer();
}

RenderComponent::~RenderComponent()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Render Component Initialization Function
//      -Default initialization, call the overloaded function for more functionality 
//-------------------------------------------------------------------------------------- -
void RenderComponent::Init()
{
    GameObject* pCamObject = m_pGameObject->GetGame()->GetCameraObject();
    m_pCameraComponent = pCamObject->GetComponent<CameraComponent>(k_cameraComponentID);
}

//-------------------------------------------------------------------------------------- -
//  Render Component Initialization Function
//      -Allows you to set the mesh and material of this component
//      -This version of init requires you to have a preloaded Mesh
//       but is far more efficient.
//      -**Note** Render component is not responsible for deleting mesh assets.
//      -**This is the recommended version of Init to use.**
//-------------------------------------------------------------------------------------- -
void RenderComponent::Init(Mesh* pMesh, Material* pMaterial)
{
    m_pMesh = pMesh;
    LoadMaterial(pMaterial);
    CreateProgram();
}

//-------------------------------------------------------------------------------------- -
//  Render Component Initialization Function
//      -Allows you to set the mesh and material of this component
//      -**Warning** This can be extremely inefficient if called multiple times
//       use the overloaded Init(Mesh* pMesh, Material* pMaterial); to avoid
//       loading multiple duplicate meshes
//      -This init function should generally be avoided because you
//       must delete the mesh loaded from the caller, the mesh will
//       NOT be deleted by this render component. The function is
//       provided for convenience and testing purposes.
//-------------------------------------------------------------------------------------- -
Mesh* RenderComponent::Init(const char* fileName, Material* pMaterial)
{
    LoadMeshFromFile(fileName);
    LoadMaterial(pMaterial);
    CreateProgram();

    return m_pMesh;
}

//-------------------------------------------------------------------------------------- -
//  Set Mesh Function
//      -Sets the mesh using a pointer
//      -**Note** Render component is not responsible for deleting mesh assets.
//-------------------------------------------------------------------------------------- -
void RenderComponent::SetMesh(Mesh* pMesh)
{
    m_pMesh = pMesh;
}

//-------------------------------------------------------------------------------------- -
//  Draw Function
//      -Makes openGL calls to draw this object
//-------------------------------------------------------------------------------------- -

void RenderComponent::Draw()
{
    //Bind VAO
    glUseProgram(m_shaderProgram);
    GLuint vao = GetVAO();
    glBindVertexArray(GetVAO());

    //Get Transform, View, and Projection Matrices
	//m_transformMatrixPair.first = m_pTransform->GetTransformMatrix();
    m_transformMatrixPair.first = m_pTransform->GetWorldTransformMatrix();
    cml::matrix44f_c cameraViewMatrix = m_pCameraComponent->GetViewMatrix();
    cml::matrix44f_c cameraProjectionMatrix = m_pCameraComponent->GetProjectionMatrix();

    //Calculate Transform, View, and Projection Matrices
    glProgramUniformMatrix4fv(m_shaderProgram, m_transformMatrixPair.second, 1, GL_FALSE, m_transformMatrixPair.first.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_viewMatrixUniform, 1, GL_FALSE, cameraViewMatrix.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_projectionMatrixUniform, 1, GL_FALSE, cameraProjectionMatrix.data());

    /*
    //TODO: Get Light position in world space
    GLint aLoc = glGetUniformLocation(m_shaderProgram, "lightPosition");
    glBindAttribLocation(m_shaderProgram, 0, "lightPosition");
    glUniform3f(m_shaderProgram, 0, 0, 0);
    */

    /*
    cml::matrix44f_c transformViewProjectionMatrix = cameraProjectionMatrix * cameraViewMatrix * m_transformMatrixPair.first;

    //Update matrix
    glProgramUniformMatrix4fv(m_shaderProgram, m_transformViewProjectionMatrixUniform, 1, GL_FALSE, transformViewProjectionMatrix.data());
    */

    //Draw
    glDrawElements(GL_TRIANGLES, GetIndices().size(), GL_UNSIGNED_INT, &GetIndices()[0]);

    glBindVertexArray(0);
}

//-------------------------------------------------------------------------------------- -
//  Load Mesh From File Function
//      -Will load a mesh from a given file path
//-------------------------------------------------------------------------------------- -
void RenderComponent::Update()
{
    //** Draw! **//
    Draw();
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
    
    glBindFragDataLocation(m_shaderProgram, 0, "colorRGBA");
    glLinkProgram(m_shaderProgram);
    glUseProgram(m_shaderProgram);

    //Will set attributes for the currently bound VBO

    //UVs
    glBindBuffer(GL_ARRAY_BUFFER, GetUVBufferObject());
    GLint texAttrib = glGetAttribLocation(m_shaderProgram, "vertUV");
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texAttrib);

    //NORMALS
    glBindBuffer(GL_ARRAY_BUFFER, GetVertexNormalObject());
    GLint normalAttrib = glGetAttribLocation(m_shaderProgram, "vertexNormal");
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalAttrib);

    //POSITION
    glBindBuffer(GL_ARRAY_BUFFER, GetVBO());
    //GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
    GLint posAttrib = glGetAttribLocation(m_shaderProgram, "vertex");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    m_transformMatrixPair.second = glGetUniformLocation(m_shaderProgram, "transformMatrix");
    m_viewMatrixUniform = glGetUniformLocation(m_shaderProgram, "viewMatrix");
    m_projectionMatrixUniform = glGetUniformLocation(m_shaderProgram, "projectionMatrix");

    //m_transformViewProjectionMatrixUniform = glGetUniformLocation(m_shaderProgram, "transformViewProjectionMatrix");

    glBindVertexArray(0);
}

GLuint RenderComponent::GetVBO() { return m_pMesh->GetVBO(); }
GLuint RenderComponent::GetEBO() { return m_pMesh->GetEBO(); }
GLuint RenderComponent::GetVAO() { return m_pMesh->GetVAO(); }
GLuint RenderComponent::GetVertexNormalObject() { return m_pMesh->GetNormalBuffer(); }
GLuint RenderComponent::GetUVBufferObject() { return m_pMesh->GetUVBuffer(); }
std::vector<unsigned int> RenderComponent::GetIndices() { return m_pMesh->GetIndices(); }
