//Vector2.cpp

#include "Vector2.h"

//-------------------------------------------------------------------------------------- -
//  Vector 2 Float
//-------------------------------------------------------------------------------------- -
Vector2_f::Vector2_f()
	:x(0)
	, y(0)
{

}

Vector2_f::Vector2_f(float x, float y)
{
    this->x = x;
    this->y = y;
}

//-------------------------------------------------------------------------------------- -
//  Vector 2 Int
//-------------------------------------------------------------------------------------- -
Vector2_i::Vector2_i()
    :x(0)
    , y(0)
{

}

Vector2_i::Vector2_i(int x, int y)
{
    this->x = x;
    this->y = y;
}