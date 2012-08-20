#include "key_slave_map.h"

int32_t key_slave_map_create(key_slave_map_p *key_slave_map, str_hash_func_p str_hash_func)
{
    key_slave_map_p new_map  = (key_slave_map_t*)malloc(sizeof(key_slave_map_t));
    if(new_map == NULL)
        return -1;
    new_map->slave_list = NULL;
    new_map->slave_num = 0;
    new_map->key_map = str_hash_func;
    *key_slave_map = new_map;
    return 1;
}

int32_t key_slave_map_add(key_slave_map_p key_slave_map, char *machine_id)
{
    assert(key_slave_map != NULL);
    int i,max_key_num=0;
    ring_entry_p insert_position,ring_iterator;
    insert_position = ring_iterator = key_slave_map->slave_list; 
    for(i=0; i<key_slave_map->slave_num; i++)
    {
	if(strcmp(machine_id, ring_iterator->slave_ptr->machine_id) == 0)
	    return -1;
        if(ring_iterator->slave_ptr->key_num > max_key_num)
	{
	    insert_position = ring_iterator;
	    max_key_num = ring_iterator->slave_ptr->key_num;
	}
	ring_iterator = ring_iterator->next;
    }
    uint32_t a,b;

    ring_entry_p new_entry = (ring_entry_t*)malloc(sizeof(ring_entry_t));
    if(new_entry == NULL)
        return -1;
    slave_p new_slave = (slave_t*)malloc(sizeof(slave_t));
    if(new_slave == NULL)
	return -1;
    new_slave->machine_id = (char*)malloc(strlen(machine_id) + 1);
    strcpy(new_slave->machine_id, machine_id);
    new_slave->key_num = 0;
    new_entry->slave_ptr = new_slave;
    //first slave
    if(insert_position == NULL)
    {
	new_entry->range_a = 0;
	new_entry->range_b = (1<<32) - 1;
	new_entry->next = NULL;
	key_slave_map->slave_list = new_entry;
	key_slave_map->slave_num++;
	return 1; 	
    }
    else
    {
        a = insert_position->range_a, b = insert_position->range_b;
    	insert_position->range_b = (a+b)/2;
    	new_entry->range_a = (a+b)/2;
    	new_entry->range_b = b;
	new_entry->next = insert_position->next;
	insert_position->next = new_entry;
	key_slave_map->slave_num++;
	/*data migration*/
	return 1;
    }   
}

int32_t key_slave_map_get(key_slave_map_p key_slave_map, char *key, slave_p *slave)
{
    assert(key != NULL);
    assert(key_slave_map != NULL);
    int32_t value =  key_slave_map->key_map(key);
    ring_entry_p ring_iterator = key_slave_map->slave_list;
    int i;
    for(i=0; i < key_slave_map->slave_num; i++)
    {
        if(ring_iterator->range_a <= value && value < ring_iterator->range_b)
	{
	    *slave = ring_iterator->slave_ptr;
	    return 1;
	}
	ring_iterator = ring_iterator->next;
    }
    return -1;
}


int32_t key_slave_map_set(key_slave_map_p key_slave_map, char *key, char *value)
{
    assert(key_slave_map != NULL);
    slave_p slave = NULL;
    key_slave_map_get(key_slave_map, key, &slave);
    slave->key_num++;
    FILE *fp = fopen(slave->machine_id, "a+");
    fprintf(fp,"%s %s\n", key, value);
    fclose(fp);
}
int32_t key_slave_map_store(key_slave_map_p key_slave_map, const char* file_name)
{
    assert(key_slave_map != NULL);

    FILE *fp = fopen(file_name, "w+");
    if(fp == NULL)
        return -1;
    fprintf(fp, "slaves number :%u\n", key_slave_map->slave_num);
    ring_entry_p slave_iterator = key_slave_map->slave_list;
    int i;
    fprintf(fp,"%s %s %s %s\n", "left_range","right_range","slave","key_num");
    for(i=0; i<key_slave_map->slave_num; i++)
    {
        fprintf(fp, "%u %u %s %u\n", slave_iterator->range_a, slave_iterator->range_b, slave_iterator->slave_ptr->machine_id, slave_iterator->slave_ptr->key_num);
	slave_iterator = slave_iterator->next;
    }
    fclose(fp);
    return 1;
}
