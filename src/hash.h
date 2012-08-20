/// @file hash.h
/// @synopsis 哈希函数，为bloom filter、一致性hash提供支持
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __HASH_H__
#define __HASH_H__
#include <stdint.h>

typedef uint32_t (*str_hash_func_p)(char *key);
uint32_t SDBMHash(char *str);
uint32_t RSHash(char *str);
uint32_t JSHash(char *str);
uint32_t PJWHash(char *str);
uint32_t ELFHash(char *str);
uint32_t BKDRHash(char *str);
uint32_t DJBHash(char *str);
uint32_t APHash(char *str);

#endif
