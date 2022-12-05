
#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP

#include "Point.hpp"
#include "GameObject.hpp"

namespace platformer_engine {

    using spic::Point;
    using spic::GameObject;

    enum Deceleration{slow = 3, normal = 2, fast = 1};

    class ForceDrivenEntityBehaviours {
    private:
        auto Seek(Point point) -> Point;
        auto Flee(Point &point) -> Point;
        auto Arrive(Point &point, Deceleration deceleration) -> Point;
        std::weak_ptr<GameObject> _gameObject;
    public:
        auto Pursuit(const std::weak_ptr<GameObject>& evader) -> Point;
        ForceDrivenEntityBehaviours(std::weak_ptr<GameObject> gameObject);
        auto Calculate() -> Point;
        auto ForwardComponent() -> Point;
        auto SideComponent() -> Point;

        void SetPath();
        void SetTarget(Point point);
        void SetTargetAgent1(std::shared_ptr<GameObject> targetAgent);
        void SetTargetAgent2(std::shared_ptr<GameObject> targetAgent);

        void SeekOn();
        void FleeOn();
        void ArriveOn();

        void SeekOff();
        void FleeOff();
        void ArriveOff();

        void SetGameObject(std::weak_ptr<GameObject> gObj) {
            _gameObject = std::move(gObj);
        }


    };
}


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP
