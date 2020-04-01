#include "channel_map.h"

int map_make_space(struct channel_map *map, int slot, int msize){
    if(map->nentries <= slot){
        int nentries = map->nentries ? map->nentries : 32;
        void **temp;

        while(nentries <= slot){
            nentries <<= 1;
        }

        temp = (void **) realloc(map->entries,nentries * msize);
        if(temp == NULL){
            return (-1);
        }

        memset(&temp[map->nentries],0,(nentries - map->nentries) * msize);

        map->nentries = nentries;
        map->entries = temp;
    }

    return (0);
}

void map_init(struct channel_map *map){
    map->entries = NULL;
    map->nentries = 0;
}

void map_clear(struct channel_map *map){
    if(map->entries != NULL){
        for(int i =0;i < map->nentries;i++){
            if(map->entries[i] != NULL){
                free(map->entries[i]);
            }
        }
        free(map->entries);
        map->entries = NULL;
    }
    map->nentries = 0;
}