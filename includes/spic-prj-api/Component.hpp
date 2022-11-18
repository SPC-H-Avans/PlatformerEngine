#ifndef COMPONENT_H_
#define COMPONENT_H_

namespace spic {

    /**
     * @brief Base class for all components.
     */
    class Component {
        public:
            Component() = default;
            /**
             * @brief Virtual destructor.
             * @spicapi
             */
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
            [[nodiscard]] auto Active() const -> bool { return _active; }

            /**
             * @brief flag New active status.
             * @spicapi
             */
            void Active(bool flag) { _active = flag; }

        private:
            /**
             * @brief Active status.
             */
            bool _active = true;
    };

} // namespace spic

#endif // COMPONENT_H_
