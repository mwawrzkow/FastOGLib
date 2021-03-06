#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include "core/base/vertexHandler.hpp"
#include "core/WindowProperties.hpp"
#include "core/primitives/Square.hpp"
#include <vector>
#include <math.h>
#include "core/base/OpenGLStart.hpp"
#include <algorithm>
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
    std::cout << key << std::endl;
    switch (action)
    {
    case GLFW_PRESS:
        onKeyPress(key);
        break;

    default:
        break;
    }
}
#ifdef __APPLE__
void CheckGLErrors()
{
    GLenum err;

    while ((err = glGetError()) != GL_NO_ERROR)
        fprintf(stderr, "OpenGL Error: %s \n", gluErrorString(err));
}
#endif
std::string readFile(const std::string &fileLoc)
{
    std::ifstream file;
    file.open(fileLoc, std::ios::in);
    std::stringstream contex;
    if (!file.fail())
    {
        contex << file.rdbuf();
    }
    return contex.str();
}

int main(int argc, char **argv)
{

    int width = 1281, height = 720;
    GLFWwindow *window = OpenGLInstance::InitWindow(width, height);

    OpenGLInstance::setClearColor(0.0, 0.0, 0.0, 1);
    GLuint ShaderProgram = OpenGLInstance::CreateProgramAndLinkShaders(
        OpenGLInstance::CreateAndCompileShaders(
            readFile("./vertShader.vert").c_str(),
            readFile("./fragShader.vert").c_str()));
    glUseProgram(ShaderProgram);

    GLint ambientLight = glGetUniformLocation(ShaderProgram, "ambientLightColor");
    // GLint LightPoint = glGetUniformLocation(ShaderProgram, "PLightPos");
    // GLint LightStrength = glGetUniformLocation(ShaderProgram, "PLightStrength");
    // float Light2DPoint[] = {0.0f, 0.0f, 0.0f}; 
    // float LightStrength2D = 2.f; 
    float ambientLightVec[] = {0.59f, 0.305f, 0.0078f};
    glUniform3fv(ambientLight, 1, ambientLightVec);
    // glUniform3fv(LightPoint, 1 , Light2DPoint); 
    // glUniform1f(LightStrength,LightStrength2D );
    Global::WindowProperties *WindowProperties = &Global::WindowProperties::getInstance();
    GPU::ArrayHandler *AH = WindowProperties->getAH();
    AH->alocateBuffer(10000);
    WindowProperties->setWindowHeight(height);
    WindowProperties->setWindowWidth(width);
    WindowProperties->getTextures()->alocateTextureSpace(100);
//     std::vector<Primitives::Square> sqrtVect;
//     for (int i = 0; i < 100; i++)
//     {
//         for (int j = 0; j < 100; j++)
//         {
//             //generate random alpha value
//             float alpha = (float)rand() / (float)RAND_MAX;
//             Primitives::Square tmp(50 * i, 50 * j, 100, alpha);
//             if(i == 0 && j == 10 ){
//                 tmp.setTexture("Sprite.png");
//             }else 
//             if (i % 2)
//             {
//                 tmp.setTexture("Square.png");
//             }
//             else
//             {
//                 tmp.setTexture("Square.png");
//             }
//             sqrtVect.push_back(tmp);

// #ifdef __APPLE__
//             CheckGLErrors();
// #endif
//         }
//     }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#ifdef DEBUG
    int nbFrames = 0;
    float currentTime = 0;
    float lastTime = 0;
    int renderedObjects = 0;
#endif
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glfwPollEvents();
        glfwSetKeyCallback(window, onKeyCallback);
        WindowProperties->setWindowHeight(height);
        WindowProperties->setWindowWidth(width);
#ifdef DEBUG
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f FPS\n", 1e3 * (1 / (1000.0 / double(nbFrames))));
            printf("rendered Objects %i \n", renderedObjects);

            nbFrames = 0;
            lastTime += 1.0;
        }
        renderedObjects = 0;
#endif
        glfwSwapBuffers(window);
    }
    // square.~square();
    glDeleteProgram(ShaderProgram);
    glfwDestroyWindow(window);
    return EXIT_SUCCESS;
}