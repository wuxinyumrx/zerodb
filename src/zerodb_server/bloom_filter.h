/// @file bloom_filter.h
/// @synopsis bloom过滤器
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __BLOOM_FILTER_H__
#define __BLOOM_FILTER_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#define nbytes(len) (len + 8 - 1)/8
#define set_bit_i(byte, i) byte |= 1<<(i) 
typedef uint32_t  (*hash_func)(const char *str);
typedef struct _bloom_filter_t
{
    /* data */
    unsigned char *bytes;
    size_t bit_length;
    size_t hash_func_num; 
    hash_func *hash_func_list;
}bloom_filter_t, *bloom_filter_p; 


// --------------------------------------------------------------------------
/// @synopsis 生成bloom过滤器
///
/// @param bloom_filter bloom过滤器
/// @param hash_funcs_num 传入的hash函数个数
/// @param ... hash_funcs_num个hash函数
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t bloom_filter_create(bloom_filter_p *bloom_filter, size_t vector_length, size_t hash_funcs_num, ...);

// --------------------------------------------------------------------------
/// @synopsis 销毁bloom过滤器
///
/// @param bloom_filter bloom过滤器
///
/// @returns 
// --------------------------------------------------------------------------
int32_t bloom_filter_destroy(bloom_filter_p *bloom_filter);

// --------------------------------------------------------------------------
/// @synopsis 将key值加入bloom过滤器
///
/// @param bloom_filter bloom过滤器
/// @param str 加入的key值字符串
/// @param len 加入的key值字符串长度
///
/// @returns 
// --------------------------------------------------------------------------
int32_t bloom_filter_add(bloom_filter_p bloom_filter, const char *str);

// --------------------------------------------------------------------------
/// @synopsis 判定
///
/// @param bloom_filter bloom过滤器
/// @param str 判定的key值字符串
/// @param len 判定的key值字符串长度
///
/// @returns 
// --------------------------------------------------------------------------
int32_t bloom_filter_check(bloom_filter_p bloom_filter, const char *str);

int32_t bloom_filter_store(bloom_filter_p bloom_filter, const char *file_name);
#endif /* end of include guard: __BLOOM_FILTER_H__ */

