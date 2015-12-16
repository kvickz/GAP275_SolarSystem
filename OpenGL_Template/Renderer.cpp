//Renderer.cpp

#include "Renderer.h"

Renderer::Renderer()
    :m_pWindow(nullptr)
{
    //
}

Renderer::~Renderer()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Renderer Initialization Function
//      -Wraps SDL Functionality
//      -Creates SDL window and GLContext
//-------------------------------------------------------------------------------------- -
void Renderer::Init()
{
    //SDL INIT
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

    //CREATE WINDOW
    m_pWindow = SDL_CreateWindow("OpenGL Tut"
                                 , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
                                 , k_screenWidth, k_screenHeight
                                 , SDL_WINDOW_OPENGL);

    m_context = SDL_GL_CreateContext(m_pWindow);

    //INIT GLEW
    glewExperimental = GL_TRUE;
    unsigned int debug = glewInit();

    //Setting clear color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    //Setting polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//-------------------------------------------------------------------------------------- -
//  Renderer Update Function
//      -functions as a basic loop to encapsulate drawing behaviors
//-------------------------------------------------------------------------------------- -
void Renderer::Update()
{
    //
}

void Renderer::Shutdown()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}

void Renderer::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapWindow()
{
    SDL_GL_SwapWindow(m_pWindow);
}