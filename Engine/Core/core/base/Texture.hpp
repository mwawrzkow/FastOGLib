#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string> 
#include <vector>
#include <map>

namespace AEG
{
    class Textures; 
    class Texture
    {
        private:
        unsigned int ID; 
        std::string location; 
        protected: 
        const std::string & getLocation(); 
        void setTextureLocation(std::string); 
        void setTextureID(unsigned int); 
        void Clear(); 
        public:
        Texture(std::string, unsigned int);
        const unsigned int& getTextureID(); 
        friend class Textures; 
    };
    class Textures
    {
    private:
        std::vector<Texture> TextureMap;
        void LoadTexture(int, const std::string &);

    public:
        Textures();
        void alocateTextureSpace(unsigned int);
        const unsigned int &getTextureIndex(const std::string &);
        void loadTexture(const std::string &);
        void unloadTexture(const std::string &);
        void unloadTexture(unsigned int);
        ~Textures();
    };
}

#endif