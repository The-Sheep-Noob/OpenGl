#pragma once
#include <string>
#include "abstraction.h"


class Object {
private:
	unsigned int program_id;
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
	void setTexture(const std::string path , int slot=0);
};
