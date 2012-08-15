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

// --------------------------------------------------------------------------
/// @synopsis 从字符串创建key
///
/// @param key 返回的key值
/// @param str 传入的字符串
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t key_create(key_p *key, char *str);

// --------------------------------------------------------------------------
/// @synopsis 比较两个key
///
/// @param left 第一个key
/// @param right 第二个key
///
/// @returns 比较结果，-1：left < right 0：left == right 1：left > right
// --------------------------------------------------------------------------
int32_t key_compare(key_p left, key_p right);

#endif /* end of include guard: __KEY_H__ */

