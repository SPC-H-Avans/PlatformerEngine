#include "Facade/NetworkingFacade.hpp"
#include "Exceptions/ServerCouldNotBeInitialized.hpp"

platformer_engine::NetworkingFacade::NetworkingFacade(int port) {
    if(enet_initialize() != 0){
        throw spic::ServerCouldNotBeInitialized();
    }
    atexit(enet_deinitialize);

    ENetEvent event;
    ENetAddress address;

    address.host = ENET_HOST_ANY;
    address.port = port;

    std::unique_ptr<ENetHost> server = std::unique_ptr<ENetHost>(enet_host_create(&address, 3, 1, 0, 0));
}
