#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "file.h"

ESP8266WebServer server(80);// port 80



String coord_matrix[32]={"WKi","WQu","WB1","WB2","WK1","WK2","WR1","WR2",
                         "WP1","WP2","WP3","WP4","WP5","WP6","WP7","WP8",
                         "BKi","BQu","BB1","BB2","BK1","BK2","BR1","BR2",
                         "BP1","BP2","BP3","BP4","BP5","BP6","BP7","BP8"};//holds board coodinates for each piece.// chess board

IPAddress serverIP(0,0,0,0);

int get_index(String a){
  if (a=="WKi")
  return 0;
  else if(a=="WQu")
  return 1;
  else if(a=="WB1")
  return 2;
  else if(a=="WB2")
  return 3;
  else if(a=="WK1")
  return 4;
  else if(a=="WK2")
  return 5;
  else if(a=="WR1")
  return 6;
  else if(a=="WR2")
  return 7;
  else if(a=="WP1")
  return 8;
  else if(a=="WP2")
  return 9;
  else if(a=="WP3")
  return 10;
  else if(a=="WP4")
  return 11;
  else if(a=="WP5")
  return 12;
  else if(a=="WP6")
  return 13;
  else if(a=="WP7")
  return 14;
  else if(a=="WP8")
  return 15;
  else if(a=="BKi")
  return 16;
  else if(a=="BQu")
  return 17;
  else if(a=="BB1")
  return 18;
  else if(a=="BB2")
  return 19;
  else if(a=="BK1")
  return 20;
  else if(a=="BK2")
  return 21;
  else if(a=="BR1")
  return 22;
  else if(a=="BR2")
  return 23;
  else if(a=="BP1")
  return 24;
  else if(a=="BP2")
  return 25;
  else if(a=="BP3")
  return 26;
  else if(a=="BP4")
  return 27;
  else if(a=="BP5")
  return 28;
  else if(a=="BP6")
  return 29;
  else if(a=="BP7")
  return 30;
  else if(a=="BP8")
  return 31;
}

void setup() {
  Serial.begin(115200);
  WiFi.begin("black", "pyrad007");  //Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println(".");
  }
  serverIP=WiFi.localIP();
  serverIP[3]=50;//set as the IP;
  IPAddress gateway=serverIP;
  gateway[3]=1;
  WiFi.config(serverIP, gateway, IPAddress(255,255,255,0), IPAddress(8,8,8,8), IPAddress(8,8,4,4));
  Serial.println(WiFi.localIP());

  server.on("/", handleRootPath);    //Associate the handler function to the path
  server.on("/get",handleGetReq);
  //whites
  server.on("/WKi",whiteKing);
  server.on("/WQu",whiteQueen);
  server.on("/WB1",whiteBishop1);
  server.on("/WB2",whiteBishop2);
  server.on("/WK1",whiteKnight1);
  server.on("/WK2",whiteKnight2);
  server.on("/WR1",whiteRook1);
  server.on("/WR2",whiteRook2);
  server.on("/WP1",whitePawn1);
  server.on("/WP2",whitePawn2);
  server.on("/WP3",whitePawn3);
  server.on("/WP4",whitePawn4);
  server.on("/WP5",whitePawn5);
  server.on("/WP6",whitePawn6);
  server.on("/WP7",whitePawn7);
  server.on("/WP8",whitePawn8);
  //blacks
  server.on("/BKi",blackKing);
  server.on("/BQu",blackQueen);
  server.on("/BB1",blackBishop1);
  server.on("/BB2",blackBishop2);
  server.on("/BK1",blackKnight1);
  server.on("/BK2",blackKnight2);
  server.on("/BR1",blackRook1);
  server.on("/BR2",blackRook2);
  server.on("/BP1",blackPawn1);
  server.on("/BP2",blackPawn2);
  server.on("/BP3",blackPawn3);
  server.on("/BP4",blackPawn4);
  server.on("/BP5",blackPawn5);
  server.on("/BP6",blackPawn6);
  server.on("/BP7",blackPawn7);
  server.on("/BP8",blackPawn8);

  server.begin();                    //Start the server
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  server.handleClient();         //Handling of incoming requests
}

void handleRootPath() {            //Handler for the rooth path
  server.send(200, "text/html", index_html);
}

void handleGetReq() { //Handler
  Serial.println("recieved request");
  for (int i = 0; i < server.args(); i++) {
    coord_matrix[get_index(server.argName(i))]=server.arg(i); //set the value of the paramter as the new coordinate...use key value here BK1-a6
  }
  server.send(200, "text/html", index_html);       //Response to the HTTP request
}
//white
void whiteKing(){server.send(200,"text/plain",coord_matrix[0]);}
void whiteQueen(){server.send(200,"text/plain",coord_matrix[1]);}
void whiteBishop1(){server.send(200,"text/plain",coord_matrix[2]);}
void whiteBishop2(){server.send(200,"text/plain",coord_matrix[3]);}
void whiteKnight1(){server.send(200,"text/plain",coord_matrix[4]);}
void whiteKnight2(){server.send(200,"text/plain",coord_matrix[5]);}
void whiteRook1(){server.send(200,"text/plain",coord_matrix[6]);}
void whiteRook2(){server.send(200,"text/plain",coord_matrix[7]);}
void whitePawn1(){server.send(200,"text/plain",coord_matrix[8]);}
void whitePawn2(){server.send(200,"text/plain",coord_matrix[9]);}
void whitePawn3(){server.send(200,"text/plain",coord_matrix[10]);}
void whitePawn4(){server.send(200,"text/plain",coord_matrix[11]);}
void whitePawn5(){server.send(200,"text/plain",coord_matrix[12]);}
void whitePawn6(){server.send(200,"text/plain",coord_matrix[13]);}
void whitePawn7(){server.send(200,"text/plain",coord_matrix[14]);}
void whitePawn8(){server.send(200,"text/plain",coord_matrix[15]);}
//black
void blackKing(){server.send(200,"text/plain",coord_matrix[16]);}
void blackQueen(){server.send(200,"text/plain",coord_matrix[17]);}
void blackBishop1(){server.send(200,"text/plain",coord_matrix[18]);}
void blackBishop2(){server.send(200,"text/plain",coord_matrix[19]);}
void blackKnight1(){server.send(200,"text/plain",coord_matrix[20]);}
void blackKnight2(){server.send(200,"text/plain",coord_matrix[21]);}
void blackRook1(){server.send(200,"text/plain",coord_matrix[22]);}
void blackRook2(){server.send(200,"text/plain",coord_matrix[23]);}
void blackPawn1(){server.send(200,"text/plain",coord_matrix[24]);}
void blackPawn2(){server.send(200,"text/plain",coord_matrix[25]);}
void blackPawn3(){server.send(200,"text/plain",coord_matrix[26]);}
void blackPawn4(){server.send(200,"text/plain",coord_matrix[27]);}
void blackPawn5(){server.send(200,"text/plain",coord_matrix[28]);}
void blackPawn6(){server.send(200,"text/plain",coord_matrix[29]);}
void blackPawn7(){server.send(200,"text/plain",coord_matrix[30]);}
void blackPawn8(){server.send(200,"text/plain",coord_matrix[31]);}
