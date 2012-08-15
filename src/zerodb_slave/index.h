/// @file index.h
/// @synopsis 索引
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __INDEX_H__
#define __INDEX_H__

struct _index_t
{
    /* data */
} /* optional variable list */;
typedef struct _index_t index_t;
typedef struct _index_t *index_p;

int32_t index_create();

int32_t index_destroy();

int32_t index_set();

int32_t index_del();

int32_t index_get();

#endif /* end of include guard: __INDEX_H__ */

