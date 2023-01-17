#include "texture.h"
#include "stb_image.h" // to get image data for texture
#include <iostream>
#include <GLEW/glew.h>


unsigned char* Texture::getTexture(const std::string& path){
    const char* c_str = path.c_str();
    unsigned char* data = stbi_load(c_str, &width, &height , &bitPerPixel , 4); // 4 because 4 channel = R G B A
    return data;
}

Texture::~Texture() {
    glDeleteTextures(1, &texture_id);
}

Texture::Texture(const std::string path, unsigned int program_id) : texture_id(0) , width(0) , height(0) , bitPerPixel(0) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Blending = how texture are rendered

    stbi_set_flip_vertically_on_load(1); // flip texture to render pixels as OpenGL expect us to 
    unsigned char* textureData = getTexture(path);
    std::cout << textureData << std::endl;
    glGenTextures(1, &texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    int uniformLocation = glGetUniformLocation(program_id, "tex"); // integer uniform = texture slot 
    glUniform1i(uniformLocation, 2); // tell shader to get texture from slot 2

    if (textureData)
        stbi_image_free(textureData);
    else
        std::cout << "no data in texture buffer !!!!";
}

void Texture::bind(){
    glActiveTexture(GL_TEXTURE2); // all texture will be bind in slot 2
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}


