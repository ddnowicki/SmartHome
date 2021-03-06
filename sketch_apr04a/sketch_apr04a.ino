#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#include "index.h"

const char* ssid = "NaszaSiecExt";
const char* password = "1234123412";
String serverName = "http://192.168.9.13";
bool getesp = false;
int getdaniel = 0;
Adafruit_MCP23X17 mcp;
ESP8266WebServer server(80);


void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
  Serial.println("DANIEL ZGASIL");
}
void setup () {

  Serial.begin(115200);
  Wire.begin();
  while (!mcp.begin_I2C())
  {
    Serial.println("mcp error.");
    delay(1000);
  }
  mcp.pinMode(2, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
void loop() {

  while (mcp.digitalRead(2)) {
    server.handleClient();
    if (!mcp.digitalRead(2)) {
      Serial.println("GET");
      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName + "/";

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);
        }
        else {
          Serial.print("Error code: ");
          Serial.println(httpResponseCode);
        }
        // Free resources
        getdaniel = 0;
        http.end();
      }
    }
  }
}
