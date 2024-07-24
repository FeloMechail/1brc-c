#include <stdio.h>
#include <string.h>

#define MAX_STATIONS 10000
#define MAX_NAME_LENGTH 100

typedef struct {
    char station_name[MAX_NAME_LENGTH];
    float min, max, sum;
    int count;
} Station;

int find_staton_index(Station stations[], int station_count, char name[]) {
    for(int i = 0; i < station_count; i++) {
        if(strcmp(stations[i].station_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE *file = fopen("test.txt", "r");
    Station stations[MAX_STATIONS];

    int station_count = 0;
    char name[MAX_NAME_LENGTH];
    float temperature;

    //file format is stationName;temperature

    while(fscanf(file, "%[^;];%f\n", name, &temperature) != EOF) {
        int index = find_staton_index(stations, station_count, name);

        if(index == -1){
            index = station_count++;
            strcpy(stations[index].station_name, name);
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

    //print results in format {stationName=min/mean/max}
    printf("{");
    for(int i = 0; i < station_count; i++) {
        printf("%s=%.2f/%.2f/%.2f\n", stations[i].station_name, stations[i].min, stations[i].sum / stations[i].count, stations[i].max);
    }
    printf("}");

    return 0;
}

