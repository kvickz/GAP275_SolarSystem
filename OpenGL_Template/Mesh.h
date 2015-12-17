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

    GLuint m_vertexNormalBufferObject;
    GLuint m_UVBufferObject;

    std::vector<float> m_verts;
    std::vector<float> m_vertNormals;
    std::vector<unsigned int> m_indices;
    std::vector<unsigned int> m_UVindices;

public:
    Mesh() {};
    Mesh(const char* const fileName);
    ~Mesh();

    GLuint GetVBO() { return m_vertexBufferObject; }
    GLuint GetEBO() { return m_elementBufferObject; }
    GLuint GetVAO() { return m_vertexArrayObject; }
    GLuint GetNormalBuffer() { return m_vertexNormalBufferObject; }
    GLuint GetUVBuffer() { return m_UVBufferObject; }
    std::vector<unsigned int> GetIndices() { return m_indices; }

private:
    void CreateObject();
};

#endif // !MESH_H
