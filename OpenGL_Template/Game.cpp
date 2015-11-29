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

    // Object Initialization
    //TODO: Remove, this is just for testing
    m_gameObjects[0]->GetComponent<RenderComponent>(2)->LoadMeshFromFile("Sphere.obj");
    CreateShaders();
    CreateProgram();
    CollectShaderVariables();
}

//-------------------------------------------------------------------------------------- -
//  Create Game Objects Function
//      -This is an initialization-phase function that will create
//       all of the initial objects for the game.
//-------------------------------------------------------------------------------------- -
void Game::CreateGameObjects()
{
    GameObjectFactory factory;

    m_gameObjects.push_back(factory.CreatePlanet());
}

#include "RenderComponent.h"

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
//  Create Shaders Function 
//      -Will create and compile vertex and fragment shader
//-------------------------------------------------------------------------------------- -

#include "Enums.h"
#include "Material.h"

void Game::CreateShaders()
{
    Material* pMaterial = new Material();
    pMaterial->LoadShader("VertexShader.glsl", ShaderType::k_vertex);
    pMaterial->LoadShader("FragmentShader.glsl", ShaderType::k_fragment);

    m_gameObjects[0]->GetComponent<RenderComponent>(2)->LoadMaterial(pMaterial);
}

//-------------------------------------------------------------------------------------- -
//  Create Program Function
//      -Will create a program and link shaders to it
//-------------------------------------------------------------------------------------- -
void Game::CreateProgram()
{
    Material* pMaterial = m_gameObjects[0]->GetComponent<RenderComponent>(2)->GetMaterial();

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, pMaterial->GetShaderGLPointer(ShaderType::k_vertex));
    glAttachShader(m_shaderProgram, pMaterial->GetShaderGLPointer(ShaderType::k_fragment));
    glLinkProgram(m_shaderProgram);
    glBindFragDataLocation(m_shaderProgram, 0, "outColor");
    glUseProgram(m_shaderProgram);

    //Will set attributes for the currently bound VBO
    GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
    //posAttrib = 0;
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
}

//-------------------------------------------------------------------------------------- -
//  Collect Shader Variables Function
//      -Gets the location of the uniforms for modulation in update
//-------------------------------------------------------------------------------------- -
void Game::CollectShaderVariables()
{
    m_transformMatrixUniform = glGetUniformLocation(m_shaderProgram, "transformMatrix");
    m_viewMatrixUniform = glGetUniformLocation(m_shaderProgram, "viewMatrix");
    m_projectionMatrixUniform = glGetUniformLocation(m_shaderProgram, "projectionMatrix");

    //Initializing matrices to 1
    m_transformMatrix.identity();
    m_viewMatrix.identity();
    m_projectionMatrix.identity();

    //Setting camera position
    m_cameraPosition[0] = 0.f;
    m_cameraPosition[1] = 5.f;
    m_cameraPosition[2] = 0.f;

    //Draw in perspective
    cml::matrix_perspective_xfov_RH(m_projectionMatrix, 90.f, 800.f / 600.f, 0.1f, 1000.f, cml::z_clip_neg_one);
}

const float k_camSpeed = 0.10f;
float camX = 0.f;
float camY = 0.f;
float camZ = 0.f;

//-------------------------------------------------------------------------------------- -
//  Main Application Draw Function
//-------------------------------------------------------------------------------------- -
void Game::Draw()
{
    
    float sinVal = sinf(SDL_GetTicks() * 0.001f);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Rotation and translation of the object
    cml::matrix44f_c objectRotation;
    cml::matrix44f_c objectTranslation;

    objectRotation.identity();
    cml::matrix_rotate_about_local_y(objectRotation, (SDL_GetTicks() * 0.001f));
    cml::matrix_translation(objectTranslation, 0.f, (sinVal * 0.05f), -2.f);

    m_transformMatrix = (objectTranslation * objectRotation);

    //Set camera position and target
    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraForward).subvector(3);
    cml::vector3f cameraPosition(camX, 0.f, camZ);

    cml::matrix_look_at_RH(m_viewMatrix
                           , cameraPosition                     //Origin
                           , cameraPosition + cameraDirection   //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));     //Up-Direction, Y is up

    //BINDING BUFFERS
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(m_shaderProgram);

    //glBindVertexArray(m_vertexArrayObject);
    RenderComponent* pRenderComponent = m_gameObjects[0]->GetComponent<RenderComponent>(2);
    glBindVertexArray(pRenderComponent->GetVAO());

    glProgramUniformMatrix4fv(m_shaderProgram, m_transformMatrixUniform, 1, GL_FALSE, m_transformMatrix.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_viewMatrixUniform, 1, GL_FALSE, m_viewMatrix.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_projectionMatrixUniform, 1, GL_FALSE, m_projectionMatrix.data());

    //glDrawElements(GL_TRIANGLES, m_vertIndices.size(), GL_UNSIGNED_INT, &m_vertIndices[0]);
    glDrawElements(GL_TRIANGLES, pRenderComponent->GetIndices().size(), GL_UNSIGNED_INT, &pRenderComponent->GetIndices()[0]);
    
}