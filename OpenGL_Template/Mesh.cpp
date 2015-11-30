//Mesh.cpp

#include "Mesh.h"

#include "FileLoader.h"

Mesh::Mesh(const char* const fileName)
    :m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_vertexArrayObject(0)
{
    m_pObjFile = new ObjFile;
    m_pObjFile->Load(fileName);

    CreateObject();
}

Mesh::~Mesh()
{
    //TODO: Safe delete
    delete m_pObjFile;
    m_pObjFile = nullptr;
}

void Mesh::CreateObject()
{
    //Allocate memory
    m_verts = m_pObjFile->GetVerticesAsFloats();
    m_indices = m_pObjFile->GetFacesAsIndices();

    //VBO
    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(float), &m_verts[0], GL_DYNAMIC_DRAW);

    //EBO
    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size(), &m_indices[0], GL_DYNAMIC_DRAW);

    //VAO
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
}