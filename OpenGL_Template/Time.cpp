//Time.cpp

#include "Time.h"

#include <SDL.h>

Time::Time()
    :m_deltaTime(0)
    , m_elapsedTicks(0)
{
    //
}

void Time::Update()
{
    m_deltaTime = SDL_GetTicks() - m_elapsedTicks;
    m_elapsedTicks = SDL_GetTicks();
}