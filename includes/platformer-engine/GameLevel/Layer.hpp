#ifndef PLATFORMER_ENGINE_LAYER_H
#define PLATFORMER_ENGINE_LAYER_H

namespace platformer_engine {

    class Layer {
    public:
        virtual void Render() = 0;

        virtual void Update() = 0;

        virtual ~Layer() = default;
    };
}

#endif //PLATFORMER_ENGINE_LAYER_H
