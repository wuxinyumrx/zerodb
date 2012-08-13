/// @file record.h
/// @synopsis 缓存和持久化记录
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __RECORD_H__
#define __RECORD_H__

struct _record_t
{
    /* data */
} /* optional variable list */;
typedef struct _record_t record_t;
typedef struct _record_t *record_p;

int32_t record_create();

int32_t record_destroy();

#endif /* end of include guard: __RECORD_H__ */

