#include "NationalTrafficConsult.h"

void SetMap(CityMap *CMap, char TTable[], char FTable[]){
    // ...
    FILE *TT = fopen("./TrainTable.txt", "w");
    FILE *FT = fopen("./FlightTable.txt", "w");
    FILE *fp = NULL;
    int cities;
    for(cities=0; cities < CMap->vexnum; cities++){
        char departure[MAX_STR_LEN], terminal[MAX_STR_LEN];
        strncpy(departure, CMap->v[cities].city, MAX_STR_LEN);
        NodeLink *nl=CMap->v[cities].first;
        while(nl!=NULL){
            strncpy(terminal, CMap->v[nl->vindex].city, MAX_STR_LEN);
            int num;
            for(num=0; nl->info[num].tag!=-1; num++){
                Info info=nl->info[num];
                if(info.tag==0)  fp=fopen("./TrainTable.txt", "a");
                else fp=fopen("./FlightTable.txt", "a");
                fprintf(fp, "%-s %-15s %-15s", info.number, departure, terminal);
                char hr[2], min[2];
                hr[0] = info.start_time.hour/10 + '0';
                hr[1] = info.start_time.hour%10 + '0';
                min[0] = info.start_time.minute/10 + '0';
                min[1] = info.start_time.minute%10 + '0';
                fprintf(fp, "%c%c: %c%c ", hr[0], hr[1], min[0], min[1]);
                hr[0] = info.end_time.hour/10 + '0';
                hr[1] = info.end_time.hour%10 + '0';
                min[0] = info.end_time.minute/10 + '0';
                min[1] = info.end_time.minute%10 + '0';
                fprintf(fp, "%c%c: %c%c ", hr[0], hr[1], min[0], min[1]);
                fprintf(fp, "%-5d ", info.duration);
                fprintf(fp, "%-.2f\n", info.cost);

                fclose(fp);
            }
            nl=nl->next;
        }
    }
    fclose(FT);
    fclose(TT);
}

CityMap *GetMap(char TTable[], char FTable[]){
    // ...
}

void ShowTrainTable(CityMap *CMap, FILE *TT){
    // ...
}

void ShowFlightTable(CityMap *CMap, FILE *FT){
    // ...
}