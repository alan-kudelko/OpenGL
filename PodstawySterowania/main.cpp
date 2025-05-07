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

enum{WINDOW_SIZE_X=800,WINDOW_SIZE_Y=800};
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

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow*window=glfwCreateWindow(WINDOW_SIZE_X,WINDOW_SIZE_Y,"Nazwa",NULL,NULL);

    glfwSetWindowAttrib(window,GLFW_RESIZABLE,GLFW_FALSE);

    if(window==nullptr){
        std::cout<<"GLFW failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,framebuffer_keyboard_input_callback);

    if(!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))){
        std::cout<<"GLAD failed to initialize"<<std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,WINDOW_SIZE_X,WINDOW_SIZE_Y);

    GLS::GL_SHADER basicShader1(vertexShaderPath,fragmentShaderPath);
    GLS::GL_SHADER basicShader2(vertexShaderPath,fragmentShaderPath);
    if(basicShader1.getShaderStatus()){
        std::cerr<<"Blad shadera"<<std::endl;
        glfwTerminate();
        return -1;
    }

    GLS::GL_POLYGON t1(4,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    //GLS::GL_TRIANGLE t1(vertices,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    //GLS::GL_TRIANGLE t1(basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    //std::cout<<GL_GPUresourceTracker.getNumberVAO()<<std::endl;
    //std::cout<<"T1: "<<t1.getShader()<<std::endl;
    //glm::mat4 projection = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, 0.1f, 100.0f);

    //glUniform4fv(colorLoc, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); // czerwony kolor

    //glm::mat4 projection = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, 0.1f, 100.0f);
    glm::mat4 projection;
    //GLuint projectionLoc = glGetUniformLocation(basicShader1.getShaderID(), "projection");

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES,0,3);
        //t1.rotate(glm::vec3(0,0,glfwGetTime()/1000));
        //r1.GLdrawShape();
        //glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));
        //t1.transform(glm::vec3(std::sin(glfwGetTime()/2)/3,0,0));
        //t1.drawShape();
        t1.drawShape();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}
