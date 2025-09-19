#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "WebSocket.h"

WebSocket::WebSocket(const char* serverAddy, int port)
{
    strncpy(serverAddress, serverAddy, sizeof(serverAddress) - 1);
    serverAddress[sizeof(serverAddress) - 1] = '\0';

    myClient = new WebSocketClient(wifi, serverAddress, port);
}

WebSocket::~WebSocket()
{
    delete myClient;
}

void WebSocket::PingSerial()
{
    Serial.print("Socket Object Instantiated\n");
}

void WebSocket::PingServer()
{
    Serial.print("Pinging Server\n");
    myClient->beginMessage(TYPE_TEXT);
    myClient->print("Hewwo ");
    myClient->endMessage();
}

void WebSocket::NetworkConnect()
{
    int status = WL_IDLE_STATUS;

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        // print the network name (SSID);
        Serial.println(ssid);                   

        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);
    }

    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
}

void WebSocket::SocketConnect(String clientID)
{
    Serial.println("Starting WebSocket connection...");
  
    // Begin WebSocket connection
    myClient->begin();
    
    // Send client ID to server
    myClient->beginMessage(TYPE_TEXT);
    myClient->print(clientID);
    myClient->endMessage();
    
    Serial.println("WebSocket connected and client ID sent!");
    Serial.println("Listening for messages...");
}

bool WebSocket::ConnectionStatus()
{
    return myClient->connected();
}

void WebSocket::WriteServer(String message)
{
    Serial.print("Writing Server\n");
    myClient->beginMessage(TYPE_TEXT);
    myClient->print(message);
    myClient->endMessage();
}