#ifndef COMPONENT_H_
#define COMPONENT_H_

namespace spic {

    /**
     * @brief Base class for all components.
     */
    class Component {
        public:
            /**
             * @brief Virtual destructor.
             * @spicapi
             */
            Component() = default;
            virtual ~Component() = default;
            Component(const Component& other) = default;
            auto operator=(const Component& other) -> Component& = default;
            Component(Component&& other) = default;



        auto operator=(Component&& other) -> Component& = default;

            /**
             * @brief Getter for active status.
             * @return true if active, false otherwise.
             * @spicapi
             */
            bool Active() const { return active; }

            /**
             * @brief flag New active status.
             * @spicapi
             */
            void Active(bool flag) { active = flag; }

        private:
            /**
             * @brief Active status.
             */
            bool active;
    };

}

#endif // COMPONENT_H_
