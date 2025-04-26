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

enum{WINDOW_SIZE_X=600,WINDOW_SIZE_Y=600};
const char*vertexShaderPath="shaders/basic_vertex_shader.vert";
const char*fragmentShaderPath="shaders/basic_fragment_shader.frag";

std::string loadShader(const char*path){
    std::stringstream sourceCode;
    std::ifstream file;
    file.open(path,std::ios_base::in);
    sourceCode<<file.rdbuf();
    file.close();
    return sourceCode.str();
}
GLuint compileShader(const char*path,GLenum shaderType){
    std::string shaderCode=loadShader(path);
    const char*sourceCode=shaderCode.c_str();

    GLuint shader=glCreateShader(shaderType);
    glShaderSource(shader,1,&sourceCode,nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
    if(!status){
        char log[512]{};
        glGetShaderInfoLog(shader,512,nullptr,log);
        std::cerr<<log<<std::endl;
        return 0;
    }
    return shader;
}
GLuint createShaderProgram(const char*vertexShaderPath,const char*fragmentShaderPath){
    GLuint vertexShader=compileShader(vertexShaderPath,GL_VERTEX_SHADER);
    GLuint fragmentShader=compileShader(fragmentShaderPath,GL_FRAGMENT_SHADER);

    GLuint shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    int status;
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&status);
    if(!status){
        char infoLog[512]{};
        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);
        std::cerr<<infoLog<<std::endl;
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
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

    GLuint basicShader=createShaderProgram(vertexShaderPath,fragmentShaderPath);
    GLuint VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

   // GLS::GL_RECTANGLE r1(vertices2,"name",basicShader,GL_DYNAMIC_DRAW);
    GLS::GL_TRIANGLE t1(vertices,basicShader,GL_DYNAMIC_DRAW);
    std::cout<<GL_GPUresourceTracker.getNumberVAO()<<std::endl;

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(basicShader);
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES,0,3);
        //r1.GLrotate(glm::vec3(0,0,glfwGetTime()/10));
        //r1.GLdrawShape(window);

        t1.GLtransform(glm::vec3(glfwGetTime()/10,0,0));
        t1.GLdrawShape(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(basicShader);
    glfwTerminate();

    return 0;
}
