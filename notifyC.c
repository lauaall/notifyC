#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>
#include <jansson.h>

typedef struct {
  int code;
  char* shortmessage;
  char* longmessage;
} HTTP_response;

HTTP_response responses[] = {
    {100, "Continue", "Request received, please continue"},
    {101, "Switching Protocols", "Switching to new protocol; obey Upgrade header"},
    {200, "OK", "Request fulfilled, document follows"},
    {201, "Created", "Document created, URL follows"},
    {202, "Accepted", "Request accepted, processing continues off-line"},
    {203, "Non-Authoritative Information", "Request fulfilled from cache"},
    {204, "No Content", "Request fulfilled, nothing follows"},
    {205, "Reset Content", "Clear input form for further input."},
    {206, "Partial Content", "Partial content follows."},
    {300, "Multiple Choices", "Object has several resources -- see URI list"},
    {301, "Moved Permanently", "Object moved permanently -- see URI list"},
    {302, "Found", "Object moved temporarily -- see URI list"},
    {303, "See Other", "Object moved -- see Method and URL list"},
    {304, "Not Modified", "Document has not changed since given time"},
    {305, "Use Proxy", "You must use proxy specified in Location to access this resource."},
    {307, "Temporary Redirect", "Object moved temporarily -- see URI list"},
    {400, "Bad Request", "Bad request syntax or unsupported method"},
    {401, "Unauthorized", "No permission -- see authorization schemes"},
    {402, "Payment Required", "No payment -- see charging schemes"},
    {403, "Forbidden", "Request forbidden -- authorization will not help"},
    {404, "Not Found", "Nothing matches the given URI"},
    {405, "Method Not Allowed", "Specified method is invalid for this server."},
    {406, "Not Acceptable", "URI not available in preferred format."},
    {407, "Proxy Authentication Required", "You must authenticate with this proxy before proceeding."},
    {408, "Request Timeout", "Request timed out; try again later."},
    {409, "Conflict", "Request conflict."},
    {410, "Gone", "URI no longer exists and has been permanently removed."},
    {411, "Length Required", "Client must specify Content-Length."},
    {412, "Precondition Failed", "Precondition in headers is false."},
    {413, "Request Entity Too Large", "Entity is too large."},
    {414, "Request-URI Too Long", "URI is too long."},
    {415, "Unsupported Media Type", "Entity body in unsupported format."},
    {416, "Requested Range Not Satisfiable", "Cannot satisfy request range."},
    {417, "Expectation Failed", "Expect condition could not be satisfied."},
    {430, "Too many requests", "The request header fields are too large"},
    {500, "Internal Server Error", "Server got"
    {501, "Not Implemented","Server does not support this operation"},

    {502, 'Bad Gateway', 'Invalid responses from another server/proxy.'},
    {503, 'Service Unavailable','The server cannot process the request due to a high load'},
    {504, 'Gateway Timeout','The gateway server did not receive a timely response'},
    {505, 'HTTP Version Not Supported', 'Cannot fulfill request.'},

int main(void) {
    CURL *curl;
    CURLcode res;
    json_t *root;
    json_error_t error;
    char *out;
    int status_code;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://lab401.com/products/flipper-zero.js");
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            printf("Error: %s\n", curl_easy_strerror(res));
            return 1;
        }

        if(status_code > 200) {
            printf("\nAn Error occured: Unknown Error\n");
            printf("%s", asctime(localtime(&time(NULL))));
            return 1;
        }

        root = json_loads(out, 0, &error);
        if(json_object_get(json_array_get(json_object_get(root, "variants"), 0), "available") == json_true()) {
            printf("\nIn stock\n%s", asctime(localtime(&time(NULL))));
            //notify();
            exit(0);
        } else {
            printf("\nNot in stock\n%s", asctime(localtime(&time(NULL))));
            //printf("Requests: %d\n\n", i);
        }
    }
    return 0;
}
