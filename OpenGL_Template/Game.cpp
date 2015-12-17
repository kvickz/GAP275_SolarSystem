//Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "FileLoader.h"
#include "Time.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

#include <math.h>

Game::Game()
    :m_running(true)
    , m_pRenderer(nullptr)
    , m_pAssetManager(nullptr)
    , m_pInputManager(nullptr)
    , m_pCamera(nullptr)
    , m_pTime(nullptr)
    //, m_deltaTime(0)
    //, m_elapsed(0)
{
    //
}

Game::~Game()
{
    delete m_pRenderer;
    m_pRenderer = nullptr;

    delete m_pAssetManager;
    m_pAssetManager = nullptr;

    delete m_pInputManager;
    m_pInputManager = nullptr;

    delete m_pTime;
    m_pTime = nullptr;

    m_pCamera = nullptr;
}

#include "RenderComponent.h"

//-------------------------------------------------------------------------------------- -
//  Main Game Initialization Function
//      -Initializes all of the main systems of the game
//      -Loads all necessary data and creates all the initial game objects
//-------------------------------------------------------------------------------------- -
void Game::Init()
{
    m_pRenderer = new Renderer();
    m_pRenderer->Init();

    m_pAssetManager = new AssetManager();
    m_pInputManager = new InputManager(this);

    m_pTime = new Time();

    CreateGameObjects();
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
#include "Mesh.h"

const int k_numOfSpheres = 2;
const int k_positionOffset = 2;

void Game::CreateGameObjects()
{
    GameObjectFactory factory(m_pRenderer, m_pTime);
    Mesh* pSphereMesh = m_pAssetManager->LoadMesh("sphere.obj");
    //Mesh* pSphereMesh = m_pAssetManager->LoadMesh("TurtleTris.obj");
    Material* pMaterial = m_pAssetManager->LoadMaterial("DefaultMaterial", "VertexShader.glsl", "FragmentShader.glsl");

	/*
    //Creating a grid of objects
    for (int j = 0; j < k_numOfSpheres; ++j)
    {
        for (int i = 0; i < k_numOfSpheres; ++i)
        {
            unsigned int index = j * k_numOfSpheres + i;

            m_gameObjects.push_back(factory.CreatePlanet(this));
            m_gameObjects[index]->GetComponent<RenderComponent>(k_renderComponentID)->Init(pSphereMesh, pMaterial);

            float x = (float)(i * k_positionOffset);
            float y = (float)(j * k_positionOffset);
            //float x = 0;
            //float y = 5;
            float z = -50.f;
            m_gameObjects[index]->GetTransformComponent()->SetPosition(x, y, z);
            //m_gameObjects[index]->GetTransformComponent()->SetPosition(0, 0, 0);
        }
    }
    */

	//OBJ1
    m_gameObjects.push_back(factory.CreatePlanet(this));
    m_gameObjects[0]->GetComponent<RenderComponent>(k_renderComponentID)->Init(pSphereMesh, pMaterial);
    m_gameObjects[0]->GetTransformComponent()->SetPosition(0, 0, -50);
    
	
	//OBJ2
	m_gameObjects.push_back(factory.CreatePlanet(this));
	m_gameObjects[1]->GetComponent<RenderComponent>(k_renderComponentID)->Init(pSphereMesh, pMaterial);
	m_gameObjects[1]->GetTransformComponent()->SetPosition(0, 0, 5);
	float scaleFactor = 0.5f;
	m_gameObjects[1]->GetTransformComponent()->SetScale(scaleFactor, scaleFactor, scaleFactor);

	m_gameObjects[1]->GetTransformComponent()->SetEulerRotation(0, 1, 0);

	//OBJ3
	m_gameObjects.push_back(factory.CreatePlanet(this));
	m_gameObjects[2]->GetComponent<RenderComponent>(k_renderComponentID)->Init(pSphereMesh, pMaterial);
	m_gameObjects[2]->GetTransformComponent()->SetPosition(0, 0, 3);
	scaleFactor = 0.2f;
	m_gameObjects[2]->GetTransformComponent()->SetScale(scaleFactor, scaleFactor, scaleFactor);
	


    //Testing parenting
    /*
    for (int i = 0; i < (k_numOfSpheres * k_numOfSpheres) - 1; ++i)
    {
        m_gameObjects[i + 1]->GetTransformComponent()->SetParent(m_gameObjects[i]->GetTransformComponent());
    }
    */

    m_gameObjects[1]->GetTransformComponent()->SetParent(m_gameObjects[0]->GetTransformComponent());
    m_gameObjects[2]->GetTransformComponent()->SetParent(m_gameObjects[1]->GetTransformComponent());
    //m_gameObjects[3]->GetTransformComponent()->SetParent(m_gameObjects[2]->GetTransformComponent());
    

    m_pCamera = factory.CreateCamera(this);
    m_pInputManager->AddPlayer(0, m_pCamera);
    m_gameObjects.push_back(m_pCamera);

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
    //Calculating time
    m_pTime->Update();

    //TODO: needs to be refactored into renderer/input manager
    if (m_pInputManager->HandleEvents() == 0)  //HANDLING WINDOW EVENTS
        return 0;

    //TODO: I'd like to get this to happen AFTER the game objects update
    //      currently with the game components drawing themselves its a bit wonky
    m_pRenderer->ClearScreen();

    //Updating objs
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
	UpdateGameObjects();

    //float sinVal = sinf(SDL_GetTicks() * 0.01f) * 0.01f;
	//m_gameObjects[0]->GetTransformComponent()->Translate(sinVal, 0.f, 0.f);
	m_gameObjects[0]->GetTransformComponent()->Rotate(0.f, 0.01f, 0.f);
	//m_gameObjects[1]->GetTransformComponent()->Rotate(0.f, 0.02f, 0.f);
    
    /*
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
    */
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

int Game::GetDeltaTime() 
{ 
    return m_pTime->GetDeltaTime();
}

unsigned long Game::GetElapsedTime() 
{ 
    return m_pTime->GetElapsedTime();
}