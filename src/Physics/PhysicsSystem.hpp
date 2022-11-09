
#ifndef PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP
#define PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP

#include <memory>
#include "Point.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
using namespace spic;

class PhysicsSystem {
public:
    bool CheckCollisions();
private:
    bool CheckBoxCollision(Point& aPos, const BoxCollider& aCol, Point& bPos, const BoxCollider& bCol);
};

#endif //PLATFORMER_ENGINE_PHYSICSSYSTEM_HPP
