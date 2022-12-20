#ifndef PLATFORMER_ENGINE_ENTITYSTATE_HPP
#define PLATFORMER_ENGINE_ENTITYSTATE_HPP

#include "Point.hpp"
#include <memory>
#include "RigidBody.hpp"
#include <boost/serialization/access.hpp>

// Forward declaration of the state machine class
class EntityStateMachine;

/**
 * @brief Abstract base class for states
 */
class EntityState
{
public:
    template<class Archive>
    void serialize(Archive &ar, unsigned int version) {
    }

    EntityState() = default;
    virtual ~EntityState() = default;

    EntityState(const EntityState&) = default;
    auto operator=(const EntityState&) -> EntityState& = default;

    EntityState(EntityState&&) = default;
    auto operator=(EntityState&&) -> EntityState& = default;

    /**
    * @brief Calculate the force coming from the current state
     * @param rigidBody A reference to the RigidBody whose force should be calculated
     * @return A 2D vector (Point) with the force to be applied to the rigidBody
    */
    virtual auto CalculateForce(std::shared_ptr<RigidBody> &rigidBody) -> spic::Point = 0;

    /**
     * @brief Clone function creates a unique_ptr to the state
     * @return a std::unique_ptr to the state
     */
    [[nodiscard]] virtual auto Clone() const -> std::unique_ptr<EntityState> = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(EntityState);

#endif //PLATFORMER_ENGINE_ENTITYSTATE_HPP
