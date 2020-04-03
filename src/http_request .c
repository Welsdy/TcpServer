//
// Created by mycentos on 2020/4/2.
//

#include "http_request .h"

#define INIT_REQUEST_HEADER_SIZE 128

const char *HTTP10 = "HTTP/1.0";
const char *HTTP11 = "HTTP/1.1";
const char *KEEP_ALIVE = "Keep-Alive";
const char *CLOSE = "close";

// init
struct http_request *http_request_new() {
    struct http_request *httpRequest = malloc(sizeof(struct http_request));
    httpRequest->method = NULL;
    httpRequest->current_state = REQUEST_STATUS;
    httpRequest->version = NULL;
    httpRequest->url = NULL;
    httpRequest->requestHeaders = malloc(sizeof(struct http_request) * INIT_REQUEST_HEADER_SIZE);
    httpRequest->request_headers_number = 0;
    return httpRequest;
}

// clear
void http_request_clear(struct http_request *httpRequest) {
    if (httpRequest->requestHeaders != NULL) {
        for (int i = 0; i < httpRequest->request_headers_number; i++) {
            free(httpRequest->requestHeaders[i].key);
            free(httpRequest->requestHeaders[i].value);
        }
        free(httpRequest->requestHeaders);
    }
    free(httpRequest);
}

// reset
void http_request_reset(struct http_request *httpRequest) {
    httpRequest->method = NULL;
    httpRequest->current_state = REQUEST_STATUS;
    httpRequest->version = NULL;
    httpRequest->url = NULL;
    httpRequest->request_headers_number = 0;
}

// add header
void http_request_add_header(struct http_request *httpRequest, char *key, char *value) {
    httpRequest->requestHeaders[httpRequest->request_headers_number].key = key;
    httpRequest->requestHeaders[httpRequest->request_headers_number].value = value;
    httpRequest->request_headers_number++;
}

// get value
char *http_request_get_header(struct http_request *httpRequest, char *key) {
    if (httpRequest->requestHeaders != NULL) {
        for (int i = 0; i < httpRequest->request_headers_number; i++) {
            if (strncmp(httpRequest->requestHeaders[i].key, key, strlen(key)) == 0) {
                return httpRequest->requestHeaders[i].value;
            }
        }
    }
    return NULL;
}

// get  state
enum http_request_state http_request_current_state(struct http_request *httpRequest) {
    return httpRequest->current_state;
}

// if need close
int http_request_close_connection(struct http_request *httpRequest) {
    char *connection = http_request_get_header(httpRequest, "Connection");

    if (connection != NULL && strncmp(connection, CLOSE, strlen(CLOSE)) == 0) {
        return 1;
    }

    if (httpRequest->version != NULL &&
        strncmp(httpRequest->version, HTTP10, strlen(HTTP10)) == 0 &&
        strncmp(connection, KEEP_ALIVE, strlen(KEEP_ALIVE)) == 1) {
        return 1;
    }
    return 0;
}