//Texture.cpp

#include "Texture.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include "Simple OpenGL Image Library\src\SOIL.h"

Texture::Texture(std::string pFilePath)
{
    //Create texture object
    glGenTextures(1, &m_textureObject);

    m_fileName = pFilePath;
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureObject);
}

void Texture::InitTexture(GLuint shaderProgram)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureObject);

    //Load Image
    unsigned char* pImage;
    pImage = SOIL_load_image(m_fileName.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage);
    SOIL_free_image_data(pImage);

    //Get uniform
    m_textureUniform = glGetUniformLocation(shaderProgram, "objectTexture");
    glUniform1i(m_textureUniform, 0);

    if (m_textureUniform == -1)
    {
        SDL_Log("Error in InitTexture()");
    }

    //WRAPPING PARAMETERS
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint uniforms;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniforms);
}