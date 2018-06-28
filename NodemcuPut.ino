 // add wifiname and password
// create the url according to your device and key
//

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT); 

  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("JioFi2_0B9548", "pizz@isbae");

}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {

 StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject(); 

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

    HTTPClient http;   
    USE_SERIAL.print("[HTTP] begin...\n");
    // instead of deviceID write your own device ID and enter the value of your key in key = you
    http.begin("https://pushio.azurewebsites.net/getState/anah?key=3443","3A B0 B1 C2 7F 74 6F D9 0C 34 F0 D6 A9 60 CF 73 A4 22 9D E8"); 
    // change the code according to your device
    http.addHeader("Content-Type", "application/json");  
 
    USE_SERIAL.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
          if(payload=="0"){
            digitalWrite(12, HIGH);}
          else
            {digitalWrite(12, LOW);}
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

}
