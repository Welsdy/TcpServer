//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_CHANNEL_H
#define TEST_CHANNEL_H

#include "event_loop.h"
#include "buffer.h"
#include "common.h"

#define EVENT_TIMEOUT    0x01
/** Wait for a socket or FD to become readable */
#define EVENT_READ        0x02
/** Wait for a socket or FD to become writeable */
#define EVENT_WRITE    0x04
/** Wait for a POSIX signal to be raised*/
#define EVENT_SIGNAL    0x08

typedef int (*event_read_callback)(void *data);

typedef int (*event_write_callback)(void *data);

struct channel
{
    int fd;
    int events;

    event_read_callback eventReadCallback;
    event_write_callback eventWriteCallback;

    void *data;
};

struct channel *channel_new(int fd,int events,
                            event_read_callback eventReadCallback,event_write_callback eventWriteCallback,
                            void *data);

int channel_write_event_is_enabled(struct channel *channel);

int channel_write_event_enable(struct channel *channel);

int channel_write_event_disable(struct channel *channel);

#endif //TEST_CHANNEL_H
