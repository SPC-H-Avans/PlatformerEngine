#ifndef PLATFORMER_ENGINE_MOVESYSTEM_HPP
#define PLATFORMER_ENGINE_MOVESYSTEM_HPP

class MoveSystem {
public:

    MoveSystem(int localClientId = 0);

    /**
    * @brief Move every active dynamic RigidBody according to their physics
    */
    void Update();

private:
    int _clientId = 0;
};


#endif //PLATFORMER_ENGINE_MOVESYSTEM_HPP
