//FileLoader.h

#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>
#include <unordered_map>

//=========================================================
//  Vertex Struct
//*********************************************************
struct Vertex
{
    float x;
    float y;
    float z;
};

//=========================================================
//  Face Struct
//*********************************************************
struct Face
{
    int indexX;
    int indexY;
    int indexZ;
};

typedef unsigned int GLuint;

//=========================================================
//  Shader File Class
//---------------------------------------------------------
class ShaderFile
{
private:
    std::string m_fileName;
    std::string m_fileSource;

public:
	bool Load(std::string fileName);
    const char* GetSource() const
    {
        return m_fileSource.c_str();
    }
};

//=========================================================
//  Obj File Class
//---------------------------------------------------------
class ObjFile
{
private:
    enum ObjDataID
    {
        k_vertGeo,
        k_vertTexture,
        k_vertNormal,
        k_face,
        k_comment,
        k_newLine,
        k_undefined,
    };

    typedef void(ObjFile::*ParsingFunction)(std::string currentLine);   //Function pointer for hash table
    typedef std::unordered_map<std::string, ObjDataID> ObjDataTable;
    typedef std::unordered_map<ObjDataID, ParsingFunction> ObjDataFunctionTable;

    ObjDataTable m_objDataTable;
    ObjDataFunctionTable m_dataFunctionTable;

    std::string m_fileName;
    std::vector<Vertex> m_vertices;
    std::vector<Vertex> m_textureVertices;
    std::vector<Face> m_faces;
    std::vector<float> m_textureVerticesAsFloats;
    std::vector<float> m_verticesAsFloats;
    std::vector<float> m_vertexNormals;
    std::vector<unsigned int> m_faceIndices;
    std::vector<unsigned int> m_faceTexCoordIndices;
    std::vector<unsigned int> m_vertNormalIndices;

public:
    ObjFile();

	bool Load(std::string fileName);

    const std::vector<Vertex>& GetVerticesAsStructs() const;
    std::vector<float>& GetVerticesAsFloats();
    const std::vector<Face>& GetFacesAsStructs() const;
    std::vector<unsigned int>& ObjFile::GetFacesAsIndices();

    unsigned int GetNumberOfIndices() const { return m_faceIndices.size(); }
    void* GetStartingIndexAddress() { return &m_faceIndices[0]; }

private:
    bool ParseFile();

    void GetDataType(ObjDataID& objDataID, std::string currentLine);
    void HandleType(const ObjDataID objDataID, std::string currentLine);

    void Skip(std::string currentLine);    //Used for unsupported data types
    void GetVertGeometry(std::string currentLine);
    void GetVertTexture(std::string currentLine);
    void GetVertNormal(std::string currentLine);
    void GetFaces(std::string currentLine);

    void RetrieveVertsFromFile();
    void RetrieveFacesFromFile();
};

#endif // !FILELOADER_H