#pragma once
#include "object.h"
#include <vector>
#include <string>


namespace Shapes {
	extern void renderShapes();
	extern std::vector<Object*> sub_objects;
}
// extern keyword = tell compiler that the var is defined somewhere else
class Square : Object {
public:
	void draw();
	Square();
	int R;
	int G;
	int B;
	int A;
	int X;
	int Y;
	int Z;
	int Size;
	std::string Texture;
};