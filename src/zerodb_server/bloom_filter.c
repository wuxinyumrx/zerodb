#include "bloom_filter.h"

int32_t bloom_filter_create(bloom_filter_p *bloom_filter, size_t vector_length, size_t hash_func_num, ...)
{
    bloom_filter_p new_bf = (bloom_filter_t*)malloc(sizeof(bloom_filter_t)); 
    if(new_bf == NULL)
        return -1;
    new_bf->bit_length = vector_length;
    new_bf->bytes = (unsigned char*)malloc(nbytes(vector_length));
    if(new_bf->bytes == NULL)
	return -1;
    memset(new_bf->bytes, nbytes(vector_length), 0);
    new_bf->hash_func_num = hash_func_num;
    new_bf->hash_func_list = (hash_func*)malloc(hash_func_num * sizeof(hash_func));
    va_list ap;
    va_start(ap, hash_func_num);
    int i;
    hash_func hash_func_i;
    for(i=0; i<hash_func_num; i++)
    {
        hash_func_i = va_arg(ap, hash_func);
	*(new_bf->hash_func_list + i) = hash_func_i;
    }
    va_end(ap); 
    *bloom_filter = new_bf;
    return 1;
}

int32_t bloom_filter_add(bloom_filter_p bloom_filter, const char *str)
{
    assert(bloom_filter != NULL);
    int i,value;
    hash_func hash_func_i;
    for(i=0; i<bloom_filter->hash_func_num; i++)
    {
        hash_func_i = *(bloom_filter->hash_func_list + i);
        value = hash_func_i(str) % bloom_filter->bit_length;
 	unsigned char *byte = bloom_filter->bytes + value/8;
       	set_bit_i(*byte, 7 - value%8);	
    }    
    return 1;

}

int32_t bloom_filter_check(bloom_filter_p bloom_filter, const char *str)
{
    assert(bloom_filter != NULL);
    int i,value;
    hash_func hash_func_i;
    for(i=0; i<bloom_filter->hash_func_num; i++)
    {
        hash_func_i = *(bloom_filter->hash_func_list + i);
	value = hash_func_i(str) % bloom_filter->bit_length;
	unsigned char byte = *(bloom_filter->bytes + value/8);
	if((byte << value%8 & 0x80) == 0)
	    return 0;
    }
    return 1;
}


int32_t bloom_filter_store(bloom_filter_p bloom_filter, const char *file_name)
{
    assert(bloom_filter != NULL); 
    FILE *fp = fopen(file_name, "w+");
    
    fprintf(fp, "bit_length %u\n", bloom_filter->bit_length);
    fprintf(fp, "hash_func_num %u\n", bloom_filter->hash_func_num);

    int i;
    fprintf(fp, "bytes:\n");
    for(i=0; i<nbytes(bloom_filter->bit_length); i++)
    {
        fprintf(fp, "%c", *(bloom_filter->bytes + i));
    }   
    fclose(fp);
    return 1;
}
char* char_2_binary(unsigned char ch)
{
    char *str = (char*)malloc(9);
    int i;
    for(i=0; i<8; i++)
    {
	/*if(ch & 0x80)
	    str[i] = '1';
	else
	    str[i] = '0';
	*/
	str[i] = (ch & 0x80) == 0 ? '0' : '1';
	ch <<= 1; 
    }
    str[8] = '\0';
    return str;
}
void bloom_filter_print_01(bloom_filter_p bloom_filter)
{
    assert(bloom_filter != NULL);
    int i;
    for(i=0; i<nbytes(bloom_filter->bit_length); i++)
    {
	unsigned char ch = *(bloom_filter->bytes + i);
        printf("%s ", char_2_binary(ch));
    } 
}
