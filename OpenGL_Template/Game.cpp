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

//-------------------------------------------------------------------------------------- -
//  Main Game Initialization Function
//-------------------------------------------------------------------------------------- -
void Game::Init()
{
    m_pRenderer = new Renderer();

    m_pRenderer->Init();

    // Object Initialization
    CreateObject("Sphere.obj");
    CreateShaders();
    CreateProgram();
    CollectShaderVariables();

    CreateGameObjects();
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

//TODO: Refactor into gameobjects
//-------------------------------------------------------------------------------------- -
//  Create Objects Function
//-------------------------------------------------------------------------------------- -
void Game::CreateObject(char* fileName)
{
    ObjFile cubeObj;
    cubeObj.Load(fileName);

    //Allocate memory
    m_verts = cubeObj.GetVerticesAsFloats();
    m_vertIndices = cubeObj.GetFacesAsIndices();

    //VBO
    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(float), &m_verts[0], GL_STATIC_DRAW);

    //EBO
    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertIndices.size(), &m_vertIndices[0], GL_STATIC_DRAW);

    //VAO
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
}

//-------------------------------------------------------------------------------------- -
//  Create Shaders Function 
//      -Will create and compile vertex and fragment shader
//-------------------------------------------------------------------------------------- -

void Game::CreateShaders()
{
    GLint debugInt = 0; //1 == success

    ShaderFile vertexSource, fragmentSource;
    vertexSource.Load("VertexShader.glsl");
    fragmentSource.Load("FragmentShader.glsl");

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vSource = vertexSource.GetSource();
    glShaderSource(m_vertexShader, 1, &vSource, nullptr);
    glCompileShader(m_vertexShader);

    const char* fSource = fragmentSource.GetSource();
    glShaderSource(m_fragmentShader, 1, &fSource, nullptr);
    glCompileShader(m_fragmentShader);

    char buffer[512] = { 0 };
    glGetShaderInfoLog(m_vertexShader, 512, NULL, buffer);
}

//-------------------------------------------------------------------------------------- -
//  Create Program Function
//      -Will create a program and link shaders to it
//-------------------------------------------------------------------------------------- -
void Game::CreateProgram()
{
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
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
    //glUseProgram(g_shaderProgram);
    glUseProgram(m_shaderProgram);
    //glBindBuffer(g_vertexBufferObject);

    glBindVertexArray(m_vertexArrayObject);

    glProgramUniformMatrix4fv(m_shaderProgram, m_transformMatrixUniform, 1, GL_FALSE, m_transformMatrix.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_viewMatrixUniform, 1, GL_FALSE, m_viewMatrix.data());
    glProgramUniformMatrix4fv(m_shaderProgram, m_projectionMatrixUniform, 1, GL_FALSE, m_projectionMatrix.data());

    glDrawElements(GL_TRIANGLES, m_vertIndices.size(), GL_UNSIGNED_INT, &m_vertIndices[0]);
    
}