#ifndef PLATFORMER_ENGINE_NETWORKINGBUFFER_HPP
#define PLATFORMER_ENGINE_NETWORKINGBUFFER_HPP

#include <cstddef>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

namespace platformer_engine{
    /**
     * @brief Utility class to easily handle packets
     */
    class NetworkingBuffer{
    public:
        /**
         * @brief Parse incoming data back to an object using Asio Boost
         * @tparam T Type of object you want to parse to
         * @param data Data from packet
         * @param MaxBufLength Max length of the buffer
         * @param objectRef Reference to the object you want to parse to
         */
        template <typename T> static void ParseIncomingDataToObject(const char* data, size_t MaxBufLength, T &objectRef){
            boost::asio::streambuf sb;

            boost::asio::streambuf::mutable_buffers_type buffers = sb.prepare(MaxBufLength);
            auto iterator = boost::asio::buffers_begin(buffers);

            iterator = std::copy_n(data, MaxBufLength, iterator);

            sb.commit(MaxBufLength);

            boost::archive::binary_iarchive in_archive(sb);
            std::istream stream(&sb);

            in_archive >> objectRef;
        }

        /**
         * @brief Parse object to outgoing data using Asio Boost
         * @tparam T Type of object to parse
         * @param object Object to parse
         * @param bufRef Reference to the buffer you want to parse to
         */
        template <typename T> static void ObjectToAsioBuffer(T object, boost::asio::streambuf &bufRef){
            std::ostream os(&bufRef);
            boost::archive::binary_oarchive out_archive(os);
            out_archive << object;
        }
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_NETWORKINGBUFFER_HPP
