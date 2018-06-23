#include <Arduino.h>
#include <pushio.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define pin 2 // lol pushio connect ke liye
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {
  pushio bulb("anah","3443");
  bulb.connect(pin);

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
      bulb.sync();
  }
}