#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"


int main(){

    FILE *file = fopen("measurements.txt", "r");

    hashtbl *tbl = hashtbl_create();
    char buffer[1024];

    while(fgets(buffer, 1024, file)){
        station *s = malloc(sizeof(station));
        char *delim = strchr(buffer, ';');
        *delim = '\0';
        double temp  = strtod(delim + 1, NULL);
        
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
