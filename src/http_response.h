//
// Created by mycentos on 2020/4/2.
//

#ifndef TCPSERVER_HTTP_RESPONSE_H
#define TCPSERVER_HTTP_RESPONSE_H

#include "common.h"
#include "buffer.h"

struct response_header {
    char *key;
    char *value;
};

enum HttpStatusCode {
    Unknown,
    OK = 200,
    MovedPermanently = 301,
    BadRequest = 400,
    NotFound = 404,
};

struct http_response {
    enum HttpStatusCode statusCode;
    char *statusMessage;
    char *contentType;
    char *body;
    struct response_header *response_headers;
    int response_headers_number;
    int keep_connected;
};

struct http_response *http_response_new();

void http_response_encode_buffer(struct http_response *httpResponse, struct buffer *buffer);

#endif //TCPSERVER_HTTP_RESPONSE_H
