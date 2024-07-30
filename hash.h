#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdint.h>

#define CAPACITY 10000
#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211

typedef struct {
    char station_name[100];
    double min, max, sum;
    int count;
} station;

typedef struct {
    char *key;
    station *value;
} hashnode;

typedef struct {
    size_t size;
    size_t capacity;
    hashnode *nodes;    
} hashtbl;

hashtbl *hashtbl_create();
hashnode *hashnode_create(const char *key, station *value);
void hashtbl_destroy(hashtbl *tbl);
void hashtbl_insert(hashtbl *tbl, const char *key, station *value);
station *hashtbl_get(hashtbl *tbl, const char *key);
int hashtbl_remove(hashtbl *tbl, const char *key);
size_t hashtbl_size(hashtbl *tbl);
void hashtbl_sort_print(hashtbl *tbl);

#endif // HASH_H
