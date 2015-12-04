//Utility.h

#ifndef UTILITY_H
#define UTILITY_H

#include <SDL.h>

#include <climits>

class Utility
{
public:
    //Clamps value from minimum to maximum
    static void Clamp(int& a, int min, int max)
    {
        //Invalid case
        if (max < min)
        {
            SDL_Log("Clamp failed, improper inputs");
            return;
        }

        if (a < min)
            a = min;
          
        if (a > max)
            a = max;
    }

};

#endif // !UTILITY_H
