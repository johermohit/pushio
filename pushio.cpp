#include "Arduino.h"
#include "pushio.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

pushio::pushio(String deviceID, String key)
{
    _deviceID = deviceID;
    _key = key;
}


String pushio::get()
{
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
    http.begin("https://pushio.azurewebsites.net/getState/" + (String)_deviceID + "?key=" + (String)_key, "3A B0 B1 C2 7F 74 6F D9 0C 34 F0 D6 A9 60 CF 73 A4 22 9D E8");
    http.addHeader("Content-Type", "application/json");

    USE_SERIAL.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            return payload;
        }
        else
        {
            return (String)httpCode;
        }
    }
    else
    {
        return (String)httpCode;
    }

    return (String)'0x5';
}

int pushio::current_state()
{
    var  this.get();
        if(state=="0")
        return 0;
    else{
        return 1;
    }
}

String pushio::put(String state)
{
    String data = '{\"key\":'+(String) _key'}';
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
    http.begin("https://pushio.azurewebsites.net/getState/" + (String)_deviceID + "?key=" + (String) _key, "3A B0 B1 C2 7F 74 6F D9 0C 34 F0 D6 A9 60 CF 73 A4 22 9D E8");
    http.addHeader("Content-Type", "application/json");

    USE_SERIAL.print("[HTTP] PUT...\n");
    int httpCode = http.PUT(data);

    if (httpCode > 0)
    {
        USE_SERIAL.printf("[HTTP] PUT... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            return payload;
        }
        else
        {
            return (String)httpCode;
        }
    }
    else
    {
        return (String)httpCode;
    }

    return (String)'0x5';
}

String pushio::toggle()
{
    return this.put();
}

void pushio::connect(int pin)
{
    _pin = pin;
    pinMode(pin, OUTPUT);
    int state = this.get();
    if(state=="0")
        digitalWrite(pin, LOW);
    else{
        digitalWrite(pin, HIGH);
    }
}

// Error codes
// 0x5 http get error

String pushio::sync(){
    int state = this.current_state();
    digitalWrite(_pin, state);
}