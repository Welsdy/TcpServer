#include "src/acceptor.h"
#include "src/event_loop.h"
#include "src/tcp_server.h"
#include "src/tcp_connection.h"
#include "src/common.h"

char rot13_char(char c){
    if((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M')){
        c += 13;
    }else if((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z')){
        c -= 13;
    }

    return c;
}

//连接建立之后的callback
int onConnectionCompleted(struct tcp_connection *tcpConnection){
    printf("connection completed\n");
    return 0;
}

//数据读到buffer之后的callback
int onMessage(struct buffer *input, struct tcp_connection *tcpConnection){
    printf("get message from tcp connection %s\n", tcpConnection->name);
    printf("Message: %s\n", input->data);

    struct buffer *output = buffer_new();
    int size = buffer_readable_size(input);
    for(int i = 0;i < size;i++){
        buffer_append_char(output,rot13_char(buffer_read_char(input)));
    }

    tcp_connection_send_buffer(tcpConnection,output);
    return 0;
}

//数据通过buffer写完之后的callback
int onWriteCompleted(struct tcp_connection *tcpConnection){
    printf("write completed\n");
    return 0;
}

//连接关闭之后的callback
int onConnectionClosed(struct tcp_connection *tcpConnection){
    printf("connection closed\n");
    return 0;
}

int main(int argc,char **argv){
    //主线程event_loop
    struct event_loop *eventLoop = event_loop_init();

    //初始化acceptor
    struct acceptor *acceptor = acceptor_init(SERV_PORT);

    //初始tcp_server，可以指定线程数目，这里线程是4，说明是一个acceptor线程，4个I/O线程，每一个I/O线程
    //tcp_server自己带一个event_loop
    struct TCPserver *tcpServer = tcp_server_init(eventLoop,acceptor,onConnectionCompleted,onMessage,
                                                    onWriteCompleted,onConnectionClosed,4);

    tcp_server_start(tcpServer);

    // main thread for acceptor
    event_loop_run(eventLoop);
}