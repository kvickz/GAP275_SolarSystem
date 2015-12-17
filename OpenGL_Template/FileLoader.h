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

    std::vector<float> m_textureVerticesAsFloats;
    std::vector<float> m_vertices;
    std::vector<float> m_vertexNormals;
    std::vector<unsigned int> m_vertexIndices;
    std::vector<unsigned int> m_uvIndices;
    std::vector<unsigned int> m_normalIndices;

public:
    ObjFile();

	bool Load(std::string fileName);

    std::vector<float>& GetVertices();
    std::vector<float>& GetVertexNormals();
    std::vector<unsigned int>& ObjFile::GetVertexIndices();
    std::vector<unsigned int>& ObjFile::GetVertNormalIndices();
    std::vector<unsigned int>& ObjFile::GetUVIndices();

    unsigned int GetNumberOfIndices() const { return m_vertexIndices.size(); }
    void* GetStartingIndexAddress() { return &m_vertexIndices[0]; }

private:
    bool ParseFile();

    void GetDataType(ObjDataID& objDataID, std::string currentLine);
    void HandleType(const ObjDataID objDataID, std::string currentLine);

    void Skip(std::string currentLine);    //Used for unsupported data types
    void GetVertGeometry(std::string currentLine);
    void GetVertTexture(std::string currentLine);
    void GetVertNormal(std::string currentLine);

    void GenericGetVertexData(std::string currentLine, int startOffset, std::vector<float>& collection);

    void GetFaces(std::string currentLine);

};

#endif // !FILELOADER_H