#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <FS.h>
#include <WebSocketsServer.h>

boolean isClient = true;


ESP8266WiFiMulti wifiMulti;
ESP8266WebServer Server(80);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

WebSocketsServer webSocket = WebSocketsServer(443);

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  if (isClient) {
    //APモード
    WiFi.mode(WIFI_AP);
    WiFi.softAP("poyo","hogehogehoge");
  } else {
    //クライアントモード
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP("ssid1","pspspspsps");
    wifiMulti.addAP("ssid2","pspspspsps");
    while (wifiMulti.run() != WL_CONNECTED) {
      delay(1000);
    }
  }
  Server.onNotFound(handleNotFound);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  Server.begin();
}


void loop() {
  Server.handleClient();
  webSocket.loop();
  webSocket.broadcastTXT("data");
}
