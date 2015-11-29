//Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <queue>

#include <cml/cml.h>

class Renderer;
class GameObject;

typedef unsigned int GLuint;
typedef int GLint;

//TODO: Remove
class RenderComponent;

class Game
{
private:
    //TODO: Clean dis shit up
    //----------------------------------
    // SHADERS
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
    unsigned int m_deltaTime;
    unsigned int m_elapsed;
    bool m_running;

    std::vector<GameObject*> m_gameObjects;
    std::queue<GameObject*> m_gameObjectsToDelete;

    Renderer* m_pRenderer;
    //----------------------------------

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

private:
    //TODO: Super refactor!
    GLuint GetShaderProgram() { return m_shaderProgram; }
    GLint GetTransformMatrixUniform() { return m_transformMatrixUniform; }
    GLint GetViewMatrixUniform() { return m_viewMatrixUniform; }
    GLint GetProjectionMatrixUniform() { return m_projectionMatrixUniform; }
    cml::matrix44f_c GetTransformMatrix() { return m_transformMatrix; }
    cml::matrix44f_c GetViewMatrix() { return m_viewMatrix; }
    cml::matrix44f_c GetProjectionMatrix() { return m_projectionMatrix; }
    cml::vector3f GetCameraPosition() { return m_cameraPosition; }

    void SetTransformMatrix(cml::matrix44f_c val) { m_transformMatrix = val; }

    void CreateShaders();
    void CreateProgram();
    void CollectShaderVariables();

    void CreateGameObjects();
    void UpdateGameObjects();
    void RemoveGameObject(GameObject* pGameObject);
    void DeleteQueuedObjects();

    //This is a shutdown function
    void DeleteAllObjects();

    void Draw();
};

#endif // !GAME_H