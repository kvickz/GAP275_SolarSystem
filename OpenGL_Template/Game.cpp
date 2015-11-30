//Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "FileLoader.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

#include <math.h>

Game::Game()
    :m_running(true)
    , m_pRenderer(nullptr)
    , m_deltaTime(0)
    , m_elapsed(0)
{
    //
}

Game::~Game()
{
    delete m_pRenderer;
    m_pRenderer = nullptr;
}

#include "RenderComponent.h"

//-------------------------------------------------------------------------------------- -
//  Main Game Initialization Function
//-------------------------------------------------------------------------------------- -
void Game::Init()
{
    m_pRenderer = new Renderer();

    m_pRenderer->Init();

    CreateGameObjects();

    CollectShaderVariables();
}

//-------------------------------------------------------------------------------------- -
//  Create Game Objects Function
//      -This is an initialization-phase function that will create
//       all of the initial objects for the game.
//-------------------------------------------------------------------------------------- -
#include "Enums.h"
#include "Constants.h"
#include "Material.h"
#include "TransformComponent.h"

void Game::CreateGameObjects()
{
    GameObjectFactory factory;

    m_gameObjects.push_back(factory.CreatePlanet());
    m_gameObjects.push_back(factory.CreatePlanet());

    // Object Initialization
    //INIT ALL GAME OBJECTS
    for (GameObject* pGameObj : m_gameObjects)
    {
        pGameObj->Init();
    }

    m_gameObjects[0]->GetComponent<RenderComponent>(k_renderComponentID)->LoadMeshFromFile("Sphere.obj");
    m_gameObjects[1]->GetComponent<RenderComponent>(k_renderComponentID)->LoadMeshFromFile("suzanne.obj");

    m_gameObjects[0]->GetTransformComponent()->SetPosition(2.8f, 0.f, -5.9f);
    m_gameObjects[1]->GetTransformComponent()->SetPosition(-2.8f, 0.f, -5.9f);
    
    for (GameObject* pGameObj : m_gameObjects)
    {
        //TODO: Eventually make a material manager that deletes the materials instead
        //      of the render components
        //Assigning material
        Material* pMaterial = new Material();
        pMaterial->LoadShader("VertexShader.glsl", ShaderType::k_vertex);
        pMaterial->LoadShader("FragmentShader.glsl", ShaderType::k_fragment);
    
        pGameObj->GetComponent<RenderComponent>(k_renderComponentID)->LoadMaterial(pMaterial);
        pGameObj->GetComponent<RenderComponent>(k_renderComponentID)->CreateProgram();
    }
}

//-------------------------------------------------------------------------------------- -
//  Main Game Update Function
//-------------------------------------------------------------------------------------- -
int Game::Update()
{
    //Calculating time delta
    m_deltaTime = SDL_GetTicks() - m_elapsed;
    m_elapsed = SDL_GetTicks();

    //Updating objs
    UpdateGameObjects();

    //TODO: needs to be refactored into renderer/input manager
    if (m_pRenderer->HandleEvents() == 0)  //HANDLING WINDOW EVENTS
        return 0;

    Draw();

    m_pRenderer->SwapWindow();

    //Remove Queued objects
    DeleteQueuedObjects();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  Update Game Objects Function
//      -Iterates through all gameObjects calling Update() within each.
//      -Also checks for objects that need to be removed
//-------------------------------------------------------------------------------------- -
void Game::UpdateGameObjects()
{
    auto iterator = m_gameObjects.begin();

    while (iterator != m_gameObjects.end())
    {
        (*iterator)->Update();

        //Places object into deletion queue
        if ((*iterator)->IsReadyToDelete())
        {
            m_gameObjectsToDelete.push((*iterator));

            auto tempIterator = iterator;
            ++iterator;

            //TODO: This might not work as expected, if it calls delete on the pointer
            m_gameObjects.erase(tempIterator);

            return; //TODO: This might be a bad idea?
        }

        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Remove Game Object Function
//      -Takes a pointer to a game object as a parameter and marks it for deletion.
//       does not actually delete the object. 
//      -Deletion of objects is handled by Game::DeleteQueuedObjects()
//-------------------------------------------------------------------------------------- -
void Game::RemoveGameObject(GameObject* pGameObject)
{
    pGameObject->DeleteObject();
}

//-------------------------------------------------------------------------------------- -
//  Delete Queued Game Objects Function
//      -Will destroy any objects inside m_gameObjectsToDelete for good.
//-------------------------------------------------------------------------------------- -
void Game::DeleteQueuedObjects()
{
    while (!m_gameObjectsToDelete.empty())
    {
        //TODO: safe delete macro
        delete m_gameObjectsToDelete.front();
        m_gameObjectsToDelete.front() = nullptr;

        m_gameObjectsToDelete.pop();
    }
}

//-------------------------------------------------------------------------------------- -
//  Main Game Shutdown Function
//-------------------------------------------------------------------------------------- -
void Game::Shutdown()
{
    m_pRenderer->Shutdown();
    DeleteAllObjects();
}

//-------------------------------------------------------------------------------------- -
//  Delete All Objects Function
//      -Only meant to be called by shutdown, does as the name says
//-------------------------------------------------------------------------------------- -
void Game::DeleteAllObjects()
{
    auto iterator = m_gameObjects.begin();

    while (iterator != m_gameObjects.end())
    {
        delete (*iterator);
        (*iterator) = nullptr;

        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Collect Shader Variables Function
//      -Gets the location of the uniforms for modulation in update
//-------------------------------------------------------------------------------------- -
void Game::CollectShaderVariables()
{
    //GLuint shaderProg = m_gameObjects[0]->GetComponent<RenderComponent>(k_renderComponentID)->GetShaderProgram();

    //m_viewMatrixUniform = glGetUniformLocation(shaderProg, "viewMatrix");
    //m_projectionMatrixUniform = glGetUniformLocation(shaderProg, "projectionMatrix");

    //Initializing matrices to 1
    m_viewMatrix.identity();
    m_projectionMatrix.identity();

    //Setting camera position
    m_cameraPosition[0] = 0.f;
    m_cameraPosition[1] = 5.f;
    m_cameraPosition[2] = 0.f;

    //Draw in perspective
    cml::matrix_perspective_xfov_RH(m_projectionMatrix, 70.f, 800.f / 600.f, 0.1f, 1000.f, cml::z_clip_neg_one);
}

const float k_camSpeed = 0.10f;
float camX = 0.f;
float camY = 0.f;
float camZ = 3.f;

unsigned int renderCount = 0;

//-------------------------------------------------------------------------------------- -
//  Main Application Draw Function
//-------------------------------------------------------------------------------------- -
void Game::Draw()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ++renderCount;

    //BINDING BUFFERS
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Set camera position and target
    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraForward).subvector(3);
    cml::vector3f cameraPosition(camX, 0.f, camZ);

    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                     //Origin
                           , cameraPosition + cameraDirection   //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));     //Up-Direction, Y is up
    
    //Render objects
    for (GameObject* pGameObj : m_gameObjects)
    {
        RenderComponent* pRenderComponent = pGameObj->GetComponent<RenderComponent>(k_renderComponentID);
        DrawObject(pRenderComponent);
    }
}

void Game::DrawObject(RenderComponent* pRenderer)
{
    GLuint shaderProg = pRenderer->GetShaderProgram();
    glUseProgram(shaderProg);
    glBindVertexArray(pRenderer->GetVAO());

    glProgramUniformMatrix4fv(shaderProg, pRenderer->GetTransformMatrixUniform(), 1, GL_FALSE, pRenderer->GetTransformMatrix().data());
    glProgramUniformMatrix4fv(shaderProg, pRenderer->GetViewMatrixUniform(), 1, GL_FALSE, m_viewMatrix.data());
    glProgramUniformMatrix4fv(shaderProg, pRenderer->GetProjectionMatrixUniform(), 1, GL_FALSE, m_projectionMatrix.data());

    glDrawElements(GL_TRIANGLES, pRenderer->GetIndices().size(), GL_UNSIGNED_INT, &pRenderer->GetIndices()[0]);

    glBindVertexArray(0);
}