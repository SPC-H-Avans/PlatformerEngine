//
// Created by Jaap Rodenburg on 07/11/2022.
//

#ifndef PLATFORMER_ENGINE_GRAPHICSFACADE_H
#define PLATFORMER_ENGINE_GRAPHICSFACADE_H

//SDL2 Facade class that creates a SDL2 window and renderer

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "GraphicsFacade/Color.h"

#include <string>
#include <vector>

class GraphicsFacade {
public:
    GraphicsFacade();
    ~GraphicsFacade();

    void init( int width, int height, const std::string& title, const Color& color );
    void quit();

    void render();
    void clear();

    inline const SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
#endif //PLATFORMER_ENGINE_GRAPHICSFACADE_H
