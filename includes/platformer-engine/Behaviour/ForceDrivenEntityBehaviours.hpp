
#ifndef PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP
#define PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP

#include "Point.hpp"
#include "GameObject.hpp"

namespace platformer_engine {

    using spic::Point;
    using spic::GameObject;

    class ForceDrivenEntityBehaviours {
    private:
        auto Seek(Point &point) -> Point;
        auto Flee(Point &point) -> Point;
        auto Arrive(Point &point) -> Point;
        std::weak_ptr<GameObject> _gameObject;
    public:
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

    };
}


#endif //PLATFORMER_ENGINE_FORCEDRIVENENTITYBEHAVIOURS_HPP
