//Material.h

#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>

#include "Enums.h"
#include "Color.h"

class ShaderFile;

typedef unsigned int GLuint;
typedef std::pair<ShaderFile, GLuint> ShaderPair;

class Material
{
private:
    std::unordered_map<ShaderType, ShaderPair> m_shaders;
    Color m_color;
    Color m_ambientColor;

public:
    Material();
    Material(const char* const pVertexFilePath, const char* const pFragmentFilePath, Color color);
    Material(const char* const pVertexFilePath, const char* const pFragmentFilePath, Color color, Color ambientColor);
    ~Material();

    void LoadShader(const char* const fileName, ShaderType type);
    const GLuint GetShaderGLPointer(const ShaderType type);
    void SetColor(float r, float g, float b);
    void SetColor(Color color);
    void SetAmbientColor(float r, float g, float b);
    void SetAmbientColor(Color color);
    Color GetColor() const { return m_color; }
    Color& GetColorRef() { return m_color; }
    Color& GetAmbientColorRef() { return m_ambientColor; }
};

#endif // !MATERIAL_H
