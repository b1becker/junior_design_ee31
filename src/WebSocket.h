#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

class WebSocket
{
public:
    WebSocket(const char* serverAddy, int port);
    ~WebSocket();
    void NetworkConnect();
    void SocketConnect(String clientID);
    void PingSerial();
    void PingServer();
    bool ConnectionStatus();
    void WriteServer(String message);
    void ReadServer(String message);


private:
    WiFiClient wifi;
    WebSocketClient *myClient;
    int port;
    char serverAddress[13];
    const char ssid[11] = "tufts_eecs";
    const char pass[14] = "foundedin1883";
};

#endif
