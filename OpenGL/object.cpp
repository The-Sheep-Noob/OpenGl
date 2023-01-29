#include "object.h"
#include <GLEW/glew.h>
#include "abstraction.h"
#include <iostream>


Object::~Object(){
    glDeleteProgram(program_id);
}

Object::Object() : program_id(glCreateProgram()) , point_count(0) {
    glUseProgram(program_id);
};

void Object::bind(){
    glUseProgram(program_id);
    if (texture.exist()) {
        texture.bind();
    }
    vertexArray.bind();
}


void Object::setIndexBuffer(unsigned int arr[], int arrSize, int drawType){
    vertexArray.bind();
    indexBuffer.bind();
    point_count = arrSize;
    indexBuffer.setData(arr, arrSize, drawType);
}

void Object::setVertexBuffer(float arr[], int arrSize, int drawType){
    vertexBuffer.bind();
    vertexBuffer.setData(arr,arrSize , drawType);
}
void Object::setVertexBufferLayout(int index, int vertexCount, int stride, int begin) {
    vertexBuffer.bind();
    vertexBuffer.layout(index , vertexCount , stride , begin);
}

void Object::setShader(const std::string path, const unsigned int shaderType){
    Shader shader(path , shaderType , program_id);
}

void Object::setTexture(const std::string path , std::string name , bool flipImage, int slot){
    std::cout << "texture added to program " << program_id << std::endl;
    glUseProgram(program_id);
    texture.setTexture( path , program_id ,name ,flipImage, slot );
}


void Object::unbind(){
    glUseProgram(0);
}

unsigned int Object::getProgram(){
    return program_id;
}


void Object::setUniform1f(std::string name, float value) {

    glProgramUniform1f(
        program_id,
        glGetUniformLocation(program_id, name.c_str()),
        value
    );
}

void Object::setUniform4f(std::string name, float value1 , float value2 , float value3 , float value4) {

    glProgramUniform4f(
        program_id,
        glGetUniformLocation(program_id, name.c_str()),
        value1 , value2, value3 , value4
    );
}

void Object::setUniform2f(std::string name, float value1, float value2) {

    glProgramUniform2f(
        program_id,
        glGetUniformLocation(program_id, name.c_str()),
        value1, value2
    );
}


void Object::setUniformMatrix4fv(std::string name, glm::mat4& first_value) {
    glProgramUniformMatrix4fv(
        program_id,
        glGetUniformLocation(program_id, name.c_str()),
        1, GL_FALSE, 
        &first_value[0][0]
    );

}

void Object::draw() {
    if (!point_count) {
        std::cout << "nothing to draw !" << std::endl;
        return;
    }
    bind();
    glDrawElements(GL_TRIANGLES, point_count, GL_UNSIGNED_INT, nullptr);
}