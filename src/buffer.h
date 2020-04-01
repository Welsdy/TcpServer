//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_BUFFER_H
#define TEST_BUFFER_H

#include "common.h"

#define INIT_BUFFER_SIZE 65536

struct buffer
{
    char *data; //实际缓冲
    int readIndex; //缓冲读取位置
    int writeIndex; //缓冲写入位置
    int total_size; //总大小
};

struct buffer *buffer_new();

void buffer_free(struct buffer *buffer);

/********** get size  *********/

int buffer_writeable_size(struct buffer *buffer);

int buffer_readable_size(struct buffer *buffer);

int buffer_front_spare_size(struct buffer *buffer);

/********* write data ***************/

int buffer_append(struct buffer *buffer, void *data, int size);

int buffer_append_char(struct buffer *buffer, char data);

int buffer_append_string(struct buffer*buffer, char * data);

/********* read data **************/

int buffer_socket_read(struct buffer *buffer, int fd);

char buffer_read_char(struct buffer *buffer);


char * buffer_find_CRLF(struct buffer * buffer);

#endif //TEST_BUFFER_H
