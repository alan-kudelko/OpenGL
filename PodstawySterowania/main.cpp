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
#include <windows.h>

#include "GLS/GL_Shape.h"
#include "GLS/GL_Shader.h"
#include "GLS/GL_GameObject.h"
#include "GLS/GL_SceneRenderer.h"
#include "GLS/GL_CollisionManager.h"
#include "GLS/GL_CollisionBehaviour.h"
#include "GLS/GL_SceneManager.h"

enum{WINDOW_SIZE_X=1000,WINDOW_SIZE_Y=1000};
const char*vertexShaderPath="shaders/orto_vertex_shader.vert";
const char*fragmentShaderPath="shaders/basic_fragment_shader.frag";

glm::vec3 locationUpdate{};
glm::vec3 rotationUpdate{};

void framebuffer_keyboard_input_callback(GLFWwindow*window,GLint key,GLint scanCode,GLint action,GLint mods){
    if(key==GLFW_KEY_W&&action==GLFW_RELEASE){
        locationUpdate.y=0;
    }
    if(key==GLFW_KEY_S&&action==GLFW_RELEASE){
        locationUpdate.y=0;
    }
    if(key==GLFW_KEY_A&&action==GLFW_RELEASE){
        locationUpdate.x=0;
    }
    if(key==GLFW_KEY_D&&action==GLFW_RELEASE){
        locationUpdate.x=0;
    }
    if(key==GLFW_KEY_E&&action==GLFW_RELEASE){
        rotationUpdate.z=0;
    }
    if(key==GLFW_KEY_Q&&action==GLFW_RELEASE){
        rotationUpdate.z=0;
    }
    if(key==GLFW_KEY_W&&action==GLFW_PRESS){
        locationUpdate.y=-10;
    }
    if(key==GLFW_KEY_S&&action==GLFW_PRESS){
        locationUpdate.y=10;
    }
    if(key==GLFW_KEY_A&&action==GLFW_PRESS){
        locationUpdate.x=-10;
    }
    if(key==GLFW_KEY_D&&action==GLFW_PRESS){
        locationUpdate.x=10;
    }
    if(key==GLFW_KEY_E&&action==GLFW_PRESS){
        rotationUpdate.z=1;
    }
    if(key==GLFW_KEY_Q&&action==GLFW_PRESS){
        rotationUpdate.z=-1;
    }


    if(key==GLFW_KEY_ESCAPE&&action==GLFW_PRESS){
        glfwSetWindowShouldClose(window,GLFW_TRUE);
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
    glfwSwapInterval(1); // 1 = VSync (synchronizacja do odœwiezania ekranu)
    return window;
}

int main(){
    GLFWwindow*window=initializeOpenGL();

    if(window==nullptr)
        return -1;

    GLS::GL_SceneManager sceneManager;
    GLS::GL_CollisionManager GL_CollisionManager1;
    GLS::GL_Shader basicShader1(vertexShaderPath,fragmentShaderPath);
    GLS::GL_Polygon r1(4,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    GLS::GL_Polygon p1(30,basicShader1.getShaderID(),GL_DYNAMIC_DRAW);
    GLS::GL_Triangle t1(basicShader1.getShaderID(),GL_DYNAMIC_DRAW);



    if(basicShader1.getShaderStatus()){
        std::cerr<<"Failed to initialize shader"<<std::endl;
        glfwTerminate();
        return -1;
    }

    auto initializeScene = [&]() {
        GLS::GL_GameObject* gObj = new GLS::GL_GameObject;
        // Paletka
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&r1);
        gObj->setGameObjectLocation(glm::vec3(420.0f, 900.0f, 0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f, 0.0f, 0.0f));
        gObj->setShapeComponentSize(glm::vec3(100.0f, 20.0f, 1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 20.0f, 1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourDoNothing);

        sceneManager.addNewGameObject(gObj);

        gObj = new GLS::GL_GameObject;
        // Pileczka
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&p1);
        gObj->setGameObjectLocation(glm::vec3(280.0f, 700.0f, 0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f, 0.0f, 0.0f));
        gObj->setShapeComponentSize(glm::vec3(20.0f, 20.0f, 1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourReverseVelocityAfterCollision);
        gObj->setGameObjectLinearVelocity(glm::vec3(0.0f,120.0f,0.0f));

        sceneManager.addNewGameObject(gObj);
        for(int j=0;j<3;j++){
            for(int i=0;i<10;i++){
                gObj = new GLS::GL_GameObject;
                gObj->assignShaderComponent(&basicShader1);
                gObj->assignShapeComponent(&r1);
                gObj->setGameObjectLocation(glm::vec3(50.0f+i*100,35.0f+j*40.0f,0.0f));
                gObj->setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
                gObj->setShapeComponentSize(glm::vec3(80.0f,20.0f,1.0f));
                gObj->createCollisionComponent(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(80.0f,20.0f,1.0f));
                gObj->createCollisionBehaviourComponent(&GLS::behaviourDestroyAfterCollision);
                sceneManager.addNewGameObject(gObj);
            }
        }
        gObj = new GLS::GL_GameObject;
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&r1);
        gObj->setGameObjectLocation(glm::vec3(0.0f,GLfloat(WINDOW_SIZE_Y)/2,0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
        gObj->setShapeComponentSize(glm::vec3(10.0f,GLfloat(WINDOW_SIZE_Y),1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,GLfloat(WINDOW_SIZE_Y),1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourDoNothing);
        sceneManager.addNewGameObject(gObj);

        gObj = new GLS::GL_GameObject;
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&r1);
        gObj->setGameObjectLocation(glm::vec3(GLfloat(WINDOW_SIZE_X),GLfloat(WINDOW_SIZE_Y)/2,0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
        gObj->setShapeComponentSize(glm::vec3(10.0f,GLfloat(WINDOW_SIZE_Y),1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(5.0f,GLfloat(WINDOW_SIZE_Y),1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourDoNothing);
        sceneManager.addNewGameObject(gObj);

        gObj = new GLS::GL_GameObject;
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&r1);
        gObj->setGameObjectLocation(glm::vec3(GLfloat(WINDOW_SIZE_X)/2.0f,-5.0f,0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
        gObj->setShapeComponentSize(glm::vec3(GLfloat(WINDOW_SIZE_X),10.0f,1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(GLfloat(WINDOW_SIZE_X),5.0f,1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourDoNothing);
        sceneManager.addNewGameObject(gObj);

        gObj = new GLS::GL_GameObject;
        gObj->assignShaderComponent(&basicShader1);
        gObj->assignShapeComponent(&r1);
        gObj->setGameObjectLocation(glm::vec3(GLfloat(WINDOW_SIZE_X)/2.0f,1005.0f,0.0f));
        gObj->setShapeComponentLocation(glm::vec3(0.0f,0.0f,0.0f));
        gObj->setShapeComponentSize(glm::vec3(GLfloat(WINDOW_SIZE_X),10.0f,1.0f));
        gObj->createCollisionComponent(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(GLfloat(WINDOW_SIZE_X),5.0f,1.0f));
        gObj->createCollisionBehaviourComponent(&GLS::behaviourDoNothing);
        sceneManager.addNewGameObject(gObj);

    };

    initializeScene();
    GLS::GL_SceneRenderer sceneRenderer(glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, -1.0f));

    double lastFrame=glfwGetTime();
    double currentFrame=glfwGetTime();
    float deltaTime=static_cast<float>(currentFrame-lastFrame);

    while(!glfwWindowShouldClose(window)){
        currentFrame=glfwGetTime();
        deltaTime=static_cast<float>(currentFrame-lastFrame);
        lastFrame=currentFrame;

        glClearColor(0.2f,0.2f,0.2f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sceneRenderer.renderScene(sceneManager.getSceneObjectsConst());

        sceneManager.getSceneObjectMutable(1).updateGameObjectLocation(deltaTime);

        sceneManager.getSceneObjectMutable(0).updateGameObjectLocation(locationUpdate);
        sceneManager.getSceneObjectMutable(0).updateGameObjectRotation(rotationUpdate);
        auto werdon=sceneManager.getSceneObjectsConst();
        for(auto it=werdon.begin();it!=werdon.end();++it){
            for(auto jt=std::next(it);jt!=werdon.end();++jt){
                GL_CollisionManager1.checkCollision(*it,*jt);
            }
        }
        sceneManager.updateScene();

        //GL_CollisionManager1.checkCollision(&gObj1,&gObj2);
        //gObj2.setShapeComponentRotation(glm::vec3(0.0f,0.0f,10.0f*glfwGetTime()/1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

