/// @file persistent.h
/// @synopsis 持久化
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __PERSISTENT_H__
#define __PERSISTENT_H__

struct _persistent_t
{
    /* data */
} /* optional variable list */;
typedef struct _persistent_t persistent_t;
typedef struct _persistent_t *persistent_p;

int32_t persistent_load();

int32_t persistent_merge();

int32_t persistent_set();

int32_t persistent_get();

int32_t persistent_del();

#endif /* end of include guard: __PERSISTENT_H__ */

