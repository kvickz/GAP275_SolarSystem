//Texture.h

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

typedef signed int GLint;
typedef unsigned int GLuint;

class Texture
{
private:
    std::string m_fileName;
    GLuint m_textureObject;
    GLuint m_textureUniform;

    int m_width;
    int m_height;

public:
    Texture(std::string pFilePath);
    ~Texture();

    void InitTexture(GLuint shaderProgram);

    GLuint GetTextureObject() { return m_textureObject; }
};

#endif // !TEXTURE_H
