#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#define RELAY1 7

BridgeServer server;
void setup() {
  // Bridge startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  pinMode(RELAY1, OUTPUT);

  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  BridgeClient client = server.accept();
  // There is a new client?
  if (client) {
    // Process request
    process(client);
    // Close connection and free resources.
    client.stop();
  }
  delay(50); // Poll every 50ms
}
void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');
  // el comando es "arduino/relay/"
  if (command == "relay") {
    raley(client);
  }
}

void raley(BridgeClient client) {
  int pos;
  pos = client.parseInt();
  digitalWrite(RELAY1,pos);

  client.println("Status: 200");
  client.println("Access-Control-Allow-Origin: *");   
  client.println("Access-Control-Allow-Methods: GET");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.print(F("Relay esta "));
  client.print(pos);
}
