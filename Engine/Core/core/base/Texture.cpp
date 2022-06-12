#include "Texture.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
namespace AEG
{
    void Texture::setTextureID(unsigned int ID)
    {
        this->ID = ID;
    }
    void Texture::setTextureLocation(std::string location)
    {
        this->location = location;
    }
    const std::string &Texture::getLocation()
    {
        return this->location;
    }
    void Texture::Clear()
    {
        this->location = "";
        this->ID = 0;
    }
    Texture::Texture(std::string location, unsigned int ID)
    {
        this->location = location;
        this->ID = ID;
    }
    const unsigned int &Texture::getTextureID()
    {
        return ID;
    }
    Textures::Textures()
    {
    }

    Textures::~Textures()
    {
    }

    void Textures::alocateTextureSpace(unsigned int size)
    {
        unsigned int texturesSpace[size];
        glGenTextures(size, texturesSpace);
        const unsigned int constSize = TextureMap.size();
        for (int i = constSize; i < constSize + size; i++)
            TextureMap.push_back(Texture("", texturesSpace[i]));
    }
    void Textures::LoadTexture(int ID, const std::string &link)
    {
        int width, height, nrChannels;
        unsigned char *val = stbi_load(link.c_str(), &width, &height, &nrChannels, 0);
        glBindTexture(GL_TEXTURE_2D, ID);


        // glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (val)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, val);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw "Failed to load texture";
        }
        stbi_image_free(val);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void Textures::loadTexture(const std::string &link)
    {
        bool isMemoryForTextureFree = false;
        unsigned int FirstFreeIDX = 0, idx;
        for (unsigned int i = 0; i < TextureMap.size() - 1; i++)
        {
            if (TextureMap[i].getLocation() == link)
            {
                isMemoryForTextureFree = true;
                return;
            }
            else if (TextureMap[i].getLocation() == "")
            {
                FirstFreeIDX = TextureMap[i].getTextureID();
                idx = i;
                i = TextureMap.size();
                isMemoryForTextureFree = true;
            }
        }
        if (!isMemoryForTextureFree)
        {
            alocateTextureSpace(1);
            loadTexture(link);
            return;
        }
        isMemoryForTextureFree = true;
        LoadTexture(FirstFreeIDX, link);
        TextureMap[idx].setTextureLocation(link);
        TextureMap[idx].setTextureID(FirstFreeIDX);
    }
    const unsigned int &Textures::getTextureIndex(const std::string &link)
    {
        for (auto t = TextureMap.begin(); t != TextureMap.end(); t++)
        {
            if (t->getLocation() == link)
            {
                return t->getTextureID();
            }
        }
        throw "Yo stupid";
    }
    void Textures::unloadTexture(const std::string &link)
    {
        for (auto t = TextureMap.begin(); t != TextureMap.end(); t++)
        {
            if (t->getLocation() == link)
            {
                unsigned int textureID = t->getTextureID();
                glDeleteTextures(1, &textureID);
                t->Clear();
            }
        }
    }
    void Textures::unloadTexture(unsigned int ID)
    {
        bool found = false;
        for (auto t = TextureMap.begin(); t != TextureMap.end(); t++)
        {
            if (t->getTextureID() == ID)
            {
                t->Clear();
                found = true;
                t = TextureMap.end();
            }
        }
        if (!found)
            throw "Yo Stupid";
        glDeleteTextures(1, &ID);
    }

}