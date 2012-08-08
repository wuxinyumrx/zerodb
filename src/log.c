/// @file log.c
/// @synopsis 日志系统
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#ifndef __LOG_C__
#define __LOG_C__

#include "log.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

static pthread_mutex_t log_file_mutex;
static char *log_file_dir;
static char *log_file_name;
static char *program_name;

// --------------------------------------------------------------------------
/// @synopsis 将字符串输出到十六进制日志文件
///
/// @param format_data 格式化的目标字符串
/// @param bin_data 源二进制串
/// @param length 二进制串的长度
// --------------------------------------------------------------------------
void bin_data_format(char *format_data, unsigned char *bin_data, int32_t length)
{/*{{{*/
    int32_t i;
    int32_t prev;
    int32_t curr;
    int32_t pos = 0, ret = 0;
    
    ret = sprintf(format_data, "\t[length = %d]\n\t", length);
    pos = pos + ret;
    
    prev = curr = 0;
    for (i = 0; i < length; i++) {
        if (i == (prev + 16)) {
            i = prev;
            curr = prev + 16;
            
            strcpy(format_data + pos, "    |    ");
            pos = pos + 9;
            
            for(; i < curr; i++)
                if (isprint(bin_data[i])) {
                    ret = sprintf(format_data + pos,  "%c", bin_data[i]);
                    pos = pos + ret;
                }
                else {
                    strcpy(format_data + pos, " ");
                    pos = pos + 1;
                }
            
            strcpy(format_data + pos, "\n\t");
            pos = pos + 2;    
            prev = curr;
        }
        ret = sprintf(format_data + pos, "%02x ", bin_data[i]);
        pos = pos + ret;
    }
    
    if (i != curr) {
        curr = i;
        for (; i < (prev + 16); i++) {
            strcpy(format_data + pos, "   ");
            pos = pos + 3;
          }
        strcpy(format_data + pos, "    |    ");
        pos = pos + 9;
            
        for (i = prev ; i < curr; i++) {
            if (isprint(bin_data[i])) {
                ret = sprintf(format_data + pos,  "%c", bin_data[i]);
                pos = pos + ret;
            }
            else {
                strcpy(format_data + pos, " ");
                pos = pos + 1;
            }    
        }
    }
    strcpy(format_data + pos, "\n");
    pos = pos + 2;
}/*}}}*/

// --------------------------------------------------------------------------
/// @synopsis 日志
///
/// @param priority 优先级
/// @param filename 产生日志文件
/// @param line 产生日志的行号
/// @param length 二进制数据的长度 DUMP专用
/// @param bin_data 二进制数据
/// @param format 数据
/// @param ... 数据内含的参数
// --------------------------------------------------------------------------
void logit(int32_t priority, char *filename, int32_t line, int32_t length, char *bin_data, const char *format, ...)
{/*{{{*/
    pthread_t pthread_num = pthread_self();
    pid_t pid_num = getpid();

    static FILE *fp_log = NULL;
    static int32_t i_day = 0, i_hour = 0;
    char sz_buf[204800]={0},sz_date[30],sz_log_file[1024]={0}; 
    time_t t = time(NULL);
    struct tm tm; 
    va_list ap;

    va_start(ap, format);
    vsnprintf(sz_buf,sizeof(sz_buf)-1, format, ap);
    va_end(ap);
    if(bin_data != NULL && length != 0)
    {
        sz_buf[strlen(sz_buf)] = '\n';
        bin_data_format(sz_buf + strlen(sz_buf), (unsigned char *)bin_data, length);
    }
    localtime_r(&t,&tm);
    bzero(sz_date,sizeof(sz_date));
    strftime(sz_date, sizeof(sz_date) - 1, "%Y-%m-%d %H:%M:%S", &tm);

#ifdef DEBUG
    fp_log = stderr;
#else
    if (pthread_mutex_lock(&log_file_mutex)) 
    {
        fprintf(stderr, "LINE:%d pthread_mutex_lock() error !", __LINE__); 
    }
    if (i_day != tm.tm_mday || i_hour != tm.tm_hour) { // new hour, open a new file to write log
        if (fp_log){ // if file is open, close it
            fclose(fp_log);
            fp_log = NULL;
        }
        snprintf(sz_log_file, sizeof(sz_log_file), "%s/%s.%s.%04d-%02d-%02d.%02d", log_file_dir, program_name, log_file_name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour);
        i_day = tm.tm_mday;
        i_hour = tm.tm_hour;
    }
    if(fp_log == NULL) {
        if ((fp_log = fopen(sz_log_file, "a")) == NULL) {
            fprintf(stderr,"can't open log file --> [%s] \n", sz_log_file);
            fp_log=stderr;
        }
    }
#endif

    switch(priority) {
    case LOG_DEBUG:
        fprintf(fp_log, "[%s][%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n", sz_date, "DEBUG", filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;  
    case LOG_ERROR:
        fprintf(fp_log, "[%s][%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n", sz_date, "ERROR", filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;
    case LOG_INFO:
        fprintf(fp_log, "[%s][%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n", sz_date, "INFO", filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;
    case LOG_SQL:
        fprintf(fp_log, "[%s][%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n", sz_date, "EXEC SQL", filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;
    case LOG_STAT:
        fprintf(fp_log, "[%s][%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n",sz_date, "DUMP", filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;
    default :
        fprintf(fp_log, "[%s][FILE:%s LINE:%d][pid: %u][threadid: %lu] %s\n", sz_date, filename, line, pid_num, pthread_num, sz_buf);
        fflush(fp_log);
        break;
    }
#ifndef DEBUG
    if (pthread_mutex_unlock(&log_file_mutex)) {
        fprintf(stderr, "LINE:%d pthread_mutex_unlock() error !", __LINE__); 
    }
#endif
    return;

}/*}}}*/

// --------------------------------------------------------------------------
/// @synopsis 初始化日志系统
///
/// @param log_file_name 日志文件名的前缀
/// @param _program_name 生成日志的程序名
///
/// @returns 是否正确初始化
// --------------------------------------------------------------------------
int32_t log_init(char *_log_file_dir, char *_log_file_name, char *_program_name)
{/*{{{*/
    log_file_dir = _log_file_dir;
    log_file_name = _log_file_name;
    program_name = _program_name;
    if(pthread_mutex_init(&log_file_mutex, NULL) != 0)
    {
        return -1;
    }
    return 0;
}/*}}}*/

// --------------------------------------------------------------------------
/// @synopsis 退出日志系统
// --------------------------------------------------------------------------
void log_exit()
{/*{{{*/
    pthread_mutex_destroy(&log_file_mutex);
}/*}}}*/

#endif
