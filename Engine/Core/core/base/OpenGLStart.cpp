#include <iostream>
#include "OpenGLStart.hpp"
#include <cassert>
namespace OpenGLInstance
{
    GLFWwindow *InitWindow(int width, int height, std::string name)
    {
        assert(width >= 1280 && "Width Value must be at least 1280");
        assert(height >= 720 && "Height Value must be at least 720");
        glewExperimental = GL_TRUE;
        std::cout << "RPG engine!\nLet's start this shit!" << std::endl;
        if (!glfwInit())
        {
            std::cerr << "GLFW init failed..." << std::endl;
            exit(-1);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        // int width = 1280, height = 720;
        GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            std::cerr << "Window init failed..." << std::endl;
            glfwTerminate();
            exit(-2);
        }
        glfwMakeContextCurrent(window);
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Glew init failed..." << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(-3);
        }
        return window;
    }
    void setClearColor(float R, float G, float B, float A)
    {
        assert(R <= 1.0f && R >= 0.0f && "Red value has to be between 0 and 1");
        assert(B <= 1.0f && B >= 0.0f && "Blue value has to be between 0 and 1");
        assert(G <= 1.0f && G >= 0.0f && "Green value has to be between 0 and 1");
        assert(A <= 1.0f && A >= 0.0f && "Alpha value has to be between 0 and 1");
        glClearColor(R, G, B, A);
    }
    std::vector<GLuint> CreateAndCompileShaders(const char *vertShaderCode, const char *fragShaderCode)
    {
        assert(vertShaderCode != nullptr && "vertShaderCode has to have value");
        assert(fragShaderCode != nullptr && "fragShaderCode has to have value");
        std::vector<GLuint> result;
        GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertShaderCode, nullptr);
        glCompileShader(vertShader);
        int success;
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
            std::cerr << "Shader Error :" << infoLog << std::endl;
            exit(-3);
        }
        result.push_back(vertShader);
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragShaderCode, nullptr);
        glCompileShader(fragShader);
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
            std::cerr << "Shader Error :" << infoLog << std::endl;
            exit(-3);
        }
        result.push_back(fragShader);
        return result;
    }
    GLuint CreateProgramAndLinkShaders(const std::vector<GLuint> shaders)
    {
        GLuint program = glCreateProgram();
        glAttachShader(program, shaders[0]);
        glAttachShader(program, shaders[1]);
        glLinkProgram(program);
        int succes;
        glGetProgramiv(program, GL_LINK_STATUS, &succes);
        if (!succes)
        {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "Linking Error: " << infoLog << std::endl;
            exit(-2);
        }
        return program;
    }
}