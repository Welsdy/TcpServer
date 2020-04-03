//
// Created by mycentos on 2020/4/2.
//

#include "http_server.h"

int http_onConnectionCompleted(struct tcp_connection *tcpConnection);

int http_onMessage(struct buffer *input,struct tcp_connection *tcpConnection);

int http_onWriteCompleted(struct tcp_connection *tcpConnection);

int http_onConnectionClosed(struct tcp_connection *tcpConnection);

int process_status_line(char *start, char *end, struct http_request *httpRequest);

struct http_server *http_server_new(struct event_loop *eventLoop, int port,request_callback requestCallback,int threadNum){
    struct http_server *httpSever = malloc(sizeof(struct http_server));
    httpSever->requestCallback = requestCallback;

    // init acceptor
    struct acceptor *acceptor = acceptor_init(SERV_PORT);

    httpSever->tcpServer = tcp_server_init(eventLoop,acceptor,http_onConnectionCompleted, http_onMessage,http_onWriteCompleted,
                                           http_onConnectionClosed,threadNum);

    // set callback data
    httpSever->tcpServer->data = httpSever;

    return httpSever;
}

void http_server_start(struct http_server *httpServer){
    tcp_server_start(httpServer->tcpServer);
}
/*********http server callback***************/

//连接建立之后的callback
int http_onConnectionCompleted(struct tcp_connection *tcpConnection){
    printf("connection completed \n");
    struct http_request *httpRequest = http_request_new();
    tcpConnection->request = httpRequest;
    return 0;
}

// buffer是框架构建好的，并且已经收到部分数据的情况下
// 注意这里可能没有收到全部数据，所以要处理数据不够的情形
int http_onMessage(struct buffer *input,struct tcp_connection *tcpConnection){
    printf("get message from tcp connection %s \n",tcpConnection->name);

    struct http_request *httpRequest = (struct http_request *) tcpConnection->request;
    struct http_server *httpServer = (struct http_server *) tcpConnection->data;

    if(parse_http_request(input,httpRequest) == 0){
        char *error_response = "HTTP/1.1 400 Bad Request\r\n\r\n";
        tcp_connection_send_data(tcpConnection,error_response, sizeof(error_response));
        tcp_connection_shutdown(tcpConnection);
    }

    //处理完了所有的request数据，接下来进行编码和发送
    if(httpRequest->current_state == REQUEST_DONE){
        struct http_response *httpResponse = http_response_new();

        //httpServer requestCallback回调
        if (httpServer->requestCallback != NULL) {
            httpServer->requestCallback(httpRequest, httpResponse);
        }

        struct buffer *buffer = buffer_new();
        http_response_encode_buffer(httpResponse, buffer);
        tcp_connection_send_buffer(tcpConnection, buffer);

        if (http_request_close_connection(httpRequest)) {
            tcp_connection_shutdown(tcpConnection);
        }
        http_request_reset(httpRequest);
    }
}

//数据通过buffer写完之后的callback
int http_onWriteCompleted(struct tcp_connection *tcpConnection) {
    printf("write completed \n");
    return 0;
}

//连接关闭之后的callback
int http_onConnectionClosed(struct tcp_connection *tcpConnection) {
    printf("connection closed \n");
    if (tcpConnection->request != NULL) {
        http_request_clear(tcpConnection->request);
        tcpConnection->request = NULL;
    }
    return 0;
}
/******** parse http request  ***************/

int parse_http_request(struct buffer *input,struct http_request *httpRequest){

    while(httpRequest->current_state != REQUEST_DONE){
        if(httpRequest->current_state == REQUEST_STATUS){
            char *crlf = buffer_find_CRLF(input);

            if(crlf){
                int request_line_size = process_status_line(input->data + input->readIndex,crlf,httpRequest);
                if(request_line_size){
                    input->readIndex += request_line_size;
                    input->readIndex += 2;// crlf
                    httpRequest->current_state = REQUEST_HEADERS;
                }
            }
        }else if(httpRequest->current_state == REQUEST_HEADERS){
            char *crlf = buffer_find_CRLF(input);

            if(crlf){
                /* start---------- : ------- crlf */

                char *start = input->data + input->readIndex;
                int request_line_size = crlf - start;
                char *colon = memmem(start,request_line_size,": ",2);
                if(colon != NULL){
                    char *key = malloc(colon - start + 1);
                    strncpy(key,start,colon - start);
                    key[colon - start] = '\0';

                    char *value = malloc(crlf - colon + 1 - 2);
                    strncpy(value,colon + 2,crlf - colon - 2);
                    value[crlf - colon - 2] = '\0';

                    http_request_add_header(httpRequest,key,value);

                    input->readIndex += request_line_size;
                    input->readIndex += 2;// crlf
                }else {
                    // end
                    input->readIndex += 2;
                    httpRequest->current_state = REQUEST_DONE;
                }
            }
        }
    }

    return 1;
}

int process_status_line(char *start,char *end,struct http_request *httpRequest){
    int status_line_size = end - start;

    // get method
    char *space = memmem(start,end - start," ",1);
    assert(space != NULL);

    int method_size = space - start;
    httpRequest->method = malloc(method_size + 1);
    strncpy(httpRequest->method,start,method_size);
    httpRequest->method[method_size + 1] = '\0';

    // get url
    start = space + 1;
    space = memmem(start,end - start," ",1);
    assert(space != NULL);

    int url_size = space - start;
    httpRequest->url = malloc(url_size + 1);
    strncpy(httpRequest->url,start,url_size);
    httpRequest->url[url_size + 1] = '\0';

    // get version
    start = space + 1;
    httpRequest->version = malloc(end - start + 1);
    strncpy(httpRequest->version,start,end - start);
    httpRequest->version[end - start + 1] = '\0';

    assert(space != NULL);
    return status_line_size;
}


