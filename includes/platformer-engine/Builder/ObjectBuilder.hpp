//
// Created by Niels on 7-11-2022.
//

#ifndef PLATFORMER_ENGINE_BUILDER_HPP
#define PLATFORMER_ENGINE_BUILDER_HPP

class ObjectBuilder {
public:
    virtual ObjectBuilder& AddAudio() = 0;
};

#endif //PLATFORMER_ENGINE_BUILDER_HPP
