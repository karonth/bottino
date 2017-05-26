/**
* Bottino
* Bottino è un bot telegram, sviluppato in arduino e basato su una matrice a led.
* Le dimensioni compatte e la connettività wifi permettono di integrarlo in oggetti IOT per dare una dimensione fisica all'interazione virtuale.
*
* Lo trovate su telegram come @Bottino_bot  
*                                                      
* written by Enkel Bici
*
* Based on examples from Adafruit & UniversalTelegramBot library
*/
 
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "LedControl.h"
 
LedControl lc=LedControl(D4,D2,D3,1);
 
// Initialize Wifi connection to the router
char ssid[] = "ssid";     // your network SSID (name)
char password[] = "password"; //"Toolbox.Torino"; // your network key

 
// Initialize Telegram BOT
#define BOTtoken "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // your Bot Token (Get from Botfather)
String botname = "Bottino";
 
WiFiClientSecure client;
//bool debug = false;
UniversalTelegramBot bot(BOTtoken, client);
 
int Bot_mtbs = 500; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

//:) ::) :O :P
byte face[][8] {
 {B00000000,
  B11000011,
  B00000000,
  B00011000,
  B00000000,
  B10000001,
  B01111110,
  B00000000},
 {B11000011,
  B11000011,
  B00000000,
  B00011000,
  B00000000,
  B10000001,
  B01111110,
  B00000000},
 {B11000011,
  B11000011,
  B00000000,
  B00011000,
  B00000000,
  B01111110,
  B01000010,
  B01111110},
 {B11000000,
  B11000011,
  B00000000,
  B00011000,
  B00000000,
  B00000000,
  B01111110,
  B00001100}};

int faceOn = 0; //which face is on at the moment
  
void setface(int whichface){
  faceOn = whichface;
  for(int i = 0; i < 8; i++){
    lc.setRow(0,i,face[faceOn][i]);
  }
}
 
void toggleFace(){   
  if(faceOn == 1){
    setface(0);
  }
  else{
    setface(1);
  }
}
 
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  //Serial.println(String(numNewMessages));
 
  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
 
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
 
    Serial.print("Chat id ");
    Serial.println(chat_id);
    Serial.print("Text - ");
    Serial.println(text);

    if (text == "ud83dude00") {
      bot.sendChatAction(chat_id, "typing");
      setface(0);
 
      bot.sendMessage(chat_id, "😀");
    }

    if (text == "ud83dude32" || text == ":O@"+botname) {
      bot.sendChatAction(chat_id, "typing");
      setface(2);
 
      bot.sendMessage(chat_id, "😲");
    }
 
    if (text == "ud83dude1c") {
      bot.sendChatAction(chat_id, "typing");
      setface(3);
 
      bot.sendMessage(chat_id, "😜");
    }
 
    if (text == "/start" || text == "/help" || text == "/start@"+botname || text == "/help@"+botname) {
      String welcome = "Hello " + from_name + " - This is "+botname+".\n";
      welcome += "This bot controls a led matrix\n";
      welcome += "😀 - print a smiley face\n";
      welcome += "😜 - print a funny face\n";
      welcome += "😲 - print a surprised face\n";

      bot.sendMessage(chat_id, welcome);
    }
  }
}

void setup() {
  Serial.begin(115200);
 
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,4);
  /* and clear the display */
  lc.clearDisplay(0);
 
  toggleFace(); //set a smiling face

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    toggleFace(); //while trying to connect toggle face, so it'll show something
    delay(500);
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
} 
 
void loop() {
 
  if (millis() > Bot_lasttime + Bot_mtbs) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
    while(numNewMessages) {
      //Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
 
    Bot_lasttime = millis();

    //bot.sendMessage("119024550", "😜");
  }
 
}
