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

const int k_numOfSpheres = 4;
const int k_positionOffset = 4;

void Game::CreateGameObjects()
{
    GameObjectFactory factory;

    //Creating a grid of objects
    for (int j = 0; j < k_numOfSpheres; ++j)
    {
        for (int i = 0; i < k_numOfSpheres; ++i)
        {
            unsigned int index = j * k_numOfSpheres + i;

            m_gameObjects.push_back(factory.CreatePlanet(this));

            Material* pMaterial = new Material("VertexShader.glsl", "FragmentShader.glsl");
            m_gameObjects[index]->GetComponent<RenderComponent>(k_renderComponentID)->Init("torusLo.obj", pMaterial);

            float x = (float)(i * k_positionOffset);
            float y = (float)(j * k_positionOffset);
            float z = -50.f;
            m_gameObjects[index]->GetTransformComponent()->SetPosition(x, y, z);
        }
    }
    
    // Object Initialization
    //INIT ALL GAME OBJECTS
    for (GameObject* pGameObj : m_gameObjects)
    {
        pGameObj->Init();
    }

    /*
    //OBJ 0
    Material* pMaterial = new Material("VertexShader.glsl", "FragmentShader.glsl");
    m_gameObjects[0]->GetComponent<RenderComponent>(k_renderComponentID)->Init("Sphere.obj", pMaterial);

    //OBJ 1
    pMaterial = new Material("VertexShader.glsl", "FragmentShader.glsl");
    m_gameObjects[1]->GetComponent<RenderComponent>(k_renderComponentID)->Init("Sphere.obj", pMaterial);

    m_gameObjects[0]->GetTransformComponent()->SetPosition(2.8f, 0.f, -5.9f);
    m_gameObjects[1]->GetTransformComponent()->SetPosition(-2.8f, 0.f, -5.9f);
    */
}

//-------------------------------------------------------------------------------------- -
//  Main Game Update Function
//-------------------------------------------------------------------------------------- -
int Game::Update()
{
    //Calculating time delta
    m_deltaTime = SDL_GetTicks() - m_elapsed;
    m_elapsed = SDL_GetTicks();

    Draw();

    //Updating objs
    UpdateGameObjects();

    //TODO: needs to be refactored into renderer/input manager
    if (m_pRenderer->HandleEvents() == 0)  //HANDLING WINDOW EVENTS
        return 0;

    UpdateGameLogic();

    m_pRenderer->SwapWindow();

    //Remove Queued objects
    DeleteQueuedObjects();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  Update Game Logic Function
//      -Runs any custom game logic
//-------------------------------------------------------------------------------------- -
void Game::UpdateGameLogic()
{
    float sinVal = sinf(SDL_GetTicks() * 0.001f);

    for (int j = 0; j < k_numOfSpheres; ++j)
    {
        for (int i = 0; i < k_numOfSpheres; ++i)
        {
            unsigned int index = j * k_numOfSpheres + i;

            float x = ((sinVal * 3.f) + ((float)(i * k_positionOffset)));
            float y = (float)(j * k_positionOffset);
            float z = -50.f;
            m_gameObjects[index]->GetTransformComponent()->SetPosition(x, y, z);
        }
    }
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

    //TODO: This doesn't do anything
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

//-------------------------------------------------------------------------------------- -
//  Main Application Draw Function
//-------------------------------------------------------------------------------------- -
void Game::Draw()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Setting polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Set camera position and target
    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraForward).subvector(3);
    cml::vector3f cameraPosition(camX, 0.f, camZ);

    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                     //Origin
                           , cameraPosition + cameraDirection   //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));     //Up-Direction, Y is up

}