//Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>

#include <cml/cml.h>

class Renderer;
class GameObject;

typedef unsigned int GLuint;
typedef int GLint;

class Game
{
private:
    //TODO: Clean dis shit up
    //----------------------------------
    //GL Vars
    //----------------------------------
    //  BUFFER OBJECTS
    GLuint m_vertexBufferObject = 0;
    GLuint m_elementBufferObject = 0;
    GLuint m_vertexArrayObject = 0;

    std::vector<float> m_verts;
    std::vector<unsigned int> m_vertIndices;

    //----------------------------------
    // SHADERS
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_shaderProgram;

    //----------------------------------
    // SHADER VARIABLES :: MAJOR REFACTORING NEEDS TO BE DONE WITH THESE
    GLint m_transformMatrixUniform;
    GLint m_viewMatrixUniform;
    GLint m_projectionMatrixUniform;

    cml::matrix44f_c m_transformMatrix;
    cml::matrix44f_c m_viewMatrix;
    cml::matrix44f_c m_projectionMatrix;

    cml::vector3f m_cameraPosition;

    //----------------------------------
    //Class Vars
    bool m_running;

    std::vector<GameObject*> m_gameObjects;

    Renderer* m_pRenderer;
    //----------------------------------

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

    //Refactor to renderer
    void SwapWindow();

    //TODO: Super refactor!
    GLuint GetVAO() { return m_vertexArrayObject; }
    std::vector<float> GetVerts() { return m_verts; }
    std::vector<unsigned int> GetIndices() { return m_vertIndices; }
    GLuint GetVertexShader() { return m_vertexShader; }
    GLuint GetFragmentShader() { return m_fragmentShader; }
    GLuint GetShaderProgram() { return m_shaderProgram; }
    GLint GetTransformMatrixUniform() { return m_transformMatrixUniform; }
    GLint GetViewMatrixUniform() { return m_viewMatrixUniform; }
    GLint GetProjectionMatrixUniform() { return m_projectionMatrixUniform; }
    cml::matrix44f_c GetTransformMatrix() { return m_transformMatrix; }
    cml::matrix44f_c GetViewMatrix() { return m_viewMatrix; }
    cml::matrix44f_c GetProjectionMatrix() { return m_projectionMatrix; }
    cml::vector3f GetCameraPosition() { return m_cameraPosition; }

    void SetTransformMatrix(cml::matrix44f_c val) { m_transformMatrix = val; }

    void CreateObject(char* fileName);
    void CreateShaders();
    void CreateProgram();
    void CollectShaderVariables();

    void Draw();
};

#endif // !GAME_H