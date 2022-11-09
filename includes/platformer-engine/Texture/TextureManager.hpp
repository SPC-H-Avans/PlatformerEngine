#ifndef PLATFORMER_ENGINE_TEXTUREMANAGER_H
#define PLATFORMER_ENGINE_TEXTUREMANAGER_H

#include <string>

//Singleton class to manage all textures
class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager s_instance;
        return s_instance;
    }

    bool Load(std::string id, std::string fileName);

    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

private:
    TextureManager() { }

};

#endif //PLATFORMER_ENGINE_TEXTUREMANAGER_H
