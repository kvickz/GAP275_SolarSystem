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

    const unsigned int k_screenWidth = 1200;
    const unsigned int k_screenHeight = 800;

public:
    Renderer();
    ~Renderer();

    void Init();
    void Update();
    void Shutdown();

    //int HandleEvents();

    void ClearScreen();
    void SwapWindow();

    float GetAspectRatio() const { return (float)k_screenWidth / (float)k_screenHeight; }
};

#endif // !RENDERER_H