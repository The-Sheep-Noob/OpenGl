#pragma once
#include <string>
#include "abstraction.h"


class Object {
private:
	unsigned int program_id;
	int point_count;
	VertexArray vertexArray;
	IndexBuffer indexBuffer;
	VertexBuffer vertexBuffer;
	Texture texture;
public:
	~Object();
	Object();
	void bind();
	void unbind();
	unsigned int getProgram();
	void setIndexBuffer(unsigned int arr[], int arrSize, int drawType);
	void setVertexBuffer(float arr[], int arrSize, int drawType);
	void setVertexBufferLayout(int index, int vertexCount, int stride, int begin=0);
	void setShader(const std::string path, const unsigned int shaderType);
	void setTexture(const std::string path ,std::string name , int slot = 0);
	void setUniform1f(std::string name, float value);
	void setUniformMatrix4fv(std::string name, float* first_value);
	void setUniform2f(std::string name, float value1, float value2);
	void setUniform4f(std::string name, float value1, float value2, float value3, float value4);
	void draw();
};