/*
 * A unit test and example of how to use the simple C hashmap
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (2)

typedef struct data_struct_s
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;

const char *strings[] = {
	"a:10", "b:20"
};

int main(char* argv, int argc)
{
    int index;
    int error;
    map_t mymap;
    char key_string[KEY_MAX_LENGTH];
    data_struct_t* value;

    fprintf(stderr, "start...\n");
    mymap = hashmap_new();

    /* First, populate the hash map with ascending values */
    for (index=0; index<KEY_COUNT; index+=1)
    {
        /* Store the key string along side the numerical value so we can free it later */
        value = malloc(sizeof(data_struct_t));
        //snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
        snprintf(value->key_string, KEY_MAX_LENGTH, "%s", strings[index]);
        value->number = index;
        //fprintf(stderr, "value->key_string=%s, value->number=%d\n",
        //        value->key_string, value->number);

        error = hashmap_put(mymap, value->key_string, value);
        assert(error==MAP_OK);
    }

    /* Now, check all of the expected values are there */
    for (index=0; index<KEY_COUNT; index+=1)
    {
        //snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
        snprintf(key_string, KEY_MAX_LENGTH, "%s", strings[index]);

        error = hashmap_get(mymap, key_string, (void**)(&value));
        //fprintf(stderr, "error=%d, value->number=%d, index=(%d)\n", error, value->number, index);

        /* Make sure the value was both found and the correct number */
        assert(error==MAP_OK);
        assert(value->number==index);
    }

    /* Make sure that a value that wasn't in the map can't be found */
    snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, KEY_COUNT);
    //snprintf(key_string, KEY_MAX_LENGTH, "%s", KEY_COUNT);

    error = hashmap_get(mymap, key_string, (void**)(&value));
    fprintf(stderr, "error=%d\n", error);

    /* Make sure the value was not found */
    assert(error==MAP_MISSING);

    /* Free all of the values we allocated and remove them from the map */
    for (index=0; index<KEY_COUNT; index+=1)
    {
        //snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
        snprintf(key_string, KEY_MAX_LENGTH, "%s", strings[index]);

        error = hashmap_get(mymap, key_string, (void**)(&value));
        assert(error==MAP_OK);

        error = hashmap_remove(mymap, key_string);
        assert(error==MAP_OK);

        free(value);
    }

    /* Now, destroy the map */
    hashmap_free(mymap);

    return 1;
}
