#ifndef PLATFORMER_ENGINE_DATASTORAGEMANAGER_HPP
#define PLATFORMER_ENGINE_DATASTORAGEMANAGER_HPP

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/unordered_map.hpp"
#include <boost/serialization/unique_ptr.hpp>
#include "Storage/DataContainer.hpp"
#include <fstream>
#include <memory>
#include <optional>

namespace platformer_engine {

    /**
     * @class Manager for storing and retrieving data from a save file.
     */
    class DataStorageManager {
    public:
        DataStorageManager() = default;

        /**
         * @brief Loads any serializable (boost) type to the save file
         * @tparam T type of the serializable object
         * @param keyName key at which the object can be found
         * @param object object that needs to be serialized
         */
        template<class T>
        void SaveData(std::string keyName, T object) {
            std::unordered_map<std::string, std::unique_ptr<IDataContainer>> dataMap;
            std::ifstream ifstr {"localSave.txt"};

            if(ifstr.is_open()) {
                try {
                    boost::archive::text_iarchive ita(ifstr);
                    ita.register_type<DataContainer<T>>();
                    ita >> dataMap;
                    ifstr.close();
                } catch (const std::exception& e) {
                    if(ifstr.is_open())
                        ifstr.close();
                }
            }

            dataMap[keyName] = std::make_unique<DataContainer<T>>(object);
            std::ofstream ofstr {"localSave.txt", std::ofstream::out | std::ofstream::trunc};
            boost::archive::text_oarchive ota(ofstr);
            ota.register_type<DataContainer<T>>();
            ota << dataMap; //Write back to file
            ofstr.close();
        }

        /**
         * @brief Retrieve an object from the save file
         * @tparam T type of serializable object
         * @param keyName key at which the object can be located
         * @return
         */
        template<class T>
        auto LoadData(std::string keyName) -> std::optional<T> {
            std::unordered_map<std::string, std::unique_ptr<IDataContainer>> dataMap;
            std::ifstream ifstr {"localSave.txt"};

            if(ifstr.is_open()) {
                try {
                    boost::archive::text_iarchive ita(ifstr);
                    ita.register_type<DataContainer<T>>();
                    ita >> dataMap;
                    ifstr.close();
                } catch (const std::exception& e) {
                    if(ifstr.is_open())
                        ifstr.close();
                }
            }

            if(dataMap.contains(keyName)) {
                auto container = static_cast<DataContainer<T>*>(dataMap[keyName].get());

                if(container != nullptr) {
                    return *(container->value);
                }
            }

            return std::nullopt;
        }

        /**
         * @brief replaces the current storage file with a new file.
         */
        void ClearStorage() {
            std::ofstream ofstr {"localSave.txt", std::ofstream::out | std::ofstream::trunc};
            ofstr << "";
        }
    };
}

#endif //PLATFORMER_ENGINE_DATASTORAGEMANAGER_HPP