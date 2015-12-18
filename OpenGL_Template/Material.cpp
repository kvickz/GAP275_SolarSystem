//Material.cpp

#include "Material.h"

#include "FileLoader.h"

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL.h>

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
Material::Material()
{
    //
}

Material::Material(const char* const pVertexFilePath, const char* const pFragmentFilePath, Color color)
{
    m_color = color;
    LoadShader(pVertexFilePath, ShaderType::k_vertex);
    LoadShader(pFragmentFilePath, ShaderType::k_fragment);
}

Material::Material(const char* const pVertexFilePath, const char* const pFragmentFilePath, Color color, Color ambientColor)
{
    m_color = color;
    m_ambientColor = ambientColor;
    LoadShader(pVertexFilePath, ShaderType::k_vertex);
    LoadShader(pFragmentFilePath, ShaderType::k_fragment);
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
Material::~Material()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Load Shaders Function 
//      -Will load a shader from filepath
//      -Also will create a 
//-------------------------------------------------------------------------------------- -
void Material::LoadShader(const char* const fileName, ShaderType type)
{
    ShaderPair pTempShader;

    pTempShader.first.Load(fileName);

    //Get Type of shader
    switch (type)
    {
    case ShaderType::k_vertex:
        pTempShader.second = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::k_fragment:
        pTempShader.second = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    
    const char* source = pTempShader.first.GetSource();
    glShaderSource(pTempShader.second, 1, &(source), nullptr);
    glCompileShader(pTempShader.second);

    //Check For compile error
    GLint success = 0;
    glGetShaderiv(pTempShader.second, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        SDL_Log("Shader failed to compile!: %s", fileName);
    }

    //Add temp to list
    m_shaders.emplace(type, pTempShader);

    const int k_bufferSize = 512;
    char buffer[k_bufferSize] = { 0 };
    glGetShaderInfoLog(pTempShader.second, k_bufferSize, NULL, buffer);
}

//-------------------------------------------------------------------------------------- -
//  Get Shader Pointer Function
//-------------------------------------------------------------------------------------- -
const GLuint Material::GetShaderGLPointer(const ShaderType type)
{
    return m_shaders[type].second;
}

//-------------------------------------------------------------------------------------- -
//  Set Color Function
//-------------------------------------------------------------------------------------- -
void Material::SetColor(float r, float g, float b)
{
    m_color = Color(r, g, b);
}

void Material::SetAmbientColor(float r, float g, float b)
{
    m_ambientColor = Color(r, g, b);
}

//-------------------------------------------------------------------------------------- -
//  Set Color Function
//-------------------------------------------------------------------------------------- -
void Material::SetColor(Color color)
{
    m_color = color;
}

void Material::SetAmbientColor(Color color)
{
    m_ambientColor = color;
}