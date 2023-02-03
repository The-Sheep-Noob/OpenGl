#include <GLEW/glew.h>
#include<iostream>
#include <GLFW/glfw3.h>
#include <fstream> // = file stream
#include <string> // to use std::getline
#include "object.h"
#include "camera.h"
#include "stb_image.h" 
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"

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

    //glfwSwapInterval(2);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glewInit need to be called after a valid glfw window was made
    if (glewInit() != GLEW_OK) {
        std::cout << "wth bro !" << std::endl;
    }



   ImGui::CreateContext();
   ImGui_ImplGlfwGL3_Init(window, true);
   ImGui::StyleColorsDark();


   
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
    sheep.setTexture("shaun.png" , "tex" , true);


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
    movSheep.setTexture("Lightning.png", "texture" , false);
    glm::mat4 sheep_projection = glm::ortho( 0.0f, width, height, 0.0f, -1.0f, 1.0f); // if a vertex is more than the value it will be rendered out of the window
    glm::mat4 sheep_model = glm::translate(glm::mat4(0.1f) , glm::vec3(-20 , -20 ,0));
    glm::mat4 mvp = sheep_projection * sheep_model;
    //mvp = model (object translation) view (camera) projection (window size)
    movSheep.setUniformMatrix4fv("mvp", mvp);




    float mtCoords[] = {
    0.0f, 0.25f, 0.0f, 0.9f, 0.0f,
   -0.2f, -0.1f , 0.0f, 0.0f, 0.6f,
    0.2f, -0.1f , 0.3f, 0.0f, 0.0f,
    };

    unsigned int mtIndices[] = { // has to be unsigned
        0,1,2,
    };

    Object mt;
    mt.setVertexBuffer(mtCoords, sizeof(mtCoords), GL_STATIC_DRAW);
    mt.setVertexBufferLayout(0, 2, sizeof(float) * 5);
    mt.setVertexBufferLayout(1, 3, sizeof(float) * 5, sizeof(float) * 2);
    mt.setIndexBuffer(mtIndices, 3 * sizeof(unsigned int), GL_STATIC_DRAW);
    mt.setShader("V_mt.shader", GL_VERTEX_SHADER);
    mt.setShader("F_mt.shader", GL_FRAGMENT_SHADER);
    glm::mat4 camera = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0));
    mt.setUniformMatrix4fv("cam", camera);


    float add = 0;
    float add2 = 0;

    // uniform = way to pass data in a shader -> per draw
    // attribute  -> per vertex

    /* Loop until the user closes the window */

    float red = 0.0f;
    float green = 1.0f;
    float blue = 0.5f;

    SwitchColor redSwitch(0.01f, red);
    SwitchColor greenSwitch(0.01f, green);
    SwitchColor blueSwitch(0.01f, blue);

    glm::mat4 projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f); // if a vertex is more than the value it will be rendered out of the window
    
    sheep.setUniformMatrix4fv("projection", projection);

    ImVec4 clear_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);

    Camera my_camera = Camera(0.02f, "cam");
    my_camera.addObjectToCamera(&mt);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();

        {
     
            ImGui::Text("Change cursor color:");
            ImGui::ColorEdit4("cursor color", (float*)&clear_color);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        
        my_camera.setCameraPosition(window);
        greenSwitch.Switch();
        redSwitch.Switch();
        blueSwitch.Switch();
        sheep.setUniform4f("i_color", red, green, blue, 1.0f);
        sheep.draw();

        //int whichID;
        //glGetIntegerv(GL_TEXTURE_BINDING_2D, &whichID);
        //std::cout << whichID << std::endl;

        add += 0.01f;
        if (add > 1.91f) {
            add = 0.0f;
        }
        loading_bar.setUniform1f("add", add);
        loading_bar.draw();


         add2 -= 0.01f;
         if (add2 < -2.0f) {
             add2 = 0;
         }
        square.setUniform1f("add", add2);
        square.draw();

        mt.draw();

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        movSheep.setUniform2f("mouse", xpos, ypos);
        movSheep.setUniform4f("u_color",clear_color.x , clear_color.y , clear_color.z , clear_color.w);
        movSheep.draw();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }


    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

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