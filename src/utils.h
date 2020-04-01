//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "event_loop.h"

void assertInSameThread(struct event_loop *eventLoop);

//1： same thread: 0： not the same thread
int isInSameThread(struct event_loop *eventLoop);

#endif //TEST_UTILS_H
