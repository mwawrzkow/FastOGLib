#include "ArrayHandler.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>

namespace GPU
{
    const unsigned int &GPU_Ref::getVAO()
    {
        return VAO;
    }
    const unsigned int &GPU_Ref::getVBO()
    {
        return VBO;
    }
    const unsigned int &GPU_Ref::getEBO()
    {
        return EBO;
    }
    bool &GPU_Ref::Taken()
    {
        return taken;
    }
    void GPU_Ref::Release()
    {
        taken = false;
    }
    GPU_Ref *GPU_Ref::Take()
    {
        taken = true;
        return this;
    }
    GPU_Ref::GPU_Ref(int VAO, int VBO, int EBO)
    {
        this->VAO = VAO;
        this->VBO = VBO;
        this->EBO = EBO;
        this->taken = false;
    }
    bool ArrayHandler::areRepetitions(unsigned int array[], int size)
    {

        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1; j++)
                if (i != j)
                    if (array[i] == array[j])
                        return true;
        return false;
    }
    ArrayHandler::ArrayHandler(/* args */)
    {
    }

    ArrayHandler::~ArrayHandler()
    {
    }
    bool ArrayHandler::alocateBuffer(int size)
    {
        unsigned int VAO[size], VBO[size], EBO[size];
        // std::cout << "Allocating the buffer" << std::endl;
        glGenVertexArrays(size, VAO);
        glGenBuffers(size, VBO);
        glGenBuffers(size, EBO);
        // std::cout << "Ended alocating the buffer" << std::endl;
        if (areRepetitions(VAO, size) || areRepetitions(VBO, size || areRepetitions(EBO, size)))
            return false;
        for (int i = 0; i < size; i++)
        {
            //<std::pair<int, bool>, GPU_Ref>
            this->GPUSpace.push_back(GPU_Ref(VAO[i], VBO[i], EBO[i]));
        }
        return true;
    }
    bool ArrayHandler::areFreeBuffers()
    {
        for (size_t i = 0; i < this->GPUSpace.size(); i++)
        {
            if (!this->GPUSpace[i].Taken())
                return true;
        }
        return false;
    }
    GPU_Ref *ArrayHandler::getFirstAvailavleBuffer()
    {
        for (size_t i = 0; i < GPUSpace.size(); i++)
        {
            if (!GPUSpace[i].Taken())
                return GPUSpace[i].Take();
        }
        return nullptr;
    }
    void ArrayHandler::releaseBuffer(int idx)
    {
        if (this->GPUSpace[idx].Taken())
        {
            this->GPUSpace[idx].Release();
        }
    }
}