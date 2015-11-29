//Michael Nevins
//GAP 275 - Solar System Project
//11-26-2015
//Main.cpp

#include <vld.h>

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <cml/cml.h>

#include <math.h>

#include "FileLoader.h"
#include "Game.h"

//************************************************************************************** *
//  Program structure
//************************************************************************************** *
//      INIT
//      MAIN LOOP
    unsigned int Update();
//      SHUTDOWN
    void Shutdown();
//
    
    void CreateObject(char* fileName);
    void CreateShaders();
    void CreateProgram();
    void CollectShaderVariables();
    
    void Draw();

//************************************************************************************** *

    Game g_game;

//-------------------------------------------------------------------------------------- -
//  Main Function
//-------------------------------------------------------------------------------------- -
int main(int argc, char* argv[])
{
    // INIT APPLICATION
    g_game.Init();

    // Object Initialization
    //CreateObject("quad.obj");
    CreateObject("Sphere.obj");
    CreateShaders();
    CreateProgram();
    CollectShaderVariables();

    // MAIN LOOP
    while (Update() == 1) {}

    // SHUTDOWN APPLICATION
    Shutdown();

    return 0;
}

/////////////////////////////////////
//  ELEMENTS TO DRAW GO HERE
/////////////////////////////////////

//Variables
//--------------------------------------
GLuint g_vertexBufferObject = 0;
GLuint g_elementBufferObject = 0;
GLuint g_vertexArrayObject = 0;

std::vector<float> g_verts;
std::vector<unsigned int> g_vertIndices;

//Shaders
//--------------------------------------

GLuint g_vertexShader;
GLuint g_fragmentShader;
GLuint g_shaderProgram;

/////////////////////////////////////

//-------------------------------------------------------------------------------------- -
//  Create Objects Function
//-------------------------------------------------------------------------------------- -
void CreateObject(char* fileName)
{
    ObjFile cubeObj;
    cubeObj.Load(fileName);

    //Allocate memory
    g_verts = cubeObj.GetVerticesAsFloats();
    g_vertIndices = cubeObj.GetFacesAsIndices();

    //VBO
    glGenBuffers(1, &g_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, g_verts.size() * sizeof(float), &g_verts[0], GL_STATIC_DRAW);

    //EBO
    glGenBuffers(1, &g_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_vertIndices.size(), &g_vertIndices[0], GL_STATIC_DRAW);

    //VAO
    glGenVertexArrays(1, &g_vertexArrayObject);
    glBindVertexArray(g_vertexArrayObject);
}

//-------------------------------------------------------------------------------------- -
//  Create Shaders Function 
//      -Will create and compile vertex and fragment shader
//-------------------------------------------------------------------------------------- -
void CreateShaders()
{
    GLint debugInt = 0; //1 == success

    ShaderFile vertexSource, fragmentSource;
    vertexSource.Load("VertexShader.glsl");
    fragmentSource.Load("FragmentShader.glsl");

    g_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    g_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vSource = vertexSource.GetSource();
    glShaderSource(g_vertexShader, 1, &vSource, nullptr);
    glCompileShader(g_vertexShader);

    const char* fSource = fragmentSource.GetSource();
    glShaderSource(g_fragmentShader, 1, &fSource, nullptr);
    glCompileShader(g_fragmentShader);

    char buffer[512] = { 0 };
    glGetShaderInfoLog(g_vertexShader, 512, NULL, buffer);

}

//-------------------------------------------------------------------------------------- -
//  Create Program Function
//      -Will create a program and link shaders to it
//-------------------------------------------------------------------------------------- -
void CreateProgram()
{
    g_shaderProgram = glCreateProgram();
    glAttachShader(g_shaderProgram, g_vertexShader);
    glAttachShader(g_shaderProgram, g_fragmentShader);
    glLinkProgram(g_shaderProgram);
    glBindFragDataLocation(g_shaderProgram, 0, "outColor");
    glUseProgram(g_shaderProgram);

    //Will set attributes for the currently bound VBO
    GLint posAttrib = glGetAttribLocation(g_shaderProgram, "position");
    //posAttrib = 0;
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
}

//-------------------------------------------------------------------------------------- -
//  Collect Shader Variables Function
//      -Gets the location of the uniforms for modulation in update
//-------------------------------------------------------------------------------------- -
GLint g_transformMatrixUniform = 0;
GLint g_viewMatrixUniform = 0;
GLint g_projectionMatrixUniform = 0;

cml::matrix44f_c g_transformMatrix;
cml::matrix44f_c g_viewMatrix;
cml::matrix44f_c g_projectionMatrix;

cml::vector3f g_cameraPosition;

void CollectShaderVariables()
{
    g_transformMatrixUniform = glGetUniformLocation(g_shaderProgram, "transformMatrix");
    g_viewMatrixUniform = glGetUniformLocation(g_shaderProgram, "viewMatrix");
    g_projectionMatrixUniform = glGetUniformLocation(g_shaderProgram, "projectionMatrix");

    //Initializing matrices to 1
    g_transformMatrix.identity();
    g_viewMatrix.identity();
    g_projectionMatrix.identity();

    //Setting camera position
    g_cameraPosition[0] = 0.f;
    g_cameraPosition[1] = 5.f;
    g_cameraPosition[2] = 0.f;

    //Draw in perspective
    cml::matrix_perspective_xfov_RH(g_projectionMatrix, 90.f, 800.f / 600.f, 0.1f, 1000.f, cml::z_clip_neg_one);
}

//-------------------------------------------------------------------------------------- -
//  Main Application Update Function
//-------------------------------------------------------------------------------------- -

//Temp variables to control the camera;
const float k_camSpeed = 0.10f;
float camX = 0.f;
float camY = 0.f;
float camZ = 0.f;

unsigned int Update()
{
    while (true)
    {
        if (g_game.HandleEvents() == 0)
            return 0;   //QUIT
        
        Draw();

        g_game.SwapWindow();
    }

    return 1;   //  Success
}

//-------------------------------------------------------------------------------------- -
//  Main Application Draw Function
//-------------------------------------------------------------------------------------- -
void Draw()
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

    //g_transformMatrix = objectTranslation;
    g_transformMatrix = objectTranslation * objectRotation;

    //Set camera position and target
    cml::vector4f cameraForward(0.f, 0.f, -1.f, 0.f);
    cml::vector3f cameraDirection = (cameraForward).subvector(3);
    cml::vector3f cameraPosition(camX, 0.f, camZ);

    cml::matrix_look_at_RH(g_viewMatrix
                           , cameraPosition                     //Origin
                           , cameraPosition + cameraDirection   //Direction
                           , cml::vector3f(0.f, 1.f, 0.f));     //Up-Direction, Y is up

    //BINDING BUFFERS
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(g_shaderProgram);
    //glBindBuffer(g_vertexBufferObject);
    glBindVertexArray(g_vertexArrayObject);
    glProgramUniformMatrix4fv(g_shaderProgram, g_transformMatrixUniform, 1, GL_FALSE, g_transformMatrix.data());
    glProgramUniformMatrix4fv(g_shaderProgram, g_viewMatrixUniform, 1, GL_FALSE, g_viewMatrix.data());
    glProgramUniformMatrix4fv(g_shaderProgram, g_projectionMatrixUniform, 1, GL_FALSE, g_projectionMatrix.data());
    
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, g_vertIndices.size(), GL_UNSIGNED_INT, &g_vertIndices[0]);
}

//-------------------------------------------------------------------------------------- -
//  Main Application Shutdown Function
//-------------------------------------------------------------------------------------- -
void Shutdown()
{
    g_game.Shutdown();
}