#ifndef PLATFORMER_ENGINE_LAYER_H
#define PLATFORMER_ENGINE_LAYER_H

class Layer {
public:
    virtual void render() = 0;
    virtual void update() = 0;
};

#endif //PLATFORMER_ENGINE_LAYER_H
