#include "shapes.h"
#include <iostream>
#include <vector>


Square::Square() : R(0), G(0), B(0), A(255), Size(1), Texture(""), X(0), Y(0) {

    Shapes::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
      0.9f, 1.0f, 1.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    setUniform1b("has_texture", false);
    glm::mat4 proj = glm::ortho(0.0f, 700.0f, 0.0f, 700.0f, -1.0f, 1.0f); // if a vertex is more than the value it will be rendered out of the window
    setUniformMatrix4fv("mvp", proj);
}

void Square::draw() {

    const float height = 700.0f;
    const float width = 700.0f;
    const int X_size = Size /2;
    const int Y_size = Size /2;
    const float X_1 = X - X_size;
    const float Y_1 = Y - Y_size;
    const float X_2 = X + X_size;
    const float Y_2 = Y + Y_size;

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 0.0f, 1.0f,
      X_2, Y_1, 0.0f, 0.0f,
      X_1, Y_1 , 1.0f, 0.0f,
      X_1, Y_2, 1.0f, 1.0f,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));

    setUniform4f("u_color", (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    if (Texture == "") 
    {
        setUniform1b("has_texture", false);
    } 
    else
    {
        setUniform1b("has_texture", true);
        setTexture(Texture, "c_texture", false);
    }
    Object::draw();
}

void Shapes::renderShapes() 
{
    for (Object* obj : Shapes::sub_objects) {
        obj->draw(); // draw object
    }
}

std::vector<Object*> Shapes::sub_objects = std::vector<Object*>();