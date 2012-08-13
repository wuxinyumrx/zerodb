/// @file bloom_filter.h
/// @synopsis bloom过滤器
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __BLOOM_FILTER_H__
#define __BLOOM_FILTER_H__

struct _bloom_filter_t
{
    /* data */
} /* optional variable list */;
typedef struct _bloom_filter_t bloom_filter_t;
typedef struct _bloom_filter_t *bloom_filter_p;

int32_t bloom_filter_create();

int32_t bloom_filter_destroy();

int32_t bloom_filter_add();

int32_t bloom_filter_check();

#endif /* end of include guard: __BLOOM_FILTER_H__ */

