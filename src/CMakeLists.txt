cmake_minimum_required(VERSION 3.15)
project(test C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

aux_source_directory(. DIR_SRCS)

add_executable(test ${DIR_SRCS} channel.c channel.h acceptor.c acceptor.h buffer.c buffer.h channel_map.c channel_map.h event_loop.c event_loop.h epoll_dispatcher.c event_loop_thread.c event_loop_thread.h thread_pool.c thread_pool.h tcp_connection.c tcp_connection.h tcp_server.c tcp_server.h common.h utils.c utils.h event_dispatcher.h)
