#ifndef PLATFORMER_ENGINE_MARIOINPUTBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_MARIOINPUTBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class MarioInputBehaviour : public spic::BehaviourScript {
    public:
        void OnUpdate() override;
    private:
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_MARIOINPUTBEHAVIOUR_HPP
