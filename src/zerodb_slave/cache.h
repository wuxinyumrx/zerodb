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

// --------------------------------------------------------------------------
/// @synopsis 创建缓存区
///
/// @param cache 缓存区
/// @param capacity 最大容量
/// @param slab_num 分区个数
/// @param min_slab_size 最小slab的大小
/// @param ratio 增长比
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t cache_create(cache_p *cache, uint32_t capacity, uint32_t slab_num, uint32_t min_slab_size, float ratio);

// --------------------------------------------------------------------------
/// @synopsis 销毁缓存区
///
/// @param cache 缓存区
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t cache_destroy(cache_p *cache);

// --------------------------------------------------------------------------
/// @synopsis 给定key获取缓存区的value
///
/// @param cache 缓存区
/// @param record in 带有key的信息 out 带有key和value信息
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t cache_get(cache_p cache, record_p record);

// --------------------------------------------------------------------------
/// @synopsis 将record存入缓存区
///
/// @param cache 缓存区
/// @param record 数据记录
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t cache_set(cache_p cache, record_p record);

#endif /* end of include guard: __CACHE_H__ */

