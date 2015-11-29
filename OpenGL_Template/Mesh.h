//Mesh.h

#ifndef MESH_H
#define MESH_H

#include <gl\glew.h>
#include <SDL_opengl.h>

#include <vector>

class ObjFile;

typedef unsigned int GLuint;

class Mesh
{
private:
    ObjFile* m_pObjFile;

    //  BUFFER OBJECTS
    GLuint m_vertexBufferObject;
    GLuint m_elementBufferObject;
    GLuint m_vertexArrayObject;

    std::vector<float> m_verts;
    std::vector<unsigned int> m_indices;

public:
    Mesh(const char* const fileName);
    ~Mesh();

    GLuint GetVBO() { return m_vertexBufferObject; }
    GLuint GetEBO() { return m_elementBufferObject; }
    GLuint GetVAO() { return m_vertexArrayObject; }
    std::vector<unsigned int> GetIndices() { return m_indices; }

private:
    void CreateObject();
};

#endif // !MESH_H
