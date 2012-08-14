/// @file package.h
/// @synopsis 二进制协议包
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-15

#ifndef __PACKAGE_H__
#define __PACKAGE_H__

struct _package_t
{
    /* data */
} /* optional variable list */;
typedef struct _package_t package_t;
typedef struct _package_t *package_p;

// --------------------------------------------------------------------------
/// @synopsis 从一个空字串创建一个package
///
/// @param package 创建的package
/// @param data 传入的空串
/// @param max_len 传入空串的最大长度，也是package的最大长度
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_create(package_p package, char *data, size_t max_len);

// --------------------------------------------------------------------------
/// @synopsis 从一个已有的数据包创建package
///
/// @param package 创建的package
/// @param data 传入的数据包
/// @param len 数据包的长度
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_create_from_data(package_p package, char *data, size_t len);

// --------------------------------------------------------------------------
/// @synopsis 从一个package的当前位置获取下一个64位数值字段
///
/// @param package 当前package
/// @param num 返回的64位数值
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_get_next_int16(package_p package, uint64_t *num);

// --------------------------------------------------------------------------
/// @synopsis 从一个package的当前位置获取下一个32位数值字段
///
/// @param package 当前package
/// @param num 返回的32位数值
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_get_next_int32(package_p package, uint32_t *num);

// --------------------------------------------------------------------------
/// @synopsis 从一个package的当前位置获取下一个16位数值字段
///
/// @param package 当前package
/// @param num 返回的16位数值
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_get_next_int16(package_p package, uint16_t *num);

// --------------------------------------------------------------------------
/// @synopsis 从一个package的当前位置获取下一个字符串字段
///
/// @param package 当前package
/// @param str 返回的字符串
/// @param len 返回的字符串长度
///
/// @returns 是否成功
// --------------------------------------------------------------------------
int32_t package_get_next_int16(package_p package, char **str, size_t len);

#endif /* end of include guard: __PACKAGE_H__ */

