#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

class WebSocket
{
public:
    WebSocket(const char* serverAddy, int port, const char* ssid, const char* pass);
    ~WebSocket();
    void NetworkConnect();
    void SocketConnect(String clientID);
    void PingServer();
    bool ConnectionStatus();
    void WriteServer(String message);
    String ReadServer();
    String PartnerReadServer();


private:
    WiFiClient wifi;
    WebSocketClient *myClient;
    int port;
    char serverAddress[13];
    char ssid[11];
    char pass[14];
};

#endif
