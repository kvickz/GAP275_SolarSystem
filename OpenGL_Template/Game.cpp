//Game.cpp

#include "Game.h"
#include "Renderer.h"

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