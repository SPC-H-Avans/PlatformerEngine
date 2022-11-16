#include "MarioMoveBehavior.hpp"
#include "Input.hpp"

namespace platformer_engine {

    void MarioMoveBehavior::OnStart() {
        spic::Input::GetMouseButton(spic::Input::MouseButton::RIGHT);
        BehaviourScript::OnStart();
    }

    void MarioMoveBehavior::OnUpdate() {
        BehaviourScript::OnUpdate();
    }

    void MarioMoveBehavior::OnTriggerEnter2D(const Collision collision) {
//        BehaviourScript::OnTriggerEnter2D(collision);
    }

    void MarioMoveBehavior::OnTriggerExit2D(const Collision collision) {
//        BehaviourScript::OnTriggerExit2D(collision);
    }

    void MarioMoveBehavior::OnTriggerStay2D(const Collision collision) {
//        BehaviourScript::OnTriggerStay2D(collision);
    }
} // platformer_engine