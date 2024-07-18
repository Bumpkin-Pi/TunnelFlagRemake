//
// Created by holly on 16/07/24.
//

#ifndef TUNNELFLAGREMAKE_CLIENT_H
#define TUNNELFLAGREMAKE_CLIENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <string>
#include <mutex>


class Client {
private:
    IPaddress ip{};
    int port = 0;
    TCPsocket client{};
public:
    std::string sendBuffer,recvBuffer; // Buffers for processing and sending packets.
    std::mutex sendMutex, recvMutex;

    Client();
    ~Client();

    void connect(std::string ip, int port);
    void listener();
    void send();
    void addToSendBuffer(std::string packet);

};


#endif //TUNNELFLAGREMAKE_CLIENT_H
