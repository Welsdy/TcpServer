//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_TCP_CONNECTION_H
#define TEST_TCP_CONNECTION_H

#include "event_loop.h"
#include "channel.h"
#include "tcp_server.h"
#include "buffer.h"
#include "utils.h"

struct tcp_connection
{
    struct event_loop *eventLoop;
    struct channel *channel;
    char *name;
    struct buffer *input_buffer;   //接收缓冲区
    struct buffer *output_buffer;  //发送缓冲区

    connection_completed_call_back connectionCompletedCallBack;
    message_call_back messageCallBack;
    write_completed_call_back writeCompletedCallBack;
    connection_closed_call_back connectionClosedCallBack;

    void * data; //for callback use: http_server
    void * request; // for callback use
    void * response; // for callback use
};

struct tcp_connection *
tcp_connection_new(int fd, struct event_loop *eventLoop, connection_completed_call_back connectionCompletedCallBack,
                   connection_closed_call_back connectionClosedCallBack,
                   message_call_back messageCallBack, write_completed_call_back writeCompletedCallBack);

int tcp_connection_send_data(struct tcp_connection *tcpConnection, void *data, int size);

int tcp_connection_send_buffer(struct tcp_connection *tcpConnection, struct buffer * buffer);

void tcp_connection_shutdown(struct tcp_connection * tcpConnection);

#endif //TEST_TCP_CONNECTION_H
