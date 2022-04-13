/*
   Hello world web server
   circuits4you.com
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include "index.h" //Our HTML webpage contents

//SSID and Password of your WiFi router
const char* ssid = "NaszaSiecExt";
const char* password = "1234123412";
String serverName = "http://192.168.9.17";
bool DANIEL = false;
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(13, LOW);
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void) {
  Serial.begin(115200);

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void) {
  server.handleClient();
    if (digitalRead(12))
    {

      while (digitalRead(12))
      {
        delay(20);
      }
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
        http.end();
      }
    }
  }
}
