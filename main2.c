#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include <stdbool.h>

int parse_to_int(char *key);
bool is_int(char c);

inline bool is_int(char c){
    return c >= '0' && c <= '9';
}

int parse_to_int(char *key){
    bool negative = 0;
    if(*key == '-') negative = 1, key++;
    int res = 0;

    while(*key != '\n'){
        if(is_int(*key)) {
            res = res * 10 + *key++ - '0';

        } else {
            key++;
            res = res * 10 + *key++ - '0';
        }
    }

    return negative ? -res : res;
}

int main(){

    FILE *file = fopen("measurements.txt", "r");

    hashtbl *tbl = hashtbl_create();
    char buffer[1024];

    while(fgets(buffer, 1024, file)){
        station *s = malloc(sizeof(station));
        char *delim = strchr(buffer, ';');
        *delim = '\0';

        int temp = parse_to_int(delim + 1);
        s->min = temp;
        s->max = temp;
        s->sum = temp;
        s->count = 1;

        hashtbl_insert(tbl, buffer, s);
    
    }
    hashtbl_sort_print(tbl);
    hashtbl_destroy(tbl);

    fclose(file);
    return 0;

}
