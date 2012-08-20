/// @file zerodb_server.c
/// @synopsis zerodb的server端
/// @author Xinyu Woo <wuxinyumrx@gmail.com>
/// @version 1.0
/// @date 2012-08-08
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "key_slave_map.h"
#include "bloom_filter.h"
#include "../hash.h"
typedef int32_t (*action)(size_t, char**);
typedef struct _command_t
{
    char command_name[20];
    action command_action;
}command_t, *command_p;

key_slave_map_p key_slave_map_g = NULL;
bloom_filter_p bloom_filter_g = NULL;

int is_key_in(char *file_path, char *key)
{
    FILE *fp = fopen(file_path, "rt");
    char str[100];
    while(fscanf(fp, "%s", str) != EOF)
    {
	if(strcmp(str, key) == 0)
	    return 1;
    }
    return 0;
}
void bloom_filter_test()
{
    FILE *keys_file = fopen("keys.data", "rt");
    FILE *test_file = fopen("test.data", "rt");
    char key[100];
    while(fscanf(keys_file, "%s", key) != EOF)
    {
        bloom_filter_add(bloom_filter_g, key);
    }
    fclose(keys_file);
    //bloom_filter_print_01(bloom_filter_g);
    bloom_filter_store(bloom_filter_g, "bloom_filter.data");
    
    int keys_num=0, mistake_num=0;
    while(fscanf(test_file, "%s", key) != EOF)
    {
	int re = bloom_filter_check(bloom_filter_g, key);
	char msg[20];
	
 	if(is_key_in("keys.data", key))
	{
	    if(re == 0)
		strcpy(msg, "error");
	    else
		strcpy(msg, "right");
	}
	else
	{
	    if(re == 0)
		strcpy(msg, "right");
	    else
	    {
		strcpy(msg, "mistake");
		mistake_num++;
	    }
	}
	keys_num++;
        printf("key:%s	result:%s\n", key, msg);
    }
    printf("total keys:%d, mistakes;%d", keys_num, mistake_num);
}
int32_t key_set(size_t argc, char **argv)
{
    bloom_filter_add(bloom_filter_g, argv[0]);
    bloom_filter_store(bloom_filter_g, "bloom_filter.data");
    key_slave_map_set(key_slave_map_g, argv[0], argv[1]);
    key_slave_map_store(key_slave_map_g, "key_slave_map.data");
}

int32_t key_get(size_t argc, char **argv)
{
    slave_p slave = NULL;
   
    if(bloom_filter_check(bloom_filter_g, argv[0]) == 0)
    {
        printf("key not exist!");
        return -1;
    } 
    key_slave_map_get(key_slave_map_g, argv[0], &slave);

    printf("%s\n", slave->machine_id);
}


int32_t slave_register(size_t argc, char **argv)
{
    key_slave_map_add(key_slave_map_g, argv[0]);
    key_slave_map_store(key_slave_map_g, "key_slave_map.data");    
}

command_t commands[] = {
    {"add", slave_register},
    {"set", key_set},
    {"get", key_get}
};

int32_t command_interprete(char *command_str)
{
    assert(command_str != NULL);
    char *token = strtok(command_str, " ");
    int i;
    for(i=0; i<sizeof(commands)/sizeof(command_t); i++)
    {
        if(strcmp(commands[i].command_name, token) == 0)
        {
	    size_t argc = 0;
	    char **argv = (char**)malloc(10*sizeof(char*));
	    while(token = strtok(NULL, " "))
	    {
    		*(argv+argc) = token;
	        argc++;
		
  	    }
	    return commands[i].command_action(argc, argv);
	}

    }
    return -1;    
}
int32_t main()
{
    bloom_filter_create(&bloom_filter_g, 32, 4, SDBMHash, RSHash, JSHash, PJWHash);
    key_slave_map_create(&key_slave_map_g, RSHash);
    char line[100];
    //bloom_filter_test();
    while(gets(line))
    {
        command_interprete(line);
    }
    
    return 0;
}
