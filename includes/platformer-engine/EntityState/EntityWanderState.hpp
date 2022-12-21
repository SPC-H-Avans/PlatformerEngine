#ifndef PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP

#include "EntityState.hpp"
#include "RigidBody.hpp"

class EntityWanderState : public EntityState {
public:
    template<class Archive>
    void serialize(Archive &ar, unsigned int version) {
        ar & boost::serialization::base_object<EntityState, EntityWanderState>(*this);
        boost::serialization::void_cast_register<EntityWanderState, EntityState>();
    }
    auto CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point override;
    [[nodiscard]] auto Clone() const -> std::unique_ptr<EntityState> override;
};


#endif //PLATFORMER_ENGINE_ENTITYWANDERSTATE_HPP
