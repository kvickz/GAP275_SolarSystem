//Color.h

#ifndef COLOR_H
#define COLOR_H

//TODO: Figure out a way to implement this
enum ColorPreset
{
    k_black,
    k_white,
    k_gray,
    k_red,
    k_green,
    k_blue,
    k_numOfColors,
};


struct Color
{
    float r;
    float g;
    float b;

    static const Color m_colors[];

    Color();
    Color(float rValue, float gValue, float bValue);
};

#endif // !COLOR_H

