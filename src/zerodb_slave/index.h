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

// --------------------------------------------------------------------------
/// @synopsis 创建索引
///
/// @param index 索引
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_create(index_p *index);

// --------------------------------------------------------------------------
/// @synopsis 销毁索引
///
/// @param index 索引
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_destroy(index_p *index);

// --------------------------------------------------------------------------
/// @synopsis 索引update或add，同时会调用cache和persistent相关函数
///
/// @param index 索引
/// @param record 数据记录
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_set(index_p index, record_p record);

// --------------------------------------------------------------------------
/// @synopsis 索引delete，同时会调用cache和persistent相关函数
///
/// @param index 索引
/// @param record 数据记录，仅包含key的信息
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_del(index_p index, record_p record);

// --------------------------------------------------------------------------
/// @synopsis 索引get，同时会调用cache和persistent相关函数
///
/// @param index 索引
/// @param record in 带有key的信息 out带有key和value信息
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_get(index_p index, record_p record);

// --------------------------------------------------------------------------
/// @synopsis index和persistent协作merge持久化文件
///
/// @param index 索引
///
/// @returns 是否正确
// --------------------------------------------------------------------------
int32_t index_merge(index_p index);

#endif /* end of include guard: __INDEX_H__ */

