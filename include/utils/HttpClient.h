//
// Created by SamiH on 20/08/2024.
//

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    // Method to perform a GET request
    std::string get(const std::string& url);

    // Method to perform a POST request
    std::string post(const std::string& url, const std::string& data);

private:
    // Callback function to handle data received from libcurl
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

    // CURL instance
    CURL* curl;
};

#endif // HTTPCLIENT_H