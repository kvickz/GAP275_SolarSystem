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
#include "Color.h"
#include "Constants.h"
#include "Material.h"
#include "TransformComponent.h"
#include "PlanetController.h"
#include "Mesh.h"

const int k_numOfSpheres = 2;
const int k_positionOffset = 2;

struct SuperThing{
    float a;
    float b;
    float c;
};

#include "PointLightComponent.h"
#include "GameObjectComponentFactory.h"
#include "Texture.h"

void Game::CreateGameObjects()
{
    GameObjectFactory factory(m_pRenderer, m_pTime);
    
    //  Load Meshes //
    Mesh* pSphereMesh = m_pAssetManager->LoadMesh("sphere.obj");
    Mesh* pRingMesh = m_pAssetManager->LoadMesh("ring.obj");

    //  Create Default Color //
    Color defaultColor(0.8f, 0.8f, 0.8f);
    Color defaultAmbientColor(0.1f, 0.1f, 0.1f);

    //  Load Texture  //
    m_pAssetManager->LoadTexture("DefaultTexture", "earth.jpg");
    Texture* pTextureDefault = m_pAssetManager->CreateTextureInstance("DefaultTexture");

    //  Load Materials //
    m_pAssetManager->LoadMaterial("DefaultMaterial", "LambertVertexShader.glsl", "LambertFragmentShader.glsl", defaultColor, defaultAmbientColor);
    
    Material* pMaterial = m_pAssetManager->CreateMaterialInstance("DefaultMaterial");
    Material* pMaterialSun = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(1.0f, 0.9f, 0.5f), pTextureDefault);
    Material* pMaterialMercury = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(1.0f, 0.3f, 0.0f), pTextureDefault);
    Material* pMaterialVenus = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.7f, 0.9f, 0.f), pTextureDefault);
    Material* pMaterialEarth = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.3f, 0.9f, 0.4f), pTextureDefault);
    Material* pMaterialMars = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(1.0f, 0.2f, 0.0f), pTextureDefault);
    Material* pMaterialJupiter = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.9f, 0.7f, 0.4f), pTextureDefault);
    Material* pMaterialSaturn = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.8f, 0.8f, 0.5f), pTextureDefault);
    Material* pMaterialUranus = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.3f, 0.6f, 0.7f), pTextureDefault);
    Material* pMaterialNeptune = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.0f, 0.5f, 0.9f), pTextureDefault);
    Material* pMaterialPluto = m_pAssetManager->CreateMaterialInstance("DefaultMaterial", Color(0.8f, 0.7f, 0.6f), pTextureDefault);

    //Creating an empty transform object to parent planets to to give them independent rotations
    const int k_numOfPlanets = 9;
    GameObject* pOrbitPositionObject[k_numOfPlanets];
    for (int i = 0; i < k_numOfPlanets; ++i)
        pOrbitPositionObject[i] = CreateEmptyObject();

    //Parameters = (PIVOT, PARENT, SCALE, ROTATION SPEED, MESH, MATERIAL)
    //OBJ1  - The Sun
    GameObject* pSun = CreatePlanet(Vector3(0, 0, 0), nullptr, 0.10f, 0.002f, pSphereMesh, pMaterialSun);
    //OBJ2  - Mercury
    GameObject* pMercury = CreatePlanet(Vector3(0, 0, 3.87f), pOrbitPositionObject[0], 0.00382f, 0.0016f, pSphereMesh, pMaterialMercury);
	//OBJ3  - Venus
    GameObject* pVenus = CreatePlanet(Vector3(0, 0, 7.23f), pOrbitPositionObject[1], 0.00949f, -0.00117f, pSphereMesh, pMaterialVenus);
    //OBJ4  - Earth
    GameObject* pEarth = CreatePlanet(Vector3(0, 0, 10), pOrbitPositionObject[2], 0.01f, 0.0001f, pSphereMesh, pMaterialEarth);
    //OBJ5  - Mars
    GameObject* pMars = CreatePlanet(Vector3(0, 0, 15.24f), pOrbitPositionObject[3], 0.00532f, 0.000802f, pSphereMesh, pMaterialMars);
    //OBJ6  - Jupiter
    GameObject* pJupiter = CreatePlanet(Vector3(0, 0, 52.03f), pOrbitPositionObject[4], 0.11209f, 0.000434f, pSphereMesh, pMaterialJupiter);
    //OBJ7  - Saturn
    GameObject* pSaturn = CreatePlanet(Vector3(0, 0, 95.39f), pOrbitPositionObject[5], 0.09449f, 0.000323f, pSphereMesh, pMaterialSaturn);
    //OBJ8  - Uranus
    GameObject* pUranus = CreatePlanet(Vector3(0, 0, 191.8f), pOrbitPositionObject[6], 0.04007f, -0.000228f, pSphereMesh, pMaterialUranus);
    //OBJ9  - Neptune
    GameObject* pNeptune = CreatePlanet(Vector3(0, 0, 300.6f), pOrbitPositionObject[7], 0.03883f, 0.000182f, pSphereMesh, pMaterialNeptune);
    //OBJ10  - Pluto
    GameObject* pPluto = CreatePlanet(Vector3(0, 0, 395.2f), pOrbitPositionObject[8], 0.00166f, 0.000159f, pSphereMesh, pMaterialPluto);
    //OBJ11 - Earth's moon
    GameObject* pMoon = CreatePlanet(Vector3(0, 0, 1), pEarth, 0.0027f, 0.00343f, pSphereMesh, pMaterialPluto);
    //OBJ12  - Saturn's Ring
    GameObject* pSaturnRing = CreatePlanet(Vector3(0, 0, 0), pSaturn, 0.17f, 0.0323f, pRingMesh, pMaterialSaturn);

    //Make the sun glow!
    pSun->GetComponent<RenderComponent>(k_renderComponentID)->SetAmbientColor(0.9f, 0.9f, 0);
    //Add Point Light Component to the sun
    GameObjectComponentFactory componentFactory;
    pSun->AddComponent(k_pointLightComponentID, componentFactory.CreatePointLightComponent(pSun, pSun->GetTransformComponent()));
    m_pPointLight = pSun;

    //CREATE CAMERA
    m_pCamera = factory.CreateCamera(this);
    m_pInputManager->AddPlayer(0, m_pCamera);
    m_gameObjects.push_back(m_pCamera);
    m_pCamera->GetTransformComponent()->SetPosition(0, 0, 0);

    // Object Initialization
    //INIT ALL GAME OBJECTS
    for (GameObject* pGameObj : m_gameObjects)
    {
        pGameObj->Init();
    }
}

//-------------------------------------------------------------------------------------- -
//  Create Object Functions
//-------------------------------------------------------------------------------------- -
//CREATE EMPTY OBJECT
GameObject* Game::CreateEmptyObject()
{
    GameObjectFactory factory(m_pRenderer, m_pTime);
    GameObject* pGameObject = factory.CreateEmptyGameObject(this);
    m_gameObjects.push_back(pGameObject);
    return pGameObject;
}

//CREATE POINT LIGHT
GameObject* Game::CreatePointLightObject()
{
    GameObjectFactory factory(m_pRenderer, m_pTime);
    GameObject* pGameObject = factory.CreatePointLight(this);
    m_gameObjects.push_back(pGameObject);
    return pGameObject;
}

//CREATE PLANET
GameObject* Game::CreatePlanet(Vector3 position, GameObject* pParent, float scale, float rotationSpeed, Mesh* pMesh, Material* pMaterial)
{
    //Create Factory & Object
    GameObjectFactory factory(m_pRenderer, m_pTime);
    GameObject* pGameObject = factory.CreatePlanet(this);

    //Add mesh & material
    pGameObject->GetComponent<RenderComponent>(k_renderComponentID)->Init(pMesh, pMaterial);

    //Set position
    float distanceScale = 0.5f;
    pGameObject->GetTransformComponent()->SetPosition(position.x, position.y, position.z * distanceScale);

    //Set Scale
    scale *= 5.0f;
    pGameObject->GetTransformComponent()->SetScale(scale, scale, scale);

    //Set Rotation Speed
    float speedScale = 0.5f;
    pGameObject->GetComponent<PlanetController>(k_planetComponentID)->SetRotationSpeed(rotationSpeed * speedScale);

    //Set Parent
    if (pParent) 
    {   //Rotate around this object
        pGameObject->GetComponent<PlanetController>(k_planetComponentID)->SetOrbitee(pParent);
    }
    else
    {   //Rotate about itself
        pGameObject->GetComponent<PlanetController>(k_planetComponentID)->SetOrbitee(pGameObject);
    }

    //Push GameObject to list
    m_gameObjects.push_back(pGameObject);
    return pGameObject;
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

    //m_pPointLight->GetTransformComponent()->Translate(0, 0.001f, 0);

    //float sinVal = sinf(SDL_GetTicks() * 0.01f) * 0.1f;
	//m_gameObjects[0]->GetTransformComponent()->Translate(sinVal, 0.f, 0.f);

    //m_gameObjects[2]->GetTransformComponent()->Rotate(0.f, 0.0001f, 0.f);
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