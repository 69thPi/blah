#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "ping.h"

#define SW_1 14
#define SW_2 12 
#define SW_3 13
#define NET_LED 2

bool bool_1 = true;
bool bool_2 = true;
bool bool_3 = true;

ESP8266WebServer server(80);// port 80

IPAddress serverIP(0,0,0,0);

void set_states()
{
 if (bool_1){
  digitalWrite(SW_1,HIGH);  
 }
 else{
 digitalWrite(SW_1,LOW);
 }
 if (bool_2){
  digitalWrite(SW_2,HIGH);  
 }
 else{
 digitalWrite(SW_2,LOW);
 }
 if (bool_3){
  digitalWrite(SW_3,HIGH);  
 }
 else{
 digitalWrite(SW_3,LOW);
 }
}

void setup() {
  pinMode(SW_1,OUTPUT);
  pinMode(SW_2,OUTPUT);
  pinMode(SW_3,OUTPUT);
  digitalWrite(SW_1,HIGH); //off
  digitalWrite(SW_2,HIGH); //off
  digitalWrite(SW_3,HIGH); //off
  
  Serial.begin(115200);
  WiFi.begin("Tortilla", "Pyrad_3.14");  //Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println(".");
  }
  serverIP=WiFi.localIP();
  serverIP[3]=51;//set as the IP;
  IPAddress gateway=serverIP;
  gateway[3]=1;
  WiFi.config(serverIP, gateway, IPAddress(255,255,255,0), IPAddress(8,8,8,8), IPAddress(8,8,4,4));
  Serial.println(WiFi.localIP());

  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.on("/get",handleGetReq);
  server.begin();                    //Start the server
  pinMode(NET_LED,OUTPUT);
}

void loop() {
  server.handleClient();         //Handling of incoming requests
  if(WiFi.status()!=WL_CONNECTED){
    digitalWrite(NET_LED,HIGH);
  }
  else{
    digitalWrite(NET_LED,LOW);
  }
}

void handleRootPath() {            //Handler for the rooth path
  server.send(200, "text/html", index_html);
}

void handleGetReq() { //Handler
  Serial.println("recieved request");
  for (int i = 0; i < server.args(); i++) {
    if(server.argName(i)=="SW_1"){
      bool_1=!bool_1;
      Serial.println("one");
    }
    else if(server.argName(i)=="SW_2"){
      bool_2=!bool_2;

      
      Serial.println("two");
    }
    else if(server.argName(i)=="SW_3"){
      bool_3=!bool_3;
      Serial.println("three");
    }
  }
  set_states();
  server.send(200, "text/html", index_html);       //Response to the HTTP request
}
