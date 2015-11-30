//Material.cpp

#include "Material.h"

#include "FileLoader.h"

#include <gl\glew.h>
#include <SDL_opengl.h>

Material::Material()
{
    //
}

Material::Material(char* pVertexFilePath, char* pFragmentFilePath)
{
    LoadShader(pVertexFilePath, ShaderType::k_vertex);
    LoadShader(pFragmentFilePath, ShaderType::k_fragment);
}

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

    //Add temp to list
    m_shaders.emplace(type, pTempShader);

    const int k_bufferSize = 512;
    char buffer[k_bufferSize] = { 0 };
    glGetShaderInfoLog(pTempShader.second, k_bufferSize, NULL, buffer);
}

const GLuint Material::GetShaderGLPointer(const ShaderType type)
{
    return m_shaders[type].second;
}