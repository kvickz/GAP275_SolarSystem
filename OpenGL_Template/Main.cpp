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
    g_game.CreateObject("Sphere.obj");
    g_game.CreateShaders();
    g_game.CreateProgram();
    g_game.CollectShaderVariables();

    // MAIN LOOP
    while (Update() == 1) {}

    // SHUTDOWN APPLICATION
    Shutdown();

    return 0;
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
}

//-------------------------------------------------------------------------------------- -
//  Main Application Shutdown Function
//-------------------------------------------------------------------------------------- -
void Shutdown()
{
    g_game.Shutdown();
}