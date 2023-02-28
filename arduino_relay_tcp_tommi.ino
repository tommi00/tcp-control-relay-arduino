#include "Ethernet.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    // mac address (keep this one when unknown)
byte ip[] = { 192, 168, 2, 159 };                       // ip address
byte gateway[] = { 192, 168, 2, 1 };                    // gateway rete
byte subnet[] = { 255, 255, 255, 0 };                   // subnet mask

unsigned int port = 9002;                               // local port to listen on

const int RELAY1_PIN  = 2;                              // relay pins
const int RELAY2_PIN  = 3;
const int RELAY3_PIN  = 4;
const int RELAY4_PIN  = 5;

String stringReceived;

EthernetServer server(port);

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);  

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
  digitalWrite(RELAY4_PIN, HIGH);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
}


void loop() {
  EthernetClient client = server.available();

  if (client.connected()) {
    stringReceived = "";
    while (client.available()) {
      char c = client.read();
      stringReceived = stringReceived + c;
    }
    Serial.println("command received: " + stringReceived);

    if (stringReceived == "PON1") {
      client.print("okPON1");                   //ack to client
      digitalWrite(RELAY1_PIN, LOW);            //turn on relay
      Serial.println("relay 1 turned on");      //serial print
    }else if (stringReceived == "POF1") {
      client.print("okPOF1");
      digitalWrite(RELAY1_PIN, HIGH);
      Serial.println("relay 1 turned off"); 
    }else if (stringReceived == "PON2") {
      client.print("okPON2");
      digitalWrite(RELAY2_PIN, LOW);
      Serial.println("relay 2 turned on");      
    }else if (stringReceived == "POF2") {
      client.print("okPOF2");
      digitalWrite(RELAY2_PIN, HIGH);
      Serial.println("relay 2 turned off"); 
    }else if (stringReceived == "PON3") {
      client.print("okPON3");
      digitalWrite(RELAY3_PIN, LOW);
      Serial.println("relay 3 turned on");      
    }else if (stringReceived == "POF3") {
      client.print("okPOF3");
      digitalWrite(RELAY3_PIN, HIGH);
      Serial.println("relay 3 turned off"); 
    }else if (stringReceived == "PON4") {
      client.print("okPON4");
      digitalWrite(RELAY4_PIN, LOW);
      Serial.println("relay 4 turned on");      
    }else if (stringReceived == "POF4") {
      client.print("okPOF4");
      digitalWrite(RELAY4_PIN, HIGH);
      Serial.println("relay 4 turned off"); 
    }else if (stringReceived == "PONALL") {
      client.print("okPONALL");
      digitalWrite(RELAY1_PIN, LOW);
      digitalWrite(RELAY2_PIN, LOW);
      digitalWrite(RELAY3_PIN, LOW);
      digitalWrite(RELAY4_PIN, LOW);
      Serial.println("all relay turned on");
    }else if (stringReceived == "POFALL") {
      client.print("okPOFALL");
      digitalWrite(RELAY1_PIN, HIGH);
      digitalWrite(RELAY2_PIN, HIGH);
      digitalWrite(RELAY3_PIN, HIGH);
      digitalWrite(RELAY4_PIN, HIGH);
      Serial.println("all relay turned off"); 
    }else{
      client.print("wrong_command");
    }
  
  }
  //tommi
  //https://github.com/tommi00
}
