#pragma once
#include <string>

class Texture {
private:
	unsigned int program_id;
	unsigned int texture_id;
	int slot;
	unsigned char* getTexture(const std::string& path);
public:
	int width;
	int height;
	int bitPerPixel;
	~Texture();
	Texture();
	bool exist();
	void setTexture(const std::string path, unsigned int program_id, std::string u_name, bool flipImage, int slot = 0);
	void bind();
	void unbind();
};
