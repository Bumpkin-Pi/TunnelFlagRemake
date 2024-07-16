//
// Created by holly on 16/07/24.
//

#define MAX_PACKET_CHARS 4096
#include <iostream>
#include "network/client.h"
extern bool closing;

Client::~Client() {
    SDLNet_TCP_Close(client);
    SDLNet_Quit();
}

Client::Client() {
    SDLNet_Init();
}

void Client::connect(std::string newIP, int newPort) {
    port = newPort;
    SDLNet_ResolveHost(&ip, newIP.c_str(), newPort);
    client = SDLNet_TCP_Open(&ip);
}

void Client::listener() {
    while (!closing){
        char text[MAX_PACKET_CHARS];
        int len = SDLNet_TCP_Recv(client, text, MAX_PACKET_CHARS);
        if (len <= 0) {
            std::cerr << "Error or connection closed: " << SDLNet_GetError() << std::endl;
            break;
        }
        text[len] = '\0';
        std::unique_lock<std::mutex> recvLock(recvMutex);
        recvBuffer += text;
        recvLock.unlock();
    }
}

void Client::send() {
    std::unique_lock<std::mutex> sendLock(sendMutex);
    SDLNet_TCP_Send(client, sendBuffer.c_str(), strlen(sendBuffer.c_str()));
    sendBuffer = "";
    sendLock.unlock();
}
