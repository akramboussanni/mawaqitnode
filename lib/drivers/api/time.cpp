#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <drivers/api/apiclient.h>

ApiClient& api = ApiClient::getInstance();

String getTimezone() {
    String response;
    if (api.get("http://worldtimeapi.org/api/ip", response)) {
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, response);

        if (error) {
            return "err while deserializing tz info";
        }

        return doc["timezone"];
    }

    return "err while fetching tz info";
}
