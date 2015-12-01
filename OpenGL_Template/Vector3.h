//Vector3.h

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);

    //Sets the vector to (0, 0, 0)
    void Identity() { x = 1; y = 1; z = 1; };
    void Zero() { x = 0; y = 0; z = 0; };

    void SetValue(float x, float y, float z);
    void Add(float x, float y, float z);
};

#endif // !VECTOR3_H