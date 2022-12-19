#ifndef PLATFORMER_ENGINE_ISYSTEM_HPP
#define PLATFORMER_ENGINE_ISYSTEM_HPP

class ISystem{
public:
    virtual void Update(double speedMultiplier) = 0;
};

#endif //PLATFORMER_ENGINE_ISYSTEM_HPP
