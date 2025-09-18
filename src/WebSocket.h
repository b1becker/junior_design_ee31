#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

class WebSocket
{
private:
    char* ssid;
    char* pass;
    char* serverAddress;
    int port;
    String clientID;

    WebSocketClient client;

public:
    WebSocket(char* network, char* password, char* server, int portId,
                                                                String botId);
    WebSocket();
    ~WebSocket();
    void WebSocket::loop();
};

#endif
