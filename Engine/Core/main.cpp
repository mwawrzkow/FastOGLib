#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include "core/base/vertexHandler.hpp"
#include "core/WindowProperties.hpp"
#include "core/primitives/Square.hpp"
#include "core/primitives/Line.hpp"
#include <vector>
#include <math.h>
#include "core/base/OpenGLStart.hpp"
#include <algorithm>
#include <chrono>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
Primitives::Square *player;
void onKeyPress(int key)
{
    if (player == nullptr)
        return; // sad man noises
    switch (key)
    {
    case GLFW_KEY_W:
        player->Move(0, 10);
        break;
    case GLFW_KEY_S:
        player->Move(0, -10);
        break;
    case GLFW_KEY_A:
        player->Move(-10, 0);
        break;
    case GLFW_KEY_D:
        player->Move(10, 0);
        break;
    default:
        break;
    }
}
void onKeyCallback(GLFWwindow *window, int key, int status, int action, int mods)
{
    std::cout << key << " " << action << std::endl;
    switch (action)
    {
    case GLFW_PRESS:
        onKeyPress(key);
        break;

    default:
        break;
    }
}
std::string readFile(const std::string &fileLoc)
{
    std::ifstream file;
    file.open(fileLoc, std::ios::in);
    std::stringstream contex;
    if (!file.fail())
    {
        contex << file.rdbuf();
    }
    file.close();
    return contex.str();
}
int main(int argc, char **argv)
{

    int width = 1280, height = 720;
    GLFWwindow *window = OpenGLInstance::InitWindow(width, height);

    OpenGLInstance::setClearColor(0.0, 0.0, 0.0, 1);
    GLuint ShaderProgram = OpenGLInstance::CreateProgramAndLinkShaders(
        OpenGLInstance::CreateAndCompileShaders(
            readFile("./vertShader.vert").c_str(),
            readFile("./fragShader.vert").c_str()));
    glUseProgram(ShaderProgram);

    GLint ambientLight = glGetUniformLocation(ShaderProgram, "ambientLightColor");
    float ambientLightVec[] = {0.59f, 0.305f, 0.0078f};
    glUniform3fv(ambientLight, 1, ambientLightVec);
    Global::WindowProperties *WindowProperties = &Global::WindowProperties::getInstance();
    GPU::ArrayHandler *AH = WindowProperties->getAH();
    AH->alocateBuffer(1);
    WindowProperties->setWindowHeight(height);
    WindowProperties->setWindowWidth(width);
    WindowProperties->getTextures()->alocateTextureSpace(1);
    std::vector<Renderable *> primVect;
    // for(int i = 0; i < 50; i++){
    //     for(int j = 0; j < 30; j++)
    //     {
    //         Primitives::Rectanagle* sq = new Primitives::Rectanagle(i* 100+45,j * 100, 75, 50);
    //         sq->setRotation(j*i/M_PI);
    //         primVect.push_back(sq);
    //         ((Primitives::Rectanagle*)primVect[primVect.size() - 1])->setTexture("Square.png");
    //     }
    // }
    Primitives::Line line({0,0},{900,900},500);
    line.setTexture("Square.png");
    primVect.push_back(&line);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    glfwSetKeyCallback(window, onKeyCallback);
    float sin = 0;
    float cos = 0;
    float angle = 0;
    while (!glfwWindowShouldClose(window))
    {
        sin = sinf(angle);
        cos = cosf(angle);
        angle += 0.1;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glfwPollEvents();
        WindowProperties->setWindowHeight(height);
        WindowProperties->setWindowWidth(width);
        for (int i = 0; i < primVect.size(); i++)
        {
            primVect[i]->Display();
        }
        glfwSwapBuffers(window);
    }
    glDeleteProgram(ShaderProgram);
    glfwDestroyWindow(window);
    return EXIT_SUCCESS;
}