/// @file cache.h
/// @synopsis 缓存
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __CACHE_H__
#define __CACHE_H__

struct _cache_t
{
    /* data */
} /* optional variable list */;
typedef struct _cache_t cache_t;
typedef struct _cache_t *cache_p;

struct _slab_t
{
    /* data */
} /* optional variable list */;
typedef struct _slab_t slab_t;
typedef struct _slab_t *slab_p;

int32_t cache_create();

int32_t cache_destroy();

int32_t cache_get();

int32_t cache_set();

#endif /* end of include guard: __CACHE_H__ */

