//Renderer.h

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class Renderer
{
private:
    SDL_Window* m_pWindow;
    SDL_GLContext m_context;

public:
    Renderer();
    ~Renderer();

    void Init();
    void Update();
    void Shutdown();

    //int HandleEvents();

    void ClearScreen();
    void SwapWindow();
};

#endif // !RENDERER_H