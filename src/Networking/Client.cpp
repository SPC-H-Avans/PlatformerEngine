#include "Networking/Client.hpp"

platformer_engine::Client::Client(const std::string &ip, int port, int clientId, bool isPartyLeader) :
        _ip(ip), _port(port), _clientId(clientId), _isPartyLeader(isPartyLeader) {}

platformer_engine::Client::Client(int clientId, bool isPartyLeader) :
        _clientId(clientId), _isPartyLeader(isPartyLeader), _ip("0"), _port(0) {}

