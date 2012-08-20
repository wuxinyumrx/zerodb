/// @file key_slave_map.h

/// @synopsis key和slave的映射关系
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __KEY_SLAVE_MAP_H__
#define __KEY_SLAVE_MAP_H__
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../hash.h"
typedef struct _slave_t
{
    char *machine_id;
    size_t key_num;
}slave_t, *slave_p;
typedef struct _ring_entry
{
    slave_p slave_ptr;
    //[range_a, range_b)
    uint32_t range_a;
    uint32_t range_b;
    struct _ring_entry *next;
}ring_entry_t, *ring_entry_p;
typedef struct _key_slave_map_t
{
    /* data */
    ring_entry_p slave_list;
    size_t slave_num;
    str_hash_func_p key_map;   
}key_slave_map_t, *key_slave_map_p;
int32_t key_slave_map_create(key_slave_map_p *key_slave_map, str_hash_func_p str_hash_func);

int32_t key_slave_map_destroy();

int32_t key_slave_map_add(key_slave_map_p key_slave_map, char *machine_id);

int32_t key_slave_map_remove();

int32_t key_slave_map_get(key_slave_map_p key_slave_map, char *key, slave_p *slave);

int32_t key_slave_map_set(key_slave_map_p key_slave_map, char *key, char *value);
int32_t key_slave_map_store(key_slave_map_p key_slave_map, const char* file_name);

int32_t key_slave_map_load(key_slave_map_p *key_slave_map, const char* file_name);
#endif /* end of include guard: __KEY_SLAVE_MAP_H__ */

