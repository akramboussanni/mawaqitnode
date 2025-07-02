#include <WiFiClientSecure.h>
#include <HTTPClient.h>

class ApiClient {
public:
    static ApiClient& getInstance();

    bool get(const char* url, String& response);
    void end();

private:
    ApiClient();
    ~ApiClient();

    static ApiClient* instance;

    WiFiClientSecure wifiClient;
    HTTPClient http;
};
