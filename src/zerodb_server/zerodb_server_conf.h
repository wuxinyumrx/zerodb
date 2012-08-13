/// @file zerodb_server_conf.h
/// @synopsis zerodb的服务端配置
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __ZERODB_SERVER_CONF_H__
#define __ZERODB_SERVER_CONF_H__

#include <json/json-c.h>

struct _zerodb_server_conf_t
{
    /* data */
} /* optional variable list */;
typedef struct _zerodb_server_conf_t zerodb_server_conf_t;
typedef struct _zerodb_server_conf_t *zerodb_server_conf_p;

int32_t zerodb_server_conf_load();

int32_t zerodb_server_conf_init();

#endif /* end of include guard: __ZERODB_SERVER_CONF_H__ */

