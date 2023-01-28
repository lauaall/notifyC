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
