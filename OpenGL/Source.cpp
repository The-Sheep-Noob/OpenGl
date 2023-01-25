#include <GLEW/glew.h>
#include<iostream>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <fstream> // = file stream
#include <string> // to use std::getline
#include "object.h"

class SwitchColor {
    private :
        bool canIncrement;
        float increment;
        float& color;
    public:
        SwitchColor(float increment, float& color) : canIncrement(true), increment(increment), color(color) {}

        void Switch() {
            if (canIncrement && (color + increment <= 1.0f)) {
                color += increment;
            }
            else {
                canIncrement = false;

                if (color - increment >= 0.0f) {
                    color -= increment;
                }
                else
                    canIncrement = true;

            }
        }
};

const float height = 680.0f;
const float width = 680.0f;


int main(void) {


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // setting OpenGL to version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting core profile

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "So cool !", NULL , NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); // making a valid glfw window

    glfwSwapInterval(2);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glewInit need to be called after a valid glfw window was made
    if (glewInit() != GLEW_OK) {
        std::cout << "wth bro !" << std::endl;
    }

   
   float smallSquareBuffer[] = {
        -1.0f,-0.9f,
        -1.0f,-1.0f,
        -0.9f,-1.0f,
        -0.9f,-0.9f
    };

   unsigned int indices2[] = { // has to be unsigned
        0,1,2,
        2,3,0,
    };

   Object loading_bar;
   loading_bar.setVertexBuffer(smallSquareBuffer, sizeof(smallSquareBuffer), GL_STATIC_DRAW);
   loading_bar.setVertexBufferLayout(0, 2, sizeof(float) * 2);
   loading_bar.setIndexBuffer(indices2, 6 * sizeof(unsigned int), GL_STATIC_DRAW);
   loading_bar.setShader("F_shader2.shader", GL_FRAGMENT_SHADER);
   loading_bar.setShader("V_shader2.shader", GL_VERTEX_SHADER);
   
   float smallSquareBuffer3[] = {
     1.0f, 1.0f,
     1.0f, 0.9f,
     0.9f, 0.9f,
     0.9f, 1.0f
    };

    unsigned int indices3[] = { // has to be unsigned
         0,1,2,
         2,3,0,
    };

    Object square;
    square.setVertexBuffer(smallSquareBuffer3, sizeof(smallSquareBuffer3), GL_STATIC_DRAW);
    square.setVertexBufferLayout(0, 2, sizeof(float) * 2);
    square.setIndexBuffer(indices3, 6 * sizeof(unsigned int), GL_STATIC_DRAW);
    square.setShader("F_shader2.shader", GL_FRAGMENT_SHADER);
    square.setShader("V_shader2.shader", GL_VERTEX_SHADER);

    float data[] = {
       -0.5f, 0.5f ,0.0f, 1.0f,
       -0.5f, -0.5f,0.0f, 0.0f,
        0.5f, -0.5f,1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,

    };

    unsigned int indices[] = { // has to be unsigned
        0,1,2,
        2,3,0,
    };
    
    Object sheep;
    sheep.setVertexBuffer(data, sizeof(data), GL_STATIC_DRAW);
    sheep.setVertexBufferLayout(0, 2, sizeof(float) * 4);
    sheep.setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    sheep.setIndexBuffer(indices, 6 * sizeof(unsigned int), GL_STATIC_DRAW);
    sheep.setShader("F_shader.shader", GL_FRAGMENT_SHADER);
    sheep.setShader("V_shader.shader", GL_VERTEX_SHADER);
    sheep.setTexture("shaun.png" , "tex");


    float movSheepCoords[] = {
        0.0f, 40.0f, 0.0f, 1.0f,
        0.0f, 0.0f , 0.0f, 0.0f,
        40.0f,0.0f , 1.0f, 0.0f,
        40.0f,40.0f, 1.0f, 1.0f,
    };

    unsigned int movSheepIndices[] = { // has to be unsigned
        0,1,2,
        2,3,0,
    };

    Object movSheep;
    movSheep.setVertexBuffer(movSheepCoords, sizeof(movSheepCoords), GL_STATIC_DRAW);
    movSheep.setVertexBufferLayout(0, 2, sizeof(float) * 4);
    movSheep.setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    movSheep.setIndexBuffer(movSheepIndices, 6 * sizeof(unsigned int), GL_STATIC_DRAW);
    movSheep.setShader("V_sheep.shader", GL_VERTEX_SHADER);
    movSheep.setShader("F_sheep.shader", GL_FRAGMENT_SHADER);
    glm::mat4 sheep_projection = glm::ortho( 0.0f, width, height, 0.0f, -1.0f, 1.0f); // if a vertex is more than the value it will be rendered out of the window
    movSheep.setUniformMatrix4fv("proj", &sheep_projection[0][0]);

    float add = 0;
    float add2 = 0;

    // uniform = way to pass data in a shader -> per draw
    // attribute  -> per vertex

    /* Loop until the user closes the window */

    float red = 0.0f;
    float green = 1.0f;
    float blue = 0.5f;

    SwitchColor redSwitch(0.05f, red);
    SwitchColor greenSwitch(0.05f, green);
    SwitchColor blueSwitch(0.05f, blue);

    glm::mat4 projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f); // if a vertex is more than the value it will be rendered out of the window
    sheep.setUniformMatrix4fv("projection", &projection[0][0]);
    // &projection[0][0] = first matrix element memory location
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        greenSwitch.Switch();
        redSwitch.Switch();
        blueSwitch.Switch();
        sheep.setUniform4f("i_color", red, green, blue, 1.0f);
        sheep.draw();

        //int whichID;
        //glGetIntegerv(GL_TEXTURE_BINDING_2D, &whichID);
        //std::cout << whichID << std::endl;

        add += 0.05f;
        if (add > 1.91f) {
            add = 0.0f;
        }
        loading_bar.setUniform1f("add", add);
        loading_bar.draw();


         add2 -= 0.05f;
         if (add2 < -2.0f) {
             add2 = 0;
         }
        square.setUniform1f("add", add2);
        square.draw();

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        movSheep.setUniform2f("mouse", xpos, ypos);
        movSheep.setUniform1f("colorf",ypos * (1 / height));
        movSheep.draw();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}


       /* // legacy openGL {
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.0f, 0.0f );
        glVertex2f(0.5f, 0.5f );
        glEnd();
        // }
        */