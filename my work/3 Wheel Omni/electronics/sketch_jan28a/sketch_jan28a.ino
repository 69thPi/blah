#include "ESP8266WiFi.h"


void setup() {
  Serial.begin(115200);
  WiFi.begin("Tanmay\xe2\x80\x99s iPhone", "pyrad007");  //Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println(".");
  }
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println(WiFi.localIP());
}

void loop() {
}
