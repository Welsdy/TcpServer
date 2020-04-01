//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_ACCEPTOR_H
#define TEST_ACCEPTOR_H

#include "common.h"

struct acceptor
{
    int listen_fd;
    int listen_port;
};

struct acceptor *acceptor_init(int port);

#endif //TEST_ACCEPTOR_H
