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

// --------------------------------------------------------------------------
/// @synopsis 创建持久化管理器
///
/// @param persistent 持久化管理器
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t persistent_new(persistent_p persistent);

// --------------------------------------------------------------------------
/// @synopsis 创建持久化管理器，并且载入原有配置
///
/// @param persistent 持久化管理器
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t persistent_load(persistent_p persistent);

// --------------------------------------------------------------------------
/// @synopsis 持久化管理器merge操作
///
/// @param persistent 持久化管理器
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t persistent_merge(persistent_p persistent);

// --------------------------------------------------------------------------
/// @synopsis 持久化管理器append (update和add) 的操作记录
///
/// @param persistent 持久化管理器
/// @param record 数据记录
/// @param file_num 返回的文件号
/// @param file_offset 返回的文件偏移
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t persistent_set(persistent_p persistent, record_p record, uint32_t *file_num, uint32_t *file_offset);

// --------------------------------------------------------------------------
/// @synopsis 持久化管理器读取对应的数据条目
///
/// @param persistent 持久化管理器
/// @param record 数据记录 in 带有验证信息 out 完整的数据记录
/// @param file_num 文件号
/// @param file_offset 文件偏移量
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t persistent_get(persistent_p persistent, record_p record, uint32_t file_num, uint32_t file_offset);

// --------------------------------------------------------------------------
/// @synopsis 持久化管理器append (delete) 的操作记录
///
/// @param persistent 持久化管理器
/// @param record 数据条目，仅含有key的信息
///
/// @returns 
// --------------------------------------------------------------------------
int32_t persistent_del(persistent_p persistent, record_p record);

#endif /* end of include guard: __PERSISTENT_H__ */

