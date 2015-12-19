//RenderComponent.h

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameObjectComponent.h"

#include "Color.h"
#include "Enums.h"
#include "Vector3.h"

#include <cml/cml.h>

class Mesh;
class Material;
class CameraComponent;

typedef unsigned int GLuint;
typedef int GLint;
typedef std::pair<cml::matrix44f_c, GLint> TransformMatrixPair;

class RenderComponent : public GameObjectComponent
{
    Mesh* m_pMesh;
    Material* m_pMaterial;
    Color* m_pMaterialColor;
    Color* m_pMaterialAmbientColor;

    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;

    Vector3* m_translationReference;
    Vector3* m_rotationReference;
    Vector3* m_pScaleReference;

    cml::matrix44f_c m_modelMatrix;
    TransformMatrixPair m_transformMatrixPair;
    GLint m_viewMatrixUniform;
    GLint m_projectionMatrixUniform;
    GLint m_pointLightPositionUniform;
    GLint m_materialAmbientColorUniform;

    GLuint m_shaderProgram;

    GLint m_transformViewProjectionMatrixUniform;

    //TODO: Refactor to allow multiple cameras
    CameraComponent* m_pCameraComponent;

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

    void SetColor(float r, float g, float b);
    void SetColor(Color color);
    void SetAmbientColor(float r, float g, float b);
    void SetAmbientColor(Color color);

    void CreateProgram();
    void Draw();

    Material* const GetMaterial() { return m_pMaterial; }

    //Getters, still not 100% sure about this structure
    GLuint GetVBO();
    GLuint GetEBO();
    GLuint GetVAO();
    GLuint GetVertexNormalObject();
    GLuint GetTextureBufferObject();
    GLuint GetUVBufferObject();
    GLuint GetShaderProgram() { return m_shaderProgram; }

    //Matrices
    cml::matrix44f_c GetTransformMatrix() { return m_transformMatrixPair.first; }
    GLint GetTransformMatrixUniform() { return m_transformMatrixPair.second; }
    GLint GetProjectionMatrixUniform() { return m_projectionMatrixUniform; }
    GLint GetViewMatrixUniform() { return m_viewMatrixUniform; }

    std::vector<unsigned int> GetIndices();

    //Local transform for the model
    //Position
    Vector3 GetPosition() { return m_position; }
    void SetPosition(float x, float y, float z);
    void Translate(float x, float y, float z);

    //Rotation
    Vector3 GetRotation() { return m_rotation; }
    void SetEulerRotation(float x, float y, float z);
    void Rotate(float x, float y, float z);

    //Scale
    Vector3 GetScale() { return m_scale; }
    void SetScale(float x, float y, float z);
    void Scale(float x, float y, float z);

private:
    void CalculateModelMatrix();
};

#endif // !RENDERCOMPONENT_H