#include "mapde.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

/**
 * @brief Get the hash value of the given str.
 */
uint32_t mapde_hash(uint32_t code) {
    return code % MAP_SIZE;
}

Map mapde_create() {
    Map map = calloc(1, sizeof(struct _map));
    short i;
    Str str = str_create(1);
    for (i = 0; i <= UCHAR_MAX; i++) {
        str_empty(str);
        str_append(str, (char)i);
        mapde_add_str(map, str);
    }
    /* Skip 2 values corresponding to CLEAR_CODE and END_CODE */
    map->next_code += 2;
    str_free(str);
    return map;
}

Str mapde_get_str(Map map, uint32_t code) {
    uint32_t hash = mapde_hash(code);
    //printf("aaaa\n");
    //printf("hash=%u\n", hash);
    Link link = map->data[hash];
    for (link = map->data[hash]; link != NULL; link = link->next) {
        if (link->code == code) {
            /* String found */
            return link->str;
        }
    }
    /* Code not found */
    return NULL;
}

void mapde_add_str(Map map, const Str str) {
    uint32_t hash = mapde_hash(map->next_code);
    Link link = link_create(str, map->next_code++, map->data[hash]);
    map->data[hash] = link;
}