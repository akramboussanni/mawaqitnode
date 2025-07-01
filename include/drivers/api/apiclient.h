class ApiClient {
public:
    static ApiClient& getInstance();

    bool get(const char* url, String& response);
    void end();

private:
    ApiClient();
    ~ApiClient();

    static ApiClient* instance;

    WiFiClient wifiClient;
    HTTPClient http;
};
