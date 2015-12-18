//Vector3.cpp

#include "Vector3.h"

#include <math.h>

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::SetValue(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Add(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}

//ADDITION
Vector3 Vector3::operator+(Vector3 b)
{
    Vector3 resultant;
    resultant.x = x + b.x;
    resultant.y = y + b.y;
    resultant.z = z + b.z;
    return resultant;
}

//SUBTRACTION
Vector3 Vector3::operator-(Vector3 b)
{
    Vector3 resultant;
    resultant.x = x - b.x;
    resultant.y = y - b.y;
    resultant.z = z - b.z;
    return resultant;
}

//MULTIPLICATION
Vector3 Vector3::operator*(float b)
{
    Vector3 resultant;
    resultant.x = x * b;
    resultant.y = y * b;
    resultant.z = z * b;
    return resultant;
}

//DIVISION
Vector3 Vector3::operator/(float b)
{
    Vector3 resultant;
    resultant.x = x / b;
    resultant.y = y / b;
    resultant.z = z / b;
    return resultant;
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
    Vector3 distance(a.x - b.x, a.y - b.y, a.z - b.z);
    //float magnitude = sqrtf(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
    return distance.Magnitude();
}

float Vector3::Magnitude()
{
    return (sqrtf(x * x + y * y + z * z));
}

Vector3 Vector3::Normalized()
{
    float magnitude = Magnitude();
    Vector3 normalizedVector(x / magnitude
                             , y / magnitude
                             , z / magnitude);

    return normalizedVector;
}