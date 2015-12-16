//Time.cpp

#include "Time.h"

#include <SDL.h>

int Time::s_deltaTime = 0;
unsigned long Time::s_elapsedTicks = 0;

Time::Time()
{
    //
}

void Time::Update()
{
    s_deltaTime = SDL_GetTicks() - s_elapsedTicks;
    s_elapsedTicks = SDL_GetTicks();
}