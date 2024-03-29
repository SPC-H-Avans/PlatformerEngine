#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-non-const-global-variables"
#pragma ide diagnostic ignored "cppcoreguidelines-non-private-member-variables-in-classes"
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Component.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <ranges>


namespace spic {

    /**
     * @brief Any object which should be represented on screen.
     */
    class GameObject {
    public:
        template<typename archive>
        void serialize(archive &ar, const unsigned /*version*/) {
            ar.template register_type<Component>();
            ar & _name;
            ar & _tag;
            ar & _active;
            ar & _transform;
            ar & _layer;
            ar & _components;
            ar & _ownerId;
            ar & _self;
        }

        /**
         * @brief Reset the _self pointer to match the current GameObject. Should only be used after de-serialization
         */
        void ResetSelf();

        /**
         * @brief Fixes the private gameObject pointer in the components this Game Object has. Should only be used after de-serialization
         */
        void FixComponents();

        /**
         * @brief Runs some fixes on the Game Object after it being de-serialized. Recommended to run after de-serialization
         */
        void FixGameObjectAfterDeserialize();

        /**
         * @brief Finds an active GameObject by name and returns it.
         * @param name The name of the GameObject you want to find.
         * @return Pointer to GameObject, or nullptr if not found.
         * @spicapi
         */
        static auto Find(const std::string &name, bool includeInactive = false) -> std::shared_ptr<GameObject>;

        /**
         * @brief Returns a vector of active GameObjects tagged tag. Returns empty
         *        vector if no GameObject was found.
         * @param tag The tag to find.
         * @return std::vector of GameObject pointers. No ownership.
         * @spicapi
         */
        static auto FindGameObjectsWithTag(const std::string &tag) -> std::vector<std::shared_ptr<GameObject>>;

        /**
         * @brief Returns one active GameObject tagged tag. Returns nullptr if no GameObject was found.
         * @param tag The tag to find.
         * @return Pointer to GameObject, or nullptr if not found.
         * @spicapi
         */
        static auto FindWithTag(const std::string &tag) -> std::shared_ptr<GameObject>;

        /**
         * @brief Returns the first active loaded object of type T.
         * @spicapi
         */
        template<class T>
        static auto FindObjectOfType(bool includeInactive = false) -> std::shared_ptr<GameObject> {
            for (auto const &[key, val]: _instances) {
                if (typeid(*val) == typeid(T)) {
                    if (includeInactive || val->Active())
                        return val;
                }
            }
            return nullptr;
        }

        /**
         * @brief Gets a list of all loaded objects of type T.
         * @spicapi
         */
        template<class T>
        static auto FindObjectsOfType(bool includeInactive = false) -> std::vector<std::shared_ptr<GameObject>> {
            std::vector<std::shared_ptr<GameObject>> result;
            for (auto const &[key, val]: _instances) {
                if (typeid(*val) == typeid(T)) {
                    if (includeInactive || val->Active()) {
                        result.template emplace_back(val);
                    }
                }
            }
            return result;
        }

        /**
         * @brief Gets a list of all instances.
         * @spicapi
         */
        static auto GetInstances(bool includeInactive = false) -> std::vector<std::shared_ptr<GameObject>> {
            std::vector<std::shared_ptr<GameObject>> result;
            for (auto const &[key, val]: _instances) {
                if (includeInactive || val->Active()) {
                    result.template emplace_back(val);
                }
            }
            return result;
        }

        /**
         * @brief Removes a GameObject from the administration.
         * @details Child GameObjects will be destroyed, too, as well as
         *          Components owned by the GameObject.
         * @param obj The GameObject to be destroyed. Must be a valid pointer to existing Game Object.
         * @exception A std::runtime_exception is thrown when the pointer is not valid.
         * @spicapi
         */
        static void Destroy(std::shared_ptr<GameObject> obj);

        /**
         * @brief Constructor.
         * @details The new GameObject will also be added to a statically
         *          available collection, the administration.  This makes the
         *          Find()-functions possible.
         *          If name equals Null the object will not be persisted
         * @param name The name for the game object.
         * @spicapi
         */
        GameObject(const std::string &name = "Null");

        /**
         * @brief Constructor.
         * @details The new GameObject will also be added to a statically
         *          available collection, the administration.  This makes the
         *          Find()-functions possible.
         * @param name The name for the game object.
         * @param tag The tag for the game object.
         * @spicapi
         */
        GameObject(const std::string &name, const std::string &tag);

        GameObject(const GameObject& other) = default;
        auto operator=(const GameObject &other) -> GameObject &;
        GameObject(GameObject&& other) = default;
        auto operator=(GameObject&& other) -> GameObject & = default;

        virtual ~GameObject() = default;

        /**
         * @brief Does the object exist? TODO wat wordt hiermee bedoeld?
         * @spicapi
         */
        operator bool();

        /**
         * @brief Compare two GameObjects.
         * @param other The other object to compare this one with.
         * @return true if not equal, false otherwise.
         * @spicapi
         */
        auto operator!=(const GameObject &other) -> bool;

        /**
         * @brief Compare two GameObjects
         * @param other The other object to compare this one with.
         * @return true if equal, false otherwise.
         * @spicapi
         */
        auto operator==(const GameObject &other) -> bool;

//        /**
//         * @brief Add given GameObject reference to this object's children list
//         * @details This function places a pointer to the gameobject in a suitable container,
//         * and sets the parent field on the child.
//         * @param other Reference to the GameObject.
//         * @spicapi
//         */
//        void AddChild(std::shared_ptr<GameObject> child);

        /**
         * @brief Returns the name of the GameObject
         * @return name of the gameobject
         * @spicapi
         */
        auto GetName() const -> std::string;

        /**
        * @brief Returns the tag of the GameObject
        * @return tag of the gameobject
        * @spicapi
        */
        [[nodiscard]] auto GetTag() const -> std::string;

//        /**
//         * @brief Returns the parent GameObject of this instance.
//         * @return pointer to the parent GameObject, nullptr if no parent set.
//         * @spicapi
//         */
//        auto Parent() -> std::shared_ptr<GameObject>;
//
//        /**
//        * @brief Returns the children of this instance
//        * @return list of pointers to the child GameObjects, empty list if no children set.
//        * @spicapi
//        */
//        auto Children() -> std::vector<std::shared_ptr<GameObject>>;

        /**
         * @brief Add a Component of the specified type. Must be a valid
         *        subclass of Component. The GameObject assumes ownership of
         *        the Component.
         * @details This function places a pointer to the component in
         *          a suitable container.
         * @param component Reference to the component.
         * @spicapi
         */
        template<class T>
        void AddComponent(std::shared_ptr<Component> component) {
            if (std::is_base_of<Component, T>::value && component != nullptr) { //T is Component
                component->SetGameObject(_self);
                _self.lock()->_components[typeid(T).name()].template emplace_back(component);
            }
        }

        /**
         * @brief Get the first component of the specified type. Must be
         *        a valid subclass of Component.
         * @return Pointer to Component instance.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] auto GetComponent() const -> std::shared_ptr<Component> {
            if (std::is_base_of<Component, T>::value) {
                if (!_self.expired()) {
                    auto comps = _self.lock()->_components;
                    if (comps.count(typeid(T).name()) > 0) {
                        auto cList = comps[typeid(T).name()];
                        if (!cList.empty())
                            return cList.front();
                    }
                }
            }
            return nullptr;
        }

//        /**
//         * @brief Get the first component of the specified type from
//         *        contained game objects. Must be
//         *        a valid subclass of Component.
//         * @return Pointer to Component instance.
//         * @spicapi
//         */
//        template<class T>
//        [[nodiscard]] auto GetComponentInChildren() const -> std::shared_ptr<Component> {
//            for (const auto &child: _self.lock()->_children) {
//                auto comp = child->template GetComponent<T>();
//                if (comp != nullptr)
//                    return comp;
//            }
//            return nullptr;
//        }

//        /**
//         * @brief Get the first component of the specified type from
//         *        the parent game object. Must be
//         *        a valid subclass of Component.
//         * @return Pointer to Component instance.
//         * @spicapi
//         */
//        template<class T>
//        [[nodiscard]] auto GetComponentInParent() const -> std::shared_ptr<Component> {
//            return _parent->template GetComponent<T>();
//        }

        /**
         * @brief Get all components of the specified type. Must be
         *        a valid subclass of Component.
         * @return Vector with pointers to Component instances.
         * @spicapi
         */
        template<class T>
        [[nodiscard]] auto GetComponents() const -> std::vector<std::shared_ptr<Component>> {
            std::vector<std::shared_ptr<Component>> result;
            if (std::is_base_of<Component, T>::value) { //Check if T is derived from Component
                if (!_self.expired()) {
                    auto comps = _self.lock()->_components;
                    auto cList = comps.find(typeid(T).name()); //Finds all components on object with type T
                    if (cList != comps.end()) {
                        for (const auto &comp: cList->second)
                            result.template emplace_back(comp);
                    }
                }
            }
            return result;
        }

//        /**
//         * @brief Get all components of the specified type from
//         *        contained game objects. Must be
//         *        a valid subclass of Component.
//         * @return Vector with pointers to Component instances.
//         * @spicapi
//         */
//        template<class T>
//        [[nodiscard]] auto GetComponentsInChildren() const -> std::vector<std::shared_ptr<Component>> {
//            std::vector<std::shared_ptr<Component>> result;
//            for (auto &child: _self.lock()->_children) {
//
//                std::vector<std::shared_ptr<Component>> comps = child->template GetComponents<T>();
//                if (result.empty())
//                    result = comps;
//                else {
//                    result.insert(result.end(), comps.begin(), comps.end());
//                }
//            }
//            return result;
//        }

//        /**
//         * @brief Get all components op the specified type from
//         *        the parent game object. Must be
//         *        a valid subclass of Component.
//         * @return Vector with pointers to Component instances.
//         * @spicapi
//         */
//        template<class T>
//        [[nodiscard]] auto GetComponentsInParent() const -> std::vector<std::shared_ptr<Component>> {
//            return _parent->template GetComponents<T>();
//        }

        /**
         * @brief Activates/Deactivates the GameObject, depending on the given true or false value.
         * @param active Desired value.
         * @spicapi
         */
        void Active(bool flag);

        /**
         * @brief Returns whether this game object is itself active.
         * @return true if active, false if not.
         * @spicapi
         */
        [[nodiscard]] auto Active() const -> bool;

        /**
         * @brief Returns whether this game component is active, taking its parents
         *        into consideration as well.
         * @return true if game object and all of its parents are active,
         *        false otherwise.
         * @spicapi
         */
        [[nodiscard]] auto IsActiveInWorld() const -> bool;

        /**
         * @brief Returns the Transform set on this object
         * @return Transform of GameObject
         * @spicapi
         */
        auto GetTransform() -> Transform;

        /**
         * @brief sets the Transform of current GameObject and updates all it's Collider's positions
         * @spicapi
         */
        void SetTransform(const Transform &transform);

        /**
         * @brief sets the id of the owning client in network
         */
        void SetOwnerId(int uid);

        /**
         * @brief returns the ownerId of this GameObject
         * @return int that represents the clientId in the network
         */
        auto GetOwnerId() -> int;

    protected:
        std::string _name; //Unique
        std::string _tag;
        bool _active = true;
        int _layer;
//        std::shared_ptr<GameObject> _parent;
//        std::vector<std::shared_ptr<GameObject>> _children;
        std::map<std::string, std::vector<std::shared_ptr<Component>>> _components; //Key is typeid.name
        Transform _transform = Transform{Point{0, 0}, 0, 0};
        std::weak_ptr<GameObject> _self;

        //Networking
        int _ownerId = 0;

        //Multiton Pattern
        static std::map<std::string, std::shared_ptr<GameObject>> _instances;
    };

} // namespace spic

#endif // GAMEOBJECT_H_

#pragma clang diagnostic pop