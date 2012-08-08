/// @file log.h
/// @synopsis 日志系统
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __LOG_H__
#define __LOG_H__

#define LOG_LEVEL  1
#define LOG_DEBUG  1
#define LOG_STAT   2
#define LOG_SQL    3
#define LOG_INFO   4
#define LOG_ERROR  5
#define LOG(log_type, format, length, bin_data, ...) if(log_type >= LOG_LEVEL){logit(log_type, __FILE__, __LINE__, length, bin_data, format, ##__VA_ARGS__);}
#define LOG_WITH_ARGU(log_type, file, line, format, length, bin_data, ...) if(log_type >= LOG_LEVEL){logit(log_type, file, line, length, bin_data, format, ##__VA_ARGS__);}

#include <stdint.h>


// --------------------------------------------------------------------------
/// @synopsis 初始化日志系统
///
/// @param log_file_name 日志文件名的前缀
/// @param _program_name 生成日志的程序名
///
/// @returns 是否正确初始化
// --------------------------------------------------------------------------
int32_t log_init(char *_log_file_dir, char *_log_file_name, char *_program_name);

// --------------------------------------------------------------------------
/// @synopsis 退出日志系统
///
/// @returns 是否正确退出
// --------------------------------------------------------------------------
void log_exit();

// --------------------------------------------------------------------------
/// @synopsis 日志
///
/// @param priority 优先级
/// @param filename 产生日志文件
/// @param line 产生日志的行号
/// @param format 格式化
/// @param ... 格式化的参数
// --------------------------------------------------------------------------
void logit(int32_t priority, char *filename, int32_t line, int32_t length, char *bin_data, const char *format, ...);

#endif
