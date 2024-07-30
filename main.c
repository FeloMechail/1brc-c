#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STATIONS 10000
#define MAX_NAME_LENGTH 100

typedef struct {
    char station_name[MAX_NAME_LENGTH];
    double min, max, sum;
    int count;
} Station;

int comparator(const void* p, const void* q){
    return strcmp(((Station*)p)->station_name, ((Station*)q)->station_name);
}

int find_staton_index(Station stations[], int station_count, char name[]) {
    for(int i = 0; i < station_count; i++) {
        if(strcmp(stations[i].station_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    //FILE *file = fopen(argv[1], "r");
    FILE *file = fopen("measurements.txt", "r");
    Station stations[MAX_STATIONS];

    int station_count = 0;
    char buffer[1024];


    //file format is stationName;temperature

    while(fgets(buffer, 1024, file)) {
        char *delim = strchr(buffer, ';');
        *delim = '\0';

        double temperature = strtod(delim + 1, NULL);

        int index = find_staton_index(stations, station_count, buffer);

        if(index == -1){
            index = station_count++;
            strcpy(stations[index].station_name, buffer);
            stations[index].min = stations[index].max = temperature;
            stations[index].sum = temperature;
            stations[index].count = 1;
        } else {
            if (temperature < stations[index].min) stations[index].min = temperature;
            if (temperature > stations[index].max) stations[index].max = temperature;
            stations[index].sum += temperature;
            stations[index].count++;
        }
    }

    fclose(file);

    qsort((void*) stations, station_count, sizeof(Station), comparator);

    //print results in format {stationName=min/mean/max}
    printf("{");
    for(int i = 0; i < station_count; i++) {
        printf("%s=%.1f/%.1f/%.1f%s", stations[i].station_name, stations[i].min, stations[i].sum / stations[i].count, stations[i].max, i < station_count - 1 ? ", " : "");
    }
    printf("}");

    return 0;
}
