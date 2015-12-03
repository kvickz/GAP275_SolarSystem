//Material.h

#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>

#include "Enums.h"

class ShaderFile;

typedef unsigned int GLuint;
typedef std::pair<ShaderFile, GLuint> ShaderPair;

class Material
{
private:
    std::unordered_map<ShaderType, ShaderPair> m_shaders;

public:
    Material();
    Material(const char* const pVertexFilePath, const char* const pFragmentFilePath);
    ~Material();

    void LoadShader(const char* const fileName, ShaderType type);
    const GLuint GetShaderGLPointer(const ShaderType type);
};

#endif // !MATERIAL_H
