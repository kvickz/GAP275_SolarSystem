//Color.cpp

#include "Color.h"

const Color Color::m_colors[ColorPreset::k_numOfColors] = {
    Color(0.0f, 0.0f, 0.0f),	//BLACK
    Color(1.0f, 1.0f, 1.0f),	//WHITE
    Color(0.5f, 0.5f, 0.5f),	//GRAY
    Color(1.1f, 0.0f, 0.0f),	//RED
    Color(0.0f, 1.0f, 0.0f),	//GREEN
    Color(0.0f, 0.0f, 1.0f),	//BLUE
};

Color::Color()
{
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(float rValue, float gValue, float bValue)
    :r(rValue)
    , g(gValue)
    , b(bValue)
{
    //
}