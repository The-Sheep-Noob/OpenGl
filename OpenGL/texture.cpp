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
Texture::Texture() : slot(0), program_id(0), texture_id(0), width(0), height(0), bitPerPixel(0) {};


Texture::Texture(const std::string path, unsigned int program_id, std::string u_name , int slot) : slot(slot) , program_id(program_id) , texture_id(0), width(0), height(0), bitPerPixel(0) {

    if (path == "" || program_id == 0) {
        return;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Blending = how texture are rendered
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);



    stbi_set_flip_vertically_on_load(1); // flip texture to render pixels as OpenGL expect us to 
    unsigned char* textureData = getTexture(path);

    glGenTextures(1, &texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);


    int uniformLocation = glGetUniformLocation(program_id, u_name.c_str()); // integer uniform = texture slot 
    glUniform1i(uniformLocation, slot); // tell shader to get texture from ${slot}

    if (textureData)
       stbi_image_free(textureData);
    else
      std::cout << "no data in texture buffer !!!!";
}

void Texture::bind(){
 
   std::cout << texture_id << std::endl;
   std::cout << program_id << std::endl;

   glActiveTexture(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}


