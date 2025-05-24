#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "GLS/GL_Shape.h"
#include "GLS/GL_Mesh.h"
#include "GLS/GL_Shader.h"
#include "GLS/GL_Collider.h"
#include "GLS/GL_GameObject.h"
#include "GLS/GL_SceneRenderer.h"
#include "GLS/GL_CollisionManager.h"
#include "GLS/GL_CollisionBehaviour.h"
#include "GLS/GL_SceneManager.h"
#include "GLS/GL_CollisionResolve.h"
#include "GLS/GL_ResourceManager.h"

namespace GLS {
    extern GL_ResourceManager GL_resourceManager;
}

enum { WINDOW_SIZE_X = 1000, WINDOW_SIZE_Y = 1000 };
const char* vertexShaderPath = "shaders/orto_vertex_shader.vert";
const char* fragmentShaderPath = "shaders/basic_fragment_shader.frag";

glm::vec3 locationUpdate{};
glm::vec3 rotationUpdate{};

void framebuffer_keyboard_input_callback(GLFWwindow* window, GLint key, GLint scanCode, GLint action, GLint mods) {
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        locationUpdate.y = 0;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        locationUpdate.y = 0;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        locationUpdate.x = 0;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        locationUpdate.x = 0;
    }
    if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
        rotationUpdate.z = 0;
    }
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
        rotationUpdate.z = 0;
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        locationUpdate.y = -1;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        locationUpdate.y = 1;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        locationUpdate.x = -1;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        locationUpdate.x = 1;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        rotationUpdate.z = 1;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        rotationUpdate.z = -1;
    }


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
GLFWwindow* initializeOpenGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "Nazwa", NULL, NULL);

    if (window == nullptr) {
        std::cerr << "GLFW failed to create a window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, framebuffer_keyboard_input_callback);

    if (!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))) {
        std::cerr << "GLAD failed to initialize" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    glfwSwapInterval(1); // 1 = VSync (synchronizacja do odœwiezania ekranu)
    return window;
}

int main() {
    GLFWwindow*window=initializeOpenGL();

    if(window==nullptr)
        return -1;

    GLS::GL_resourceManager.createShader("basic", vertexShaderPath, fragmentShaderPath);

    GLS::GL_SceneManager sceneManager;
    GLS::GL_CollisionManager collisionManager;
    GLS::GL_CollisionResolve collisionResolve;
    GLS::GL_SceneRenderer sceneRenderer(glm::ortho(0.0f, 1000.0f, 1000.0f, 0.0f, 1.0f, -1.0f));

    GLS::GL_GameObject*obj1=new GLS::GL_GameObject(GLS::GL_resourceManager.getShaderByName("basic"), "Rectangle", glm::vec3(500.0f, 500.0f, 0.0f), glm::vec3(0.0f), glm::vec3(100.0f, 20.0f, 1.0f));

    sceneManager.addNewGameObject(obj1);

    GLS::GL_GameObject* obj2=new GLS::GL_GameObject(GLS::GL_resourceManager.getShaderByName("basic"),4,glm::vec3(500.0f,400.0f,0.0f),glm::vec3(0.0f),glm::vec3(100.0f,100.0f,1.0f));
    sceneManager.addNewGameObject(obj2);

    GLS::GL_BoxCollider x;

    double lastFrame=glfwGetTime();
    double currentFrame=glfwGetTime();
    float deltaTime=static_cast<float>(currentFrame-lastFrame);

    while (!glfwWindowShouldClose(window)) {
        currentFrame = glfwGetTime();
        deltaTime = static_cast<float>(currentFrame - lastFrame);
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        std::vector<GLS::GL_GameObject*>sceneObjects=sceneManager.getSceneObjectsMutable();
        std::vector<GLS::GL_CollisionInfo>collisionsInfo=collisionManager.checkCollisions(sceneObjects);

        sceneObjects[0]->move(locationUpdate);
        sceneObjects[0]->rotate(rotationUpdate);

        sceneObjects[1]->rotate(glm::vec3(0.0f,0.0f,deltaTime*20));

        sceneManager.updateScene();
        sceneRenderer.renderScene(sceneObjects);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

