// #include <Arduino.h>
// #include <ArduinoHttpClient.h>
// #include <WiFiNINA.h> 

// /////// you can enter your sensitive data in the Secret tab/arduino_secrets.h
// /////// WiFi Settings ///////
// char ssid[] = "tufts_eecs";
// char pass[] = "foundedin1883";

// char serverAddress[] = "34.28.153.91";  // server address
// int port = 80;

// WiFiClient wifi;
// WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
// String clientID = "56FC703ACE1A"; //Insert your Client ID Here!
// int status = WL_IDLE_STATUS;
// int count = 0;

// void setup() {
//   Serial.begin(9600);
//   while ( status != WL_CONNECTED) {
//     Serial.print("Attempting to connect to Network named: ");
//     Serial.println(ssid);                   // print the network name (SSID);

//     // Connect to WPA/WPA2 network:
//     status = WiFi.begin(ssid, pass);
//   }

//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your WiFi shield's IP address:
//   IPAddress ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);
// }

// void loop() {
//   Serial.println("Starting WebSocket connection...");
  
//   // Begin WebSocket connection
//   client.begin();
  
//   // Send client ID to server
//   client.beginMessage(TYPE_TEXT);
//   client.print(clientID);
//   client.endMessage();
  
//   Serial.println("WebSocket connected and client ID sent!");
//   Serial.println("Listening for messages...");
  
//   // Main communication loop
//   while (client.connected()) {
//     // Check for incoming messages
//     int messageSize = client.parseMessage();
//     if (messageSize > 0) {
//       Serial.println("Received a message:");
//       Serial.print("Message: ");
      
//       // Read and print the message
//       while (client.available()) {
//         Serial.print((char)client.read());
//       }
//       Serial.println();
//     }
    
//     // Send periodic messages (optional)
//     if (count % 10000 == 0) { // Send every ~10 seconds (adjust as needed)
//       client.beginMessage(TYPE_TEXT);
//       client.print("Hello from Arduino client: ");
//       client.print(clientID);
//       client.print(" - Message #");
//       client.print(count / 10000);
//       client.endMessage();
      
//       Serial.println("Sent periodic message to server");
//     }
    
//     count++;
//     delay(1); // Small delay to prevent overwhelming the loop
//   }
  
//   // If connection is lost, print message and attempt to reconnect
//   Serial.println("WebSocket connection lost. Attempting to reconnect...");
//   delay(5000); // Wait 5 seconds before trying to reconnect
// }