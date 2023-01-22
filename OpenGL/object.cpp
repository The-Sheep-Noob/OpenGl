#include "object.h"
#include <GLEW/glew.h>
#include "abstraction.h"

Object::~Object(){
    glDeleteProgram(program_id);
}

Object::Object() : program_id(glCreateProgram()) , texture("" , 0) {};

void Object::bind(){
    vertexArray.bind();
    glUseProgram(program_id);
}


void Object::setIndexBuffer(unsigned int arr[], int arrSize, int drawType){
    vertexArray.bind();
    indexBuffer.bind();
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

void Object::setTexture(const std::string path , int slot){
    Texture textureGen(path , program_id , slot);
    texture = textureGen;
}


void Object::unbind(){
    glUseProgram(0);
}

unsigned int Object::getProgram(){
    return program_id;
}
