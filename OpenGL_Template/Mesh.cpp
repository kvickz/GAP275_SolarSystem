//Mesh.cpp

#include "Mesh.h"

#include "FileLoader.h"

Mesh::Mesh(const char* const fileName)
    :m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_vertexArrayObject(0)
    , m_vertexNormalBufferObject(0)
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
    m_verts = m_pObjFile->GetVertices();
    m_indices = m_pObjFile->GetVertexIndices();
    m_vertNormals = m_pObjFile->GetVertexNormals();
    m_UVindices = m_pObjFile->GetUVIndices();
    
    //Vertex Normal Buffer
    glGenBuffers(1, &m_vertexNormalBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexNormalBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_vertNormals.size() * sizeof(float), &m_vertNormals[0], GL_DYNAMIC_DRAW);
    /*
    //Texture Coordinate Buffer
    glGenBuffers(1, &m_UVBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_UVBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_UVindices.size(), &m_UVindices[0], GL_DYNAMIC_DRAW);
    */
    
    //VBO
    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(float), &m_verts[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //EBO
    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size(), &m_indices[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //TEXTURE
    //glGenTextures(1, g_)

    //VAO
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
}