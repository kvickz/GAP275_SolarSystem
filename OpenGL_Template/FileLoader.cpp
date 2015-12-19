//FileLoader.cpp

#include "FileLoader.h"

#include <SDL.h>    //TODO: Extract out to debug class
#include <fstream>

#define SPACE ' '
#define NEWLINE '\0' 
#define FORWARDSLASH '/'

ObjFile::ObjFile()
{
    //Initialize the data table
    m_objDataTable.emplace("v", ObjDataID::k_vertGeo);
    m_objDataTable.emplace("vt", ObjDataID::k_vertTexture);
    m_objDataTable.emplace("vn", ObjDataID::k_vertNormal);
    m_objDataTable.emplace("f", ObjDataID::k_face);
    m_objDataTable.emplace("\n", ObjDataID::k_newLine);
    m_objDataTable.emplace("#", ObjDataID::k_comment);

    //Initialize the data/function table, linking functions to object data
    m_dataFunctionTable.emplace(ObjDataID::k_vertGeo, &ObjFile::GetVertGeometry);
    m_dataFunctionTable.emplace(ObjDataID::k_vertTexture, &ObjFile::GetVertTexture);
    m_dataFunctionTable.emplace(ObjDataID::k_vertNormal, &ObjFile::GetVertNormal);
    m_dataFunctionTable.emplace(ObjDataID::k_face, &ObjFile::GetFaces);
    m_dataFunctionTable.emplace(ObjDataID::k_newLine, &ObjFile::Skip);
    m_dataFunctionTable.emplace(ObjDataID::k_comment, &ObjFile::Skip);
    m_dataFunctionTable.emplace(ObjDataID::k_undefined, &ObjFile::Skip);
}

bool ObjFile::Load(std::string fileName)
{
    m_fileName = fileName;
    return ParseFile();
}

//-------------------------------------------------------------------------------------- -
// Parse File Function
//      -Encapsulates all the functionality to parse an obj file
//-------------------------------------------------------------------------------------- -
bool ObjFile::ParseFile()
{
    std::ifstream tempStream;
    tempStream.open(m_fileName);

    //Failed to open file
    if (!tempStream.is_open())
    {
        SDL_Log("Failed to open file: %s", m_fileName);
        return false;
    }

    //Loop through entire file
    while (!tempStream.eof())
    {
        //Get current line
        std::string currentLine;
        std::getline(tempStream, currentLine);

        //Figure out which type of data it is
        ObjDataID id;
        GetDataType(id, currentLine);

        //Delegate the logic based on type
        HandleType(id, currentLine);
    }

    tempStream.close();
    return true;
}

//-------------------------------------------------------------------------------------- -
// Get Data Type Function
//      -Determines what kind of data to parse through
//-------------------------------------------------------------------------------------- -
void ObjFile::GetDataType(ObjDataID& objDataID, std::string currentLine)
{
    //Get the first char
    std::string firstWord;

    //Add the first word to firstWorld
    for (unsigned int i = 0; i < currentLine.size(); ++i)
    {
        if (currentLine[i] == SPACE)
            break;

        firstWord += currentLine[i];
    }

    //Check if the type exists
    auto findIt = m_objDataTable.find(firstWord);

    if (findIt != m_objDataTable.end())
        objDataID = m_objDataTable[firstWord];   //return type
    else
        objDataID = ObjDataID::k_undefined;      //Not found

}

//-------------------------------------------------------------------------------------- -
// Handle Type Function
//      -Call the function tied to the data type
//-------------------------------------------------------------------------------------- -
void ObjFile::HandleType(const ObjDataID objDataID, std::string currentLine)
{
    (this->*m_dataFunctionTable[objDataID])(currentLine);
}

//-------------------------------------------------------------------------------------- -
// Delegation Functions
//      -Each function is responsible for certain types of data in obj files
//       this data is represented by the first set of letters on each new line.
//-------------------------------------------------------------------------------------- -
void ObjFile::Skip(std::string currentLine) { }

void ObjFile::GetVertGeometry(std::string currentLine)
{
    GenericGetVertexData(currentLine, 2, m_vertices);
}

void ObjFile::GetVertTexture(std::string currentLine)
{
    GenericGetVertexData(currentLine, 3, m_textureVerticesAsFloats);
}

void ObjFile::GetVertNormal(std::string currentLine)
{
    GenericGetVertexData(currentLine, 3, m_vertexNormals);
}

//***************************
//      GET VERTS
//***************************
void ObjFile::GenericGetVertexData(std::string currentLine, int startOffset, std::vector<float>& collection)
{
    std::string tempString;

    //Read the line
    for (unsigned int i = startOffset; i <= currentLine.size(); ++i)
    {
        if (currentLine[i] == SPACE || currentLine[i] == NEWLINE)
        {
            float convertedString = (float)::atof(tempString.c_str());    //Convert to a float
            collection.push_back(convertedString);                //push it back
            tempString.clear();                                           //Clear the string
        }
        else
        {
            tempString += currentLine[i];
        }
    }
}

//***************************
//      GET FACES
//***************************
void ObjFile::GetFaces(std::string currentLine)
{
    const int k_startOffset = 2;
    unsigned int indicesCollectionIndex = 0;
    std::string tempString;

    std::vector<unsigned int>* pIndexCollections[3];
    pIndexCollections[0] = &m_vertexIndices;
    pIndexCollections[1] = &m_uvIndices;
    pIndexCollections[2] = &m_normalIndices;

    //Read the line
    for (unsigned int i = k_startOffset; i <= currentLine.size(); ++i)
    {
        char currentChar = currentLine[i];
        if (currentChar == SPACE || currentChar == NEWLINE || currentChar == FORWARDSLASH)
        {
            //Convert value from string to int, also convert 1-based indexing from obj to 0
            unsigned int convertedString = (unsigned int)::atoi(tempString.c_str()) - 1;    

            //Push the value to the appropriate collection
            pIndexCollections[indicesCollectionIndex]->push_back(convertedString);
            
            //Clear and reset
            tempString.clear();

            //Iterate the index if necessary, if not, just reset
            if (currentChar == FORWARDSLASH)
                ++indicesCollectionIndex;
            else if (currentChar == SPACE)
                indicesCollectionIndex = 0;
        }
        else
        {
            tempString += currentChar;
        }
    }
}

//---------------------------------------------------------------------------- -
//  Get Vertices Function
//      -Returns the vertices in the form of floats.
//---------------------------------------------------------------------------- -
std::vector<float>& ObjFile::GetVertices()
{
    return m_vertices;
}

//---------------------------------------------------------------------------- -
//  Get Vertex Normals Function
//      -Returns the vertex normals in the form of floats.
//---------------------------------------------------------------------------- -
std::vector<float>& ObjFile::GetVertexNormals()
{
    return m_vertexNormals;
}

//---------------------------------------------------------------------------- -
//  Get UV Texture Coordinates Function
//      -Returns the texture coordinates in the form of unsigned ints.
//---------------------------------------------------------------------------- -
std::vector<unsigned int>& ObjFile::GetUVIndices()
{
    return m_uvIndices;
}

//---------------------------------------------------------------------------- -
//  Get Faces Function
//      -Returns the vertices in the form of unsigned ints.
//---------------------------------------------------------------------------- -
std::vector<unsigned int>& ObjFile::GetVertexIndices()
{
    return m_vertexIndices;
}

//---------------------------------------------------------------------------- -
//  Get Faces Function
//      -Returns the vertices in the form of unsigned ints.
//---------------------------------------------------------------------------- -
std::vector<unsigned int>& ObjFile::GetVertNormalIndices()
{
    return m_normalIndices;
}


//---------------------------------------------------------------------------- -
//  Load Function
//      -Takes in a string of a filename
//---------------------------------------------------------------------------- -
bool ShaderFile::Load(std::string fileName)
{
    std::ifstream tempStream;
    m_fileSource.clear();

    tempStream.open(fileName);

    //Failed to open file
    if (!tempStream.is_open())
    {
        SDL_Log("Failed to open file: %s", m_fileName);
        return false;
    }

    std::string currentLine;

    while (std::getline(tempStream, currentLine))
    {
        m_fileSource += currentLine + "\n";
    }

    m_fileName = fileName;

    return true;
}