#include "Networking/Client.hpp"

platformer_engine::Client::Client(std::string ip, int port, int clientId, bool isPartyLeader) : _ip(ip), _port(port), _clientId(clientId), _isPartyLeader(isPartyLeader) {}

