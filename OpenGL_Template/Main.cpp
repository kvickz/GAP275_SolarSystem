//Michael Nevins
//GAP 275 - Solar System Project
//11-26-2015
//Main.cpp

//#include <vld.h>
#include <SDL.h>
#include "Game.h"

//************************************************************************************** *
//  Program structure
//************************************************************************************** *
//  Game makes GameObjects, those objects contain components created from XML files
//  Those components tell the rest of the game what to do.
//
//************************************************************************************** *
    Game g_game;
//-------------------------------------------------------------------------------------- -
//  Main Function
//-------------------------------------------------------------------------------------- -
int main(int argc, char* argv[])
{
    // INIT APPLICATION
    g_game.Init();

    // MAIN LOOP
    while (g_game.Update() == 1) {}

    // SHUTDOWN APPLICATION
    g_game.Shutdown();

    return 0;
}