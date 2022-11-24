#ifndef PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#define PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#include "enet/enet.h"
#include "Debug.hpp"
#include <memory>
namespace platformer_engine{
    class NetworkingFacade{
    public:
        NetworkingFacade(int port);
        ~NetworkingFacade();
    };
}  // namespace platformer_engine
#endif //PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
