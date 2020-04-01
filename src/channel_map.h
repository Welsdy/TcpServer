//
// Created by mycentos on 2020/3/31.
//

#ifndef TEST_CHANNEL_MAP_H
#define TEST_CHANNEL_MAP_H

#include "channel.h"

struct channel_map
{
    void **entries;

    int nentries;
};

int map_make_space(struct channel_map *map, int slot, int msize);

void map_init(struct channel_map *map);

void map_clear(struct channel_map *map);

#endif //TEST_CHANNEL_MAP_H
