
#ifndef PLATFORMER_ENGINE_DATACONTAINER_HPP
#define PLATFORMER_ENGINE_DATACONTAINER_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class IDataContainer {
public:
    IDataContainer() {}

    template<typename archive>
    void serialize(archive &ar, const unsigned /*version*/) {
        ar& test;
    }

    int test = 1;

    virtual ~IDataContainer() = default;
    IDataContainer(const IDataContainer& other) = default;

    auto operator=(const IDataContainer &other) -> IDataContainer & = default;

    IDataContainer(IDataContainer &&other) = default;

    auto operator=(IDataContainer &&other) -> IDataContainer & = default;
};

template<typename T>
class DataContainer : public IDataContainer {
public:
    DataContainer() {}
    DataContainer(T object) : value(object) {}
    ~DataContainer() = default;
    T value;

    template<typename archive> void serialize(archive& ar, const unsigned /*version*/) {
        ar & value;
    }
};

#endif //PLATFORMER_ENGINE_DATACONTAINER_HPP
