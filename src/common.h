//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h> 
#include <sys/uio.h> 
#include <sys/wait.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <assert.h>

#define    SERV_PORT      12345
#define    MAXLINE        4096
#define    LISTENQ        1024

#endif //TEST_COMMON_H
