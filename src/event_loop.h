//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_EVENT_LOOP_H
#define TEST_EVENT_LOOP_H

#include "channel.h"
#include "channel_map.h"
#include "event_dispatcher.h"
#include "common.h"


extern const struct event_dispatcher epoll_dispatcher;

struct channel_element
{
    int type;
    struct channel *channel;
    struct channel_element *next; 
};


struct event_loop
{
    int quit;
    const struct event_dispatcher *eventDispatcher;

    // dispather data
    void *event_dispatcher_data;
    struct channel_map *channelMap;

    int is_handle_pending;
    struct channel_element *pending_head;
    struct channel_element *pending_tail;

    pthread_t owner_thread_id;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int socketPair[2];
    char *thread_name;
};

struct event_loop *event_loop_init();

struct event_loop *event_loop_init_with_name(char * thread_name);

int event_loop_run(struct event_loop *eventLoop);

void event_loop_wakeup(struct event_loop *eventLoop);

// add remove update channel
int event_loop_add_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_remove_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_update_channel_event(struct event_loop *eventLoop, int fd, struct channel *channel1);

int event_loop_handle_pending_add(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_remove(struct event_loop *eventLoop, int fd, struct channel *channel);

int event_loop_handle_pending_update(struct event_loop *eventLoop, int fd, struct channel *channel);

// dispather派发完事件之后，调用该方法通知event_loop执行对应事件的相关callback方法
// res: EVENT_READ | EVENT_READ等
int channel_event_activate(struct event_loop *eventLoop, int fd, int res);

#endif //TEST_EVENT_LOOP_H
