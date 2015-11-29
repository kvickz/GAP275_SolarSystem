//Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "FileLoader.h"

#include <math.h>

Game::Game()
    :m_running(true)
    , m_pRenderer(nullptr)
{
    //
}

Game::~Game()
{
    delete m_pRenderer;
    m_pRenderer = nullptr;
}

void Game::Init()
{
    m_pRenderer = new Renderer();

    m_pRenderer->Init();
}

void Game::Update()
{
    m_pRenderer->Update();
}

void Game::Shutdown()
{
    m_pRenderer->Shutdown();
}

//TODO: Remove
void Game::SwapWindow()
{
    m_pRenderer->SwapWindow();
}

int Game::HandleEvents()
{
    return m_pRenderer->HandleEvents();
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

void Game::Draw()
{
    /*
    float sinVal = sinf(SDL_GetTicks() * 0.001f);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Rotation and translation of the object
    cml::matrix44f_c objectRotation;
    cml::matrix44f_c objectTranslation;

    objectRotation.identity();
    cml::matrix_rotate_about_local_y(objectRotation, (SDL_GetTicks() * 0.001f));
    cml::matrix_translation(objectTranslation, 0.f, (sinVal * 0.05f), -2.f);

    //g_transformMatrix = objectTranslation * objectRotation;
    g_game.SetTransformMatrix(objectTranslation * objectRotation);

    //Set camera position and target
    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraForward).subvector(3);
    cml::vector3f cameraPosition(camX, 0.f, camZ);

    cml::matrix_look_at_RH(g_game.GetViewMatrix()
                           , cameraPosition                     //Origin
                           , cameraPosition + cameraDirection   //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));     //Up-Direction, Y is up

    //BINDING BUFFERS
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glUseProgram(g_shaderProgram);
    glUseProgram(g_game.GetShaderProgram());
    //glBindBuffer(g_vertexBufferObject);

    glBindVertexArray(g_game.GetVAO());

    glProgramUniformMatrix4fv(g_game.GetShaderProgram(), g_game.GetTransformMatrixUniform(), 1, GL_FALSE, g_game.GetTransformMatrix().data());
    glProgramUniformMatrix4fv(g_game.GetShaderProgram(), g_game.GetViewMatrixUniform(), 1, GL_FALSE, g_game.GetViewMatrix().data());
    glProgramUniformMatrix4fv(g_game.GetShaderProgram(), g_game.GetProjectionMatrixUniform(), 1, GL_FALSE, g_game.GetProjectionMatrix().data());

    glDrawElements(GL_TRIANGLES, g_game.GetIndices().size(), GL_UNSIGNED_INT, &g_game.GetIndices()[0]);
    */
}