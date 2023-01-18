#include <GLEW/glew.h>
#include<iostream>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <fstream> // = file stream
#include <string> // to use std::getline
#include "abstraction.h"

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



int main(void) {


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // setting OpenGL to version 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting core profile

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(680, 680, "So cool !", NULL , NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); // making a valid glfw window

    glfwSwapInterval(5);

    // glewInit need to be called after a valid glfw window was made
    if (glewInit() != GLEW_OK) {
        std::cout << "wth bro !" << std::endl;
    }

   
   float smallSquareBuffer[] = {
        -0.2f,0.2f,
        -0.2f,-0.2f,
         0.2f,-0.2f,
         0.2f, 0.2f
    };

   unsigned int indices2[] = { // has to be unsigned
        0,1,2,
        2,3,0,
    };

    VertexBuffer myVertBuffer2;
    myVertBuffer2.setData(smallSquareBuffer , sizeof(smallSquareBuffer), GL_STATIC_DRAW);
    myVertBuffer2.layout(0, 2, sizeof(float) * 2);

    IndexBuffer myIndexBuffer2;
    myIndexBuffer2.setData(indices2, 6 * sizeof(unsigned int), GL_STATIC_DRAW);

    Shader myFShader2("F_shader2.shader", GL_FRAGMENT_SHADER);
    Shader myVShader2("V_shader2.shader", GL_VERTEX_SHADER, myFShader2.getProgram());
  

    float data[] = {
       -0.7f, 0.5f ,0.0f, 1.0f,
       -0.5f, -0.5f,0.0f, 0.0f,
        0.5f, -0.5f,1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,

    };

    unsigned int indices[] = { // has to be unsigned
        0,1,2,
        2,3,0,
    };
    

    VertexArray myVertexArray;

    VertexBuffer myVertBuffer;
    myVertBuffer.setData(data , sizeof(data), GL_STATIC_DRAW);
    myVertBuffer.layout(0, 2, sizeof(float) * 4);
    myVertBuffer.layout(1, 2, sizeof(float) * 4, sizeof(float) * 2);

    IndexBuffer myIndexBuffer;
    myIndexBuffer.setData(indices, 6 * sizeof(unsigned int), GL_STATIC_DRAW);

    Shader myFShader("F_shader.shader", GL_FRAGMENT_SHADER);
    Shader myVShader("V_shader.shader", GL_VERTEX_SHADER, myFShader.getProgram());

    Texture myTexture("shaun.png" , myFShader.getProgram());

    int addLocation = glGetUniformLocation(myFShader2.getProgram() , "add");
    float add = 0;

    bool nice = true;
    int u_location = glGetUniformLocation(myFShader.getProgram(), "i_color"); // specifing uniform location
    if (u_location == -1) {
        nice = false;
        std::cout << "couldn't find uniform !" << std::endl;
    }
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
    int u2_location = glGetUniformLocation(myFShader.getProgram(), "projection"); // specifing uniform location

    glUniformMatrix4fv(u2_location, 1, GL_FALSE, &projection[0][0]);
    // &projection[0][0] = first matrix element memory location
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

       /* // legacy openGL {
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.0f, 0.0f );
        glVertex2f(0.5f, 0.5f );
        glEnd();
        // }
        */

        greenSwitch.Switch();
        redSwitch.Switch();
        blueSwitch.Switch();

        myVertexArray.bind();
        myIndexBuffer.bind();
        myVertBuffer.bind();
        myFShader.bindProgram();
       // myTexture.bind();

        glUniform4f(u_location, red, green, blue , 1.0f  ); // 4f = 4 floats -> setting uniform value

        //  object to draw , vertices to begin , number of vertices 
       // glDrawArrays(GL_TRIANGLES,0,6); // draw the triangle

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw from a index buffer

        myVertexArray.unbind();
        myIndexBuffer2.bind();
        myVertBuffer2.bind();
        myFShader2.bindProgram();

        add += 0.01f;
        if (add > 0.5f) {
            add = 0.0f;
        }
        glUniform1f(addLocation, add);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw from a index buffer


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}