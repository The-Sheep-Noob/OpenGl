#pragma once
#include <string>

class Texture {
private:
	unsigned int texture_id;
	unsigned int program_id;
	unsigned char* getTexture(const std::string& path);
public:
	int width;
	int height;
	int bitPerPixel;
	~Texture();
	Texture(const std::string path, unsigned int program_id);
	void bind();
	void unbind();
};
