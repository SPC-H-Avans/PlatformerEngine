#include <stdexcept>

#include "Director/GameObjectDirector.hpp"

auto GameObjectDirector::CreatePlayer() -> std::shared_ptr<GameObject> {
    auto builder = GameObjectBuilder("gameObject1").AddAnimator();
    throw std::logic_error("Function not implemented");
}
