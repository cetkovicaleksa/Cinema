#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    // Flip image vertically to match OpenGL's coordinate system
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    // Force load as RGBA to handle any color space issues
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4);
    if (data)
    {
        std::cout << "Loaded texture: " << path << " (" << width << "x" << height
            << ", original " << nrChannels << " channels, converted to RGBA)" << std::endl;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
