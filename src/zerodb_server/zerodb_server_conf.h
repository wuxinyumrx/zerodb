/// @file zerodb_server_conf.h
/// @synopsis zerodb的服务端配置
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __ZERODB_SERVER_CONF_H__
#define __ZERODB_SERVER_CONF_H__

#include <json/json-c.h>

#define ZERODB_SERVER_CONF_LOCATION "./"

struct _zerodb_server_conf_t
{
    /* data */
} /* optional variable list */;
typedef struct _zerodb_server_conf_t zerodb_server_conf_t;
typedef struct _zerodb_server_conf_t *zerodb_server_conf_p;

// --------------------------------------------------------------------------
/// @synopsis 载入zerodb服务端配置
///
/// @param zerodb_server_conf zerodb服务端配置
///
/// @returns 
// --------------------------------------------------------------------------
int32_t zerodb_server_conf_load(zerodb_server_conf_p zerodb_server_conf);

// --------------------------------------------------------------------------
/// @synopsis 初始化zerodb服务端配置
///
/// @param zerodb_server_conf zerodb服务端配置
///
/// @returns 
// --------------------------------------------------------------------------
int32_t zerodb_server_conf_init(zerodb_server_conf_p zerodb_server_conf);

#endif /* end of include guard: __ZERODB_SERVER_CONF_H__ */

