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

    std::string temp;

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
// Skip Function
//      -Skips the line while parsing a file
//-------------------------------------------------------------------------------------- -
void ObjFile::Skip(std::string currentLine) { }

//-------------------------------------------------------------------------------------- -
// Get Vertex Geometry Function
//-------------------------------------------------------------------------------------- -
void ObjFile::GetVertGeometry(std::string currentLine)
{
    const int k_startOffset = 2;

    std::string tempString;

    //Read the line
    for (unsigned int i = k_startOffset; i <= currentLine.size(); ++i)
    {
        if (currentLine[i] == SPACE || currentLine[i] == NEWLINE)
        {
            float convertedString = (float)::atof(tempString.c_str());    //Convert to a float
            m_verticesAsFloats.push_back(convertedString);                //push it back
            tempString.clear();                                           //Clear the string
        }
        else
        {
            tempString += currentLine[i];
        }
    }
}

//-------------------------------------------------------------------------------------- -
// Get Vertex Texture Function
//-------------------------------------------------------------------------------------- -
void ObjFile::GetVertTexture(std::string currentLine)
{
    const int k_startOffset = 3;

    std::string tempString;

    //Read the line
    for (unsigned int i = k_startOffset; i <= currentLine.size(); ++i)
    {
        if (currentLine[i] == SPACE || currentLine[i] == NEWLINE)
        {
            float convertedString = (float)::atof(tempString.c_str());    //Convert to a float
            m_textureVerticesAsFloats.push_back(convertedString);         //push it back
            tempString.clear();                                           //Clear the string
        }
        else
        {
            tempString += currentLine[i];
        }
    }
}

//-------------------------------------------------------------------------------------- -
// Get Vertex Normal Function
//-------------------------------------------------------------------------------------- -
void ObjFile::GetVertNormal(std::string currentLine)
{
    const int k_startOffset = 3;

    std::string tempString;

    //Read the line
    for (unsigned int i = k_startOffset; i <= currentLine.size(); ++i)
    {
        if (currentLine[i] == SPACE || currentLine[i] == NEWLINE)
        {
            float convertedString = (float)::atof(tempString.c_str());      //Convert to a float
            m_vertexNormals.push_back(convertedString);                     //push it back
            tempString.clear();                                             //Clear the string
        }
        else
        {
            tempString += currentLine[i];
        }
    }
}

//-------------------------------------------------------------------------------------- -
// Get Vertex Faces Function
//-------------------------------------------------------------------------------------- -
void ObjFile::GetFaces(std::string currentLine)
{
    const int k_startOffset = 2;
    unsigned int faceTypeIndex = 0;
    std::string tempString;

    //Read the line
    for (unsigned int i = k_startOffset; i <= currentLine.size(); ++i)
    {
        char currentChar = currentLine[i];
        if (currentChar == SPACE || currentChar == NEWLINE || currentChar == FORWARDSLASH)
        {
            unsigned int convertedString = (unsigned int)::atoi(tempString.c_str()) - 1;    //convert 1-based indexing to 0

            switch (faceTypeIndex)
            {
            case 0:
                m_faceIndices.push_back(convertedString);
                break;
            case 1:
                m_faceTexCoordIndices.push_back(convertedString);
                break;
            case 2:
                m_vertNormalIndices.push_back(convertedString);
                break;
            }
            
            tempString.clear();

            if (currentChar == FORWARDSLASH)
                ++faceTypeIndex;
            else if (currentChar == SPACE)
                faceTypeIndex = 0;
        }
        else
        {
            tempString += currentChar;
        }
    }
}

//---------------------------------------------------------------------------- -
//  Get Vertices Function
//      -Returns the vertices in the form of structs.
//---------------------------------------------------------------------------- -
const std::vector<Vertex>& ObjFile::GetVerticesAsStructs() const
{
    return m_vertices;   
}

//---------------------------------------------------------------------------- -
//  Get Vertices Function
//      -Returns the vertices in the form of floats.
//---------------------------------------------------------------------------- -
std::vector<float>& ObjFile::GetVerticesAsFloats()
{
    return m_verticesAsFloats;
}

const std::vector<Face>& ObjFile::GetFacesAsStructs() const
{
    return m_faces;
}

//---------------------------------------------------------------------------- -
//  Get Faces Function
//      -Returns the vertices in the form of floats.
//---------------------------------------------------------------------------- -
std::vector<unsigned int>& ObjFile::GetFacesAsIndices()
{
    return m_faceIndices;
}

bool ShaderFile::Load(std::string fileName)
{
    std::ifstream tempStream;
    m_fileSource.clear();

    tempStream.open(fileName);

    std::string currentLine;

    while (std::getline(tempStream, currentLine))
    {
        m_fileSource += currentLine + "\n";
    }

    m_fileName = fileName;

    return true;
}