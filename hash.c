#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint64_t fnv1a_hash(const char *key) {
    uint64_t hash = FNV_OFFSET_BASIS;
    while (*key) {
        hash ^= (uint64_t)(unsigned char)(*key++);
        hash *= FNV_PRIME;
    }
    return hash;
}

hashnode *hashnode_create(const char *key, station *value) {
    hashnode *node = malloc(sizeof(hashnode));
    node->key = strdup(key);
    node->value = value;

    return node;
}

static size_t find_index(hashtbl *tbl, const char *key){
    size_t index = fnv1a_hash(key) % tbl->capacity;
    while (tbl->nodes[index].key != NULL){
        if (strcmp(tbl->nodes[index].key, key) == 0){
            return index;
        }
        index = (index + 1) % tbl->capacity;
    }   
    return index;  
}

hashtbl *hashtbl_create(){
    hashtbl *tbl = malloc(sizeof(hashtbl));
    tbl->size = 0;
    tbl->capacity = CAPACITY;
    tbl->nodes = calloc(tbl->capacity, sizeof(hashnode));

    return tbl;
}

void hashtbl_destroy(hashtbl *tbl){
    for (size_t i = 0; i < tbl->capacity; i++){
        if (tbl->nodes[i].key != NULL){
            free(tbl->nodes[i].key);
            free(tbl->nodes[i].value);
        }
    }
    free(tbl->nodes);
    free(tbl);
}

void hashtbl_insert(hashtbl *tbl, const char *key, station *value){
    size_t index = find_index(tbl, key);
    if (tbl->nodes[index].key == NULL){
        tbl->nodes[index] = *hashnode_create(key, value);
        tbl->size++;
    }
    else{
        tbl->nodes[index].value->count++;
        tbl->nodes[index].value->sum += value->sum;
        if (value->min < tbl->nodes[index].value->min) tbl->nodes[index].value->min = value->min;
        if (value->max > tbl->nodes[index].value->max) tbl->nodes[index].value->max = value->max;

        free(value);
    }
}

station *hashtbl_get(hashtbl *tbl, const char *key){
    size_t index = find_index(tbl, key);
    return tbl->nodes[index].value;
}

int hashtbl_remove(hashtbl *tbl, const char *key){
    size_t index = find_index(tbl, key);
    if (tbl->nodes[index].key == NULL){
        return 0;
    }
    free(tbl->nodes[index].key);
    free(tbl->nodes[index].value);
    tbl->nodes[index].key = NULL;
    tbl->nodes[index].value = NULL;
    tbl->size--;
    return 1;
}

size_t hashtbl_size(hashtbl *tbl){
    return tbl->size;
}

void hashtbl_sort_print(hashtbl *tbl){
    hashnode *sorted = malloc(tbl->size * sizeof(hashnode));
    size_t j = 0;
    for (size_t i = 0; i < tbl->capacity; i++){
        if (tbl->nodes[i].key != NULL){
            sorted[j] = tbl->nodes[i];
            j++;
        }
    }

    for (size_t i = 0; i < tbl->size; i++){
        for (size_t j = i + 1; j < tbl->size; j++){
            if (strcmp(sorted[i].key, sorted[j].key) > 0){
                hashnode temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    printf("{");
    for (size_t i = 0; i < tbl->size; i++){
        printf("%s=%.1f/%.1f/%.1f%s", sorted[i].key, (double)sorted[i].value->min/10, (double)(sorted[i].value->sum/10) / sorted[i].value->count, (double)sorted[i].value->max/10, i == tbl->size - 1 ? "" : ", ");
    }
    puts("}");
    free(sorted);
}



