
#ifndef PLATFORMER_ENGINE_DATACONTAINER_HPP
#define PLATFORMER_ENGINE_DATACONTAINER_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

/**
 * @class Interface to encapsulate templated DataContainer in a map
 */
class IDataContainer {
public:
    IDataContainer() = default;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned /*version*/) {
    }

    virtual ~IDataContainer() = default;
    IDataContainer(const IDataContainer& other) = default;
    auto operator=(const IDataContainer &other) -> IDataContainer & = default;
    IDataContainer(IDataContainer &&other) = default;
    auto operator=(IDataContainer &&other) -> IDataContainer & = default;
};

/**
 * @class a container to store any type of serializable data.
 * @tparam T
 */
template<typename T>
class DataContainer : public IDataContainer {
public:
    DataContainer() = default;
    DataContainer(T object) : value(std::make_unique<T>(object)) {}
    ~DataContainer() override = default;

    DataContainer(const DataContainer& other) = default;
    auto operator=(const DataContainer &other) -> DataContainer & = default;
    DataContainer(DataContainer &&other)  noexcept = default;
    auto operator=(DataContainer &&other)  noexcept -> DataContainer & = default;

    std::unique_ptr<T> value;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned /*version*/) {
        ar & boost::serialization::base_object<IDataContainer>(*this);
        ar & value;
    }
};

#endif //PLATFORMER_ENGINE_DATACONTAINER_HPP
