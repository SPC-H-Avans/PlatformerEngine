#ifndef PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP
#define PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

namespace platformer_engine {

    class DodgeObjectsBehaviour : public spic::BehaviourScript {
    public:
        void OnStart() override;
        void OnUpdate() override;
        void OnTriggerEnter2D(Collision collision) override;
        void OnTriggerExit2D(Collision collision) override;
        void OnTriggerStay2D(Collision collision) override;

        /*
         * Idea behind this:
         * FDE has two colliders, one in itself that has the same location as the object and one that's in front of
         * the FDE in the direction it's heading.
         * There should be a lookahead in the FDE body that decides how far away the object is.
         * The body is responsible for updating the second collider's location.
         *
         * When a collision is detected:
         *  > Check if it was the 'main' or the 'lookahead' collider
         *  > if it's the lookahead collider
         */
    };

}  // namespace platformer_engine

#endif //PLATFORMER_ENGINE_DODGEOBJECTSBEHAVIOUR_HPP
