#include "package.h"

int32_t package_create(package_p package, char *data, size_t max_len)
{
    if(NULL == package || NULL == data || max_len <= 0)
    {
        return -1;
    }
}
