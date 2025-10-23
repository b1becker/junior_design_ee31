#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>

#include "WebSocket.h"
/********** Constructor ********
*
* Sets all needed strings to establish connection
*
* Parameters:
*      Server Address
*      Port
*      SSID
*      Password
************************/
WebSocket::WebSocket(const char* serverAddy, int port, const char* id, const char* password)
{
    strncpy(serverAddress, serverAddy, sizeof(serverAddress) - 1);
    serverAddress[sizeof(serverAddress) - 1] = '\0';

    strncpy(ssid, id, sizeof(ssid) - 1);
    ssid[sizeof(ssid) - 1] = '\0';

    strncpy(pass, password, sizeof(pass) - 1);
    pass[sizeof(pass) - 1] = '\0';

    myClient = new WebSocketClient(wifi, serverAddress, port);
}

/********** Desctucor ********
*
* Deletes Dynamically allocated object
*
************************/
WebSocket::~WebSocket()
{
    delete myClient;
}


/********** Network Connect ********
*
* Connects to the EE31 WiFi Network
*
************************/
void WebSocket::NetworkConnect()
{
    int status = WL_IDLE_STATUS;

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");

        Serial.println(ssid);                   


        status = WiFi.begin(ssid, pass);
    }


    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());


    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
}

/********** Socket Connect ********
*
* Connects to the EE31 Web Socket
*
************************/
void WebSocket::SocketConnect(String clientID)
{
    Serial.println("Starting WebSocket connection...");
  

    myClient->begin();
    

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

/********** Unique Server Write Message to confirm connection ********
*
* Hewwo
*
************************/
void WebSocket::PingServer()
{
    Serial.print("Pinging Server\n");
    myClient->beginMessage(TYPE_TEXT);
    myClient->print("Hewwo ");
    myClient->endMessage();
}

/********** Server Write********
*
* Notes:
*   Only processes strings rn
*
************************/
void WebSocket::WriteServer(String message)
{
    Serial.println("Writing Server\n");
    myClient->beginMessage(TYPE_TEXT);
    myClient->print(message);
    myClient->endMessage();
}

/********** ReadServer ********
*
* Reads message from server
* Parses message to see if from us
* Further parses to see if a recognized command.
*
************************/
String WebSocket::ReadServer()
{
    String message = "";
    String ID = "WebClient_56FC703ACE1A";
    String command;
    bool ours;
    bool valid_com;
    int messageSize = myClient->parseMessage();
    if (messageSize > 0) {      
        while (myClient->available()) {
            message += (char)myClient->read();
        }
        for (unsigned int i = 0; i < ID.length(); i++)
        {
            if(message.charAt(i) == ID.charAt(i))
            {
                ours = true;
                continue;
            } else {
                ours = false;
                break;
            }
        }

        if(ours == true)
        {
            command = message.substring(ID.length() + 1);

            if(command.charAt(0) == 'C'){
                return command.substring(1);
            }
        }
    }
    return "NULL";   
}

/********** PartnerReadServer ********
*
* Reads message from server
* Parses message to see if from us
* Further parses to see if a recognized command.
*
************************/
String WebSocket::PartnerReadServer()
{
    String message = "";
    String partner_ID ="F79721857DC5";
    String command;
    bool ours;
    bool valid_com;
    int messageSize = myClient->parseMessage();
    if (messageSize > 0) {      
        while (myClient->available()) {
            message += (char)myClient->read();
        }
        for (unsigned int i = 0; i < partner_ID.length(); i++)
        {
            if(message.charAt(i) == partner_ID.charAt(i))
            {
                ours = true;
                continue;
            } else {
                ours = false;
                break;
            }
        }
        if(ours == true)
        {
            command = message.substring(partner_ID.length() + 1);

            if(command.charAt(0) == '_'){
                command = command.substring(6);
            }
            //Command Parsing Code:
            //C1? Some other form.
            Serial.println(command);
        }
    }
    return "NULL";   
}