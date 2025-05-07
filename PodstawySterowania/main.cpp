#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GLS/GL_SHAPES.h"
#include "GLS/GL_SHADER.h"
#include "GLS/GL_GameObject.h"

enum{WINDOW_SIZE_X=1000,WINDOW_SIZE_Y=1000};
const char*vertexShaderPath="shaders/orto_vertex_shader.vert";
const char*fragmentShaderPath="shaders/basic_fragment_shader.frag";

void framebuffer_keyboard_input_callback(GLFWwindow*window,GLint key,GLint scanCode,GLint action,GLint mods){
    if(key==GLFW_KEY_W&&action==GLFW_PRESS){
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
    if(key==GLFW_KEY_S&&action==GLFW_PRESS){

    }
}
GLS::GL_VertexData vertices[]{
    {
        {0.5f,0.5f,0.0f},
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,0.0f}
    },
    {
        {0.5f,-0.5f,0.0f},
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,0.0f}
    },
    {
        {-0.5f,-0.5f,0.0f},
        {1.0f,0.0f,0.0f,0.0f},
        {0.0f,0.0f}
    },
};

GLFWwindow*initializeOpenGL(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow*window=glfwCreateWindow(WINDOW_SIZE_X,WINDOW_SIZE_Y,"Nazwa",NULL,NULL);

    if(window==nullptr){
        std::cerr<<"GLFW failed to create a window"<<std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowAttrib(window,GLFW_RESIZABLE,GLFW_FALSE);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window,framebuffer_keyboard_input_callback);

    if(!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))){
        std::cerr<<"GLAD failed to initialize"<<std::endl;
        glfwTerminate();
        return nullptr;
    }

    glViewport(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);

    return window;
}

int main(){
    GLFWwindow*window=initializeOpenGL();

    if(window==nullptr)
        return -1;

    GLS::GL_SHADER basicShader1(vertexShaderPath,fragmentShaderPath);

    if(basicShader1.getShaderStatus()){
        std::cerr<<"Failed to initialize shader"<<std::endl;
        glfwTerminate();
        return -1;
    }

    GLS::GL_POLYGON t1(4,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);

    GLS::GL_GameObject gObj1;
    //gObj1.addComponent();

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        t1.drawShape();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
