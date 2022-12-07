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
    class DataStorageManager {
    public:
        DataStorageManager() = default;

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

        void ClearStorage() {
            std::ofstream ofstr {"localSave.txt", std::ofstream::out | std::ofstream::trunc};
            ofstr << "";
        }
    };
}

#endif //PLATFORMER_ENGINE_DATASTORAGEMANAGER_HPP