//Material.h

#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>
#include <string>

#include "Enums.h"
#include "Color.h"

class ShaderFile;
class Texture;

typedef unsigned int GLuint;
typedef std::pair<ShaderFile, GLuint> ShaderPair;

class Material
{
private:
    std::unordered_map<ShaderType, ShaderPair> m_shaders;
    
    Texture* m_pTexture;
    Color m_color;
    Color m_ambientColor;

public:
    Material();
    Material(std::string pVertexFilePath, std::string pFragmentFilePath, Color color);
    Material(std::string pVertexFilePath, std::string pFragmentFilePath, Color color, Color ambientColor);
    ~Material();

    void LoadShader(std::string fileName, ShaderType type);
    const GLuint GetShaderGLPointer(const ShaderType type);
    void SetColor(float r, float g, float b);
    void SetColor(Color color);
    void SetAmbientColor(float r, float g, float b);
    void SetAmbientColor(Color color);
    Color GetColor() const { return m_color; }
    Color& GetColorRef() { return m_color; }
    Color& GetAmbientColorRef() { return m_ambientColor; }

    void LoadTexture(std::string fileName, GLuint shaderProgram);
    GLuint GetTextureBufferObject();
};

#endif // !MATERIAL_H
