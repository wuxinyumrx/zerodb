/// @file key.h
/// @synopsis key值的相关操作
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __KEY_H__
#define __KEY_H__

struct _key_t
{
    /* data */
} /* optional variable list */;
typedef struct _key_t key_t;
typedef struct _key_t *key_p;

int32_t key_create();

int32_t key_compare();

#endif /* end of include guard: __KEY_H__ */

