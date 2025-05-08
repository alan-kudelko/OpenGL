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

#include "GLS/GL_Shape.h"
#include "GLS/GL_Shader.h"
#include "GLS/GL_GameObject.h"
#include "GLS/GL_SceneRenderer.h"

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
    glfwSwapInterval(1); // 1 = VSync (synchronizacja do odœwie¿ania ekranu)
    return window;
}

int main(){
    GLFWwindow*window=initializeOpenGL();

    if(window==nullptr)
        return -1;

    GLS::GL_Shader basicShader1(vertexShaderPath,fragmentShaderPath);

    if(basicShader1.getShaderStatus()){
        std::cerr<<"Failed to initialize shader"<<std::endl;
        glfwTerminate();
        return -1;
    }

    GLS::GL_Polygon r1(4,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    GLS::GL_Triangle t1(basicShader1.getShaderID(),GL_DYNAMIC_DRAW);

    GLS::GL_GameObject gObj1;
    gObj1.addComponent(&basicShader1);
    gObj1.addComponent(&t1);
    gObj1.setGameObjectLocation(glm::vec3(300.0f,500.0f,0.0f));
    gObj1.setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
    //gObj1.addComponent(&t1);
    GLS::GL_SceneRenderer sceneRenderer(glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, -1.0f));

    //gObj1.addComponent();
    double lastFrame=glfwGetTime();
    double currentFrame=glfwGetTime();
    float deltaTime=static_cast<float>(currentFrame-lastFrame);

    while(!glfwWindowShouldClose(window)){
        currentFrame=glfwGetTime();
        deltaTime=static_cast<float>(currentFrame-lastFrame);
        lastFrame = currentFrame;

        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sceneRenderer.renderObject(gObj1);
        //r1.drawShape();
        //gObj1.renderObject();
        gObj1.updateGameObjectRotation(glm::vec3(0.0f,0.0f,400.0f*deltaTime));
        //gObj1.setShapeComponentRotation(glm::vec3(0.0f,0.0f,10.0f*glfwGetTime()/1));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
