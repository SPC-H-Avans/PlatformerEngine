namespace platformer_engine {
    enum ConnectionStatus {
        Disconnected,
        Connecting,
        Connected,
        Disconnecting,
        Reconnecting,
        InitializingMap,
        WaitingForMap
    };
}// namespace platformer_engine