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
                                 , 800, 600
                                 , SDL_WINDOW_OPENGL);

    m_context = SDL_GL_CreateContext(m_pWindow);

    //INIT GLEW
    glewExperimental = GL_TRUE;
    unsigned int debug = glewInit();
}

//-------------------------------------------------------------------------------------- -
//  Handle Events Function
//      -Encapsulates the handling of events
//      -Returns 0 or FALSE for quitting
//-------------------------------------------------------------------------------------- -
int Renderer::HandleEvents()
{
    SDL_Event appEvent;
    while (SDL_PollEvent(&appEvent))
    {
        //-------------------------
        // WINDOW EVENT HANDLING
        //-------------------------
        if (appEvent.type == SDL_QUIT || appEvent.key.keysym.sym == SDLK_ESCAPE)
            return 0;   //QUIT

        //-------------------------
        //KEY HANDLING
        //-------------------------

        //KEY DOWN EVENTS
        if (appEvent.type == SDL_KEYDOWN)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {

            }

            //W key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                
            }

            if (appEvent.key.keysym.sym == SDLK_a)
            {
                
            }

            if (appEvent.key.keysym.sym == SDLK_d)
            {
                
            }
        }

        //KEY UP EVENTS
        if (appEvent.type == SDL_KEYUP)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {

            }

            //W key
            if (appEvent.key.keysym.sym == SDLK_s)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_a)
            {

            }

            if (appEvent.key.keysym.sym == SDLK_d)
            {

            }
        }
    }

    return 1;   //SUCCESS
}

void Renderer::Update()
{
    HandleEvents();
}

void Renderer::Shutdown()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_pWindow);

    SDL_Quit();
}

void Renderer::SwapWindow()
{
    SDL_GL_SwapWindow(m_pWindow);
}