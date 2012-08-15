/// @file zerodb_slave_conf.h
/// @synopsis zerodb的slave端配置
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __ZERODB_SLAVE_CONF_H__
#define __ZERODB_SLAVE_CONF_H__

struct _zerodb_slave_conf_t
{
    /* data */
} /* optional variable list */;
typedef struct _zerodb_slave_conf_t zerodb_slave_conf_t;
typedef struct _zerodb_slave_conf_t *zerodb_slave_conf_p;

// --------------------------------------------------------------------------
/// @synopsis 载入zerodb工作端配置
///
/// @param zerodb_slave_conf zerodb工作端配置
/// @param zerodb_slave_conf_location 配置文件地址
///
/// @returns 
// --------------------------------------------------------------------------
int32_t zerodb_slave_conf_load(zerodb_slave_conf_p zerodb_slave_conf, char *zerodb_slave_conf_location);

// --------------------------------------------------------------------------
/// @synopsis 初始化工作端配置
///
/// @param zerodb_slave_conf zerodb工作端配置
///
/// @returns 
// --------------------------------------------------------------------------
int32_t zerodb_slave_conf_init(zerodb_slave_conf_p zerodb_slave_conf);

#endif /* end of include guard: __ZERODB_SLAVE_CONF_H__ */

