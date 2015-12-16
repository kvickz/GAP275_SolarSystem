//FileLoader.h

#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>

struct Vertex
{
    float x;
    float y;
    float z;
};

struct Face
{
    int indexX;
    int indexY;
    int indexZ;
};

typedef unsigned int GLuint;

class ShaderFile
{
private:
    std::string m_fileName;
    std::string m_fileSource;

public:
    //bool Load(const char* fileName);
	bool Load(std::string fileName);
    const char* GetSource() const
    {
        return m_fileSource.c_str();
    }
};

class ObjFile
{

private:
    std::string m_fileName;
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    std::vector<float> m_verticesAsFloats;
    std::vector<unsigned int> m_facesAsIndices;

public:
	bool Load(std::string fileName);
    void RetrieveVertsFromFile();
    void RetrieveFacesFromFile();

    const std::vector<Vertex>& GetVerticesAsStructs() const;
    std::vector<float>& GetVerticesAsFloats();
    const std::vector<Face>& GetFacesAsStructs() const;
    std::vector<unsigned int>& ObjFile::GetFacesAsIndices();

    unsigned int GetNumberOfIndices() const { return m_facesAsIndices.size(); }
    void* GetStartingIndexAddress() { return &m_facesAsIndices[0]; }
};

#endif // !FILELOADER_H