#include <SPI.h>
#include <MFRC522.h>
#include <WiFiUdp.h>
#include <NTPClient.h> 
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define RST_PIN         0                             //D3 on ESP8266
#define SS_PIN          4                             //D2 on ESP8266

MFRC522 mfrc522(SS_PIN, RST_PIN);                     // Create MFRC522 instance
MFRC522::MIFARE_Key key;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

///////////////////////////////////////////////////////  SETUP  ////////////////////////////////////////////////////////
                                                                                                                      //
const char* ssid     = "Tanmay\xe2\x80\x99s iPhone"; // YOUR WiFi NAME                                                //
const char* password = "pyrad007";                   // YOUR WiFi PASSWORD                                            //
String ipaddress="172.20.10.3";                      //server IP Address Fixed (Set as Static from router)            //
String path = "/practice/index.php";                                                                                  //
                                                                                                                      //
String Station= "St3";                               //STATION ID -different for each station.                        //
                                                     //XX0X for inventory and XX00 for other.                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int blockNum=60,sno=0;                                               //RFID data block, workpiece index

String mainSerial,preSerial="";                                      //serial number style

byte bufferLen=18;
byte newBlockData [16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};            //Serial number to insert
byte readBlockData[18];

bool baseStn=false;

unsigned long elapsed=0,save_t=0;

MFRC522::StatusCode status;

void setup() {
  SPI.begin();                      // Init SPI bus
  mfrc522.PCD_Init();               // Init MFRC522 
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }
  digitalWrite(LED_BUILTIN,LOW);
  timeClient.begin();               // time stamp
  Serial.begin(115200);             // Initialize serial communications with the PC
  if(Station=="St0"){
        baseStn=true;
        Serial.print("Enter serial number::");
        while(Serial.available()==0){}
        sno= Serial.readString().toInt();
        Serial.println(sno);
  }
  Serial.println("===============================");
  Serial.println("    Scan card...");
}

void set_id()
{
  for(int i=0;i<16;i++){ //put serial number
    newBlockData[i]=mainSerial[i];
  }
  sno=sno+1;
}


String set_url(String foo){
  String getData = "?sno=" + foo + "&locn=" + Station;
  String ext = "&chng=2&secs="+String(elapsed);
  if(!baseStn)
  {
    getData+= ext;
  }
  
  return "http://" + ipaddress + path + getData;
}

void WriteDataToBlock(int fooNum, byte foo[]) 
{
  for (byte i=0;i<6;i++){
    key.keyByte[i] = 0xFF;
  }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, fooNum, &key, &(mfrc522.uid));
  if (status == MFRC522::STATUS_OK){
    if (mfrc522.MIFARE_Write(fooNum, foo, 16) == MFRC522::STATUS_OK){
    Serial.println("Card Written Successfully!");}
  }
  else{Serial.println("Error 103: Authentication Issue");} 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}


void ReadDataFromBlock(int fooNum, byte foo[]) 
{
  for (byte i=0;i<6;i++){
    key.keyByte[i] = 0xFF;
  }
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, fooNum, &key, &(mfrc522.uid));
  
  if (status == MFRC522::STATUS_OK){
     if( mfrc522.MIFARE_Read(fooNum, foo, &bufferLen) == MFRC522::STATUS_OK){
        Serial.println("Card Read Successfully!");
        }
     else{
      Serial.println("Error 101: Read issue");
      }
  }
  else{
    Serial.println("Error 102: Authentication issue");}
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void loop() {
  //#keep blue LED on for wifi status.
  if(WiFi.status() != WL_CONNECTED){
     digitalWrite(LED_BUILTIN,HIGH);                  //if network broken LED-> OFF
     WiFi.begin(ssid, password);
  }
  else{
    digitalWrite(LED_BUILTIN,LOW); 
  }
  //#RFID DETECT CODEBIT
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) {
    return;
    }
  //#database talk #//
  HTTPClient http;
  String url="http://"+ipaddress+path;
  digitalWrite(LED_BUILTIN,HIGH);                     //LED status working.
  if(baseStn){                                        //inventory station
          Serial.print(F("Card UID:"));
          for (byte i=0;i<mfrc522.uid.size; i++){
             Serial.print(mfrc522.uid.uidByte[i] <0x10? "0" : " " );
             Serial.print(mfrc522.uid.uidByte[i], HEX);
          }
         Serial.println(" ");
         mainSerial=preSerial+String(sno);
         Serial.print("SERIAL NUMBER::");
         Serial.println(mainSerial);
         Serial.println("***** Process Status *****");
         url= set_url(mainSerial);
         for(int i=0;i<16;i++){                        //put serial number into newBlockData
             newBlockData[i]=mainSerial[i];
             }
         WriteDataToBlock(blockNum, newBlockData);    //Write into RFID
         set_id();                                    //auto-update the serial number
  }
  else{                                               // work station
         ReadDataFromBlock(blockNum, readBlockData);  //put serial number into readBlockData
         char ig[18];
         int j;
         for (j=0 ; j<16 ; j++){
            //Serial.write(readBlockData[j]);         //print bit data.
            ig[j]=readBlockData[j];
            }
         ig[j]='\0';
          ////set elapsd if punch in is true, else set elapsed to 0
         if(mainSerial==ig){
             timeClient.update();
             elapsed=timeClient.getEpochTime() -save_t;
         }
         else{
             mainSerial=ig;
             timeClient.update();
             save_t=timeClient.getEpochTime();
             elapsed=0;
         }
         url= set_url(ig);                            //set url for database update.
   }
   http.begin(url);
   Serial.println("Contacting Server...");
   while(http.GET()!=200);
   http.end();
   Serial.println("Database updated");
   Serial.println("===============================");
   if(baseStn){
    Serial.println("    Scan next card");
    Serial.println("===============================");
   }
}
