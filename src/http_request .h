//
// Created by mycentos on 2020/4/2.
//

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "common.h"

struct request_header{
    char *key;
    char *value;
};

enum http_request_state{
    REQUEST_STATUS,    //等待解析状态行
    REQUEST_HEADERS,   //等待解析headers
    REQUEST_BODY,      //等待解析请求body
    REQUEST_DONE       //解析完成
};

struct http_request{
    char *version;
    char *method;
    char *url;
    enum http_request_state current_state;
    struct request_header *requestHeaders;
    int request_headers_number;
};

// init request
struct http_request *http_request_new();

// clear request
void http_request_clear(struct http_request *httpRequest);

// reset request
void http_request_reset(struct http_request *httpRequest);

// add header for request
void http_request_add_header(struct http_request *httpRequest,char *key,char *value);

// get header
char *http_request_get_header(struct http_request *httpRequest,char *key);

// get request current state
enum http_request_state http_request_current_state(struct http_request *httpRequest);

// if need close the connection
int http_request_close_connection(struct http_request *httpRequest);

#endif //HTTP_REQUEST_H
