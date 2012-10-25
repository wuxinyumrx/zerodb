/// @file hash.h
/// @synopsis 哈希函数，为bloom filter、一致性hash提供支持
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __HASH_H__
#define __HASH_H__
#include <stdint.h>

typedef uint32_t (*str_hash_func_p)(char *key);

uint32_t sdbm_hash(char *str);

uint32_t rs_hash(char *str);

uint32_t js_hash(char *str);

uint32_t pjw_hash(char *str);

uint32_t elf_hash(char *str);

uint32_t bkdr_hash(char *str);

uint32_t djb_hash(char *str);

uint32_t ap_hash(char *str);

#endif
