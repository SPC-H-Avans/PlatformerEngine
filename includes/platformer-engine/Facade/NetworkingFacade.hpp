#ifndef PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#define PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
#include "enet/enet.h"
namespace platformer_engine{
    class NetworkingFacade{
    public:
        NetworkingFacade();
        ~NetworkingFacade();
        void Initialize();
        void Shutdown();
        void Update();


    };
}
#endif //PLATFORMER_ENGINE_NETWORKINGFACADE_HPP
