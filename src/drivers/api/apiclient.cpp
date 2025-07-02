#include "drivers/api/apiclient.h"
#include <Arduino.h>

// Static instance pointer initialization
ApiClient* ApiClient::instance = nullptr;

ApiClient& ApiClient::getInstance() {
    if (instance == nullptr) {
        instance = new ApiClient();
        instance->wifiClient.setInsecure();
    }
    return *instance;
}

ApiClient::ApiClient() {}

ApiClient::~ApiClient() {
    http.end();
}

bool ApiClient::get(const char* url, String& response) {
    http.begin(wifiClient, url);
    int code = http.GET();

    if (code > 0) {
        response = http.getString();
        http.end();
        return true;
    } else {
        http.end();
        return false;
    }
}

void ApiClient::end() {
    http.end();
}
