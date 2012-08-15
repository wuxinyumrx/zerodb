/// @file key_slave_map.h
/// @synopsis key和slave的映射关系
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __KEY_SLAVE_MAP_H__
#define __KEY_SLAVE_MAP_H__

struct _key_slave_map_t
{
    /* data */
} /* optional variable list */;
typedef struct _key_slave_map_t key_slave_map_t;
typedef struct _key_slave_map_t *key_slave_map_p;

int32_t key_slave_map_create(key_slave_map_p *key_slave_map, );

int32_t key_slave_map_destroy();

int32_t key_slave_map_add();

int32_t key_slave_map_remove();

int32_t key_slave_map_get();

#endif /* end of include guard: __KEY_SLAVE_MAP_H__ */

