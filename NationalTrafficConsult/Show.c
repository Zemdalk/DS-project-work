#include "NationalTrafficConsult.h"

void SetMap(CityMap *CMap, char TTable[], char FTable[]){
    // ...
    FILE *TT = fopen(TTable, "w");
    FILE *FT = fopen(FTable, "w");
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
                if(info.tag==0)  fp=fopen(TTable, "a");
                else fp=fopen(FTable, "a");
                PrintLine(info, departure, terminal, fp);
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
    CityMap *CMap = malloc(sizeof(CityMap));
    CMap->edgenum = CMap->vexnum = 0;
    FILE *pf = fopen(TTable, "r");
    char number[8]="";
    char departure[MAX_STR_LEN]="", terminal[MAX_STR_LEN]="";
    Time start_time;
    Time end_time;
    int duration;
    char cost_str[MAX_STR_LEN];
    double cost;
    char c1, c2;
    char sh1, sm1, sh2, sm2;
    char eh1, em1, eh2, em2;

    while(fscanf(pf, "%s %s %s %c%c%c %c%c   %c%c%c %c%c   %d %s\n", 
        number, departure, terminal, &sh1, &sh2, &c1, &sm1, &sm2, &eh1, &eh2, &c2, &em1, &em2, 
        &duration, cost_str) != EOF){
        cost=atof(cost_str);
        // fgetc(pf);

        start_time.hour = (sh1-'0')*10+(sh2-'0');
        start_time.minute = (sm1-'0')*10+(sm2-'0');
        end_time.hour = (eh1-'0')*10+(eh2-'0');
        end_time.minute = (em1-'0')*10+(em2-'0');

        CMap = AddTrain(CMap, departure, terminal, start_time, end_time, cost);
        strncpy(departure, "", MAX_STR_LEN);
        strncpy(terminal, "", MAX_STR_LEN);
    }

    fclose(pf);
    pf = fopen(FTable, "r");

    while(fscanf(pf, "%s %s %s %c%c%c %c%c %c%c%c %c%c %d %s\n", 
        number, departure, terminal, &sh1, &sh2, &c1, &sm1, &sm2, &eh1, &eh2, &c2, &em1, &em2, 
        &duration, cost_str) != EOF){
        cost=atof(cost_str);
        fgetc(pf);

        start_time.hour = (sh1-'0')*10+(sh2-'0');
        start_time.minute = (sm1-'0')*10+(sm2-'0');
        end_time.hour = (eh1-'0')*10+(eh2-'0');
        end_time.minute = (em1-'0')*10+(em2-'0');

        CMap = AddFlight(CMap, departure, terminal, start_time, end_time, cost);
        strncpy(departure, "", MAX_STR_LEN);
        strncpy(terminal, "", MAX_STR_LEN);
    }

    return CMap;
}

void ShowTrainTable(CityMap *CMap, char TTable[]){
    int totalpage=0;

    FILE *pf=fopen(TTable, "r");
    int len;
    char buff[MAX_STR_LEN];
    while(fgets(buff, MAX_STR_LEN, pf) != NULL){
        len=strlen(buff);
        buff[len-1]='\0';  // ȥ�����з�
        totalpage++;
    }
    if(totalpage % MAX_PAGE_LINES){
        totalpage /= MAX_PAGE_LINES;
    }else{
        totalpage /= MAX_PAGE_LINES;
        totalpage--;
    }
    if(totalpage == -1) totalpage++; // �ձ�totalpage����Ϊ-1�����⴦��Ϊ0
    fclose(pf);

    // totalpage: ��ҳ��������0��ʼ�����������ʵ����ҳ����С1
    // offset: ҳ����ţ���0��ʼ�����������ʵ��ҳ�����С1
    // func: ѡ��Ĺ���
    int offset=0, func;
    ShowTrainTableByPage(CMap, TTable, offset, totalpage);
    do{
        printf("��ѡ�񡭡�\n");
        printf("(1. ��һҳ  2. ��һҳ  3. ��ת��ָ��ҳ��  4. �˳�)\n");
        scanf("%d", &func); getchar();
        if(func == 4) break;
        else if((func == 1 && offset == 0) || (func == 2 && offset == totalpage)){
            InvalidInputs();
            continue;
        }else if(func == 1){
            offset--;
        }else if(func == 2){
            offset++;
        }else if(func == 3){
            printf("��������Ҫ��ת����ҳ��: \n");
            scanf("%d", &offset); getchar();
            offset--;
            if (!(offset >= 0 && offset <= totalpage)){
                InvalidInputs();
                continue;
            }
        }else if(!(func >= 1 && func <= 4)){
            InvalidInputs();
            continue;
        }

        ShowTrainTableByPage(CMap, TTable, offset, totalpage);

    }while(1);
}

void ShowTrainTableByPage(CityMap *CMap, char TTable[], int offset, int totalpage){
    int i;
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<34;i++) printf(" ");
    printf("�г����α�");
    for(i=0;i<34;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    printf("����    ");
    printf("ʼ��վ");
    for(i=0;i<10;i++) printf(" ");
    printf("�յ�վ");
    for(i=0;i<9;i++) printf(" ");
    printf("����ʱ�� ");
    printf("����ʱ�� ");
    printf("ʱ��(����)  ");
    printf("Ʊ��(Ԫ)");
    printf("\n");

    FILE *pf=fopen(TTable, "r");
    int len, counter=0;
    char buff[MAX_STR_LEN];
    while(fgets(buff, MAX_STR_LEN, pf) != NULL){
        len=strlen(buff);
        buff[len-1]='\0';  // ȥ�����з�
        if(counter >= (offset * MAX_PAGE_LINES) && counter < ((offset + 1) * MAX_PAGE_LINES)) 
            printf("%s\n", buff);
        counter++;
        if(counter >= ((offset + 1) * MAX_PAGE_LINES)) break;
    }

    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<31;i++) printf(" ");
    printf("�� %d ҳ���� %d ҳ", offset + 1, totalpage + 1);
    for(i=0;i<31;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");

    fclose(pf);
}

void ShowFlightTable(CityMap *CMap, char FTable[]){
    int totalpage=0;

    FILE *pf=fopen(FTable, "r");
    int len;
    char buff[MAX_STR_LEN];
    while(fgets(buff, MAX_STR_LEN, pf) != NULL){
        len=strlen(buff);
        buff[len-1]='\0';  // ȥ�����з�
        totalpage++;
    }
    if(totalpage % MAX_PAGE_LINES){
        totalpage /= MAX_PAGE_LINES;
    }else{
        totalpage /= MAX_PAGE_LINES;
        totalpage--;
    }
    if(totalpage == -1) totalpage++; // �ձ�totalpage����Ϊ-1�����⴦��Ϊ0
    fclose(pf);

    // totalpage: ��ҳ��������0��ʼ�����������ʵ����ҳ����С1
    // offset: ҳ����ţ���0��ʼ�����������ʵ��ҳ�����С1
    // func: ѡ��Ĺ���
    int offset=0, func;
    ShowFlightTableByPage(CMap, FTable, offset, totalpage);
    do{
        printf("��ѡ�񡭡�\n");
        printf("(1. ��һҳ  2. ��һҳ  3. ��ת��ָ��ҳ��  4. �˳�)\n");
        scanf("%d", &func); getchar();
        if(func == 4) break;
        else if((func == 1 && offset == 0) || (func == 2 && offset == totalpage)){
            InvalidInputs();
            continue;
        }else if(func == 1){
            offset--;
        }else if(func == 2){
            offset++;
        }else if(func == 3){
            printf("��������Ҫ��ת����ҳ��: \n");
            scanf("%d", &offset); getchar();
            offset--;
            if (!(offset >= 0 && offset <= totalpage)){
                InvalidInputs();
                continue;
            }
        }else if(!(func >= 1 && func <= 4)){
            InvalidInputs();
            continue;
        }

        ShowFlightTableByPage(CMap, FTable, offset, totalpage);

    }while(1);
}

void ShowFlightTableByPage(CityMap *CMap, char FTable[], int offset, int totalpage){
    int i;
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<34;i++) printf(" ");
    printf("�ɻ������");
    for(i=0;i<34;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");
    printf("�����  ");
    printf("ʼ��վ");
    for(i=0;i<10;i++) printf(" ");
    printf("�յ�վ");
    for(i=0;i<9;i++) printf(" ");
    printf("����ʱ�� ");
    printf("����ʱ�� ");
    printf("ʱ��(����)  ");
    printf("Ʊ��(Ԫ)");
    printf("\n");

    FILE *pf=fopen(FTable, "r");
    int len, counter=0;
    char buff[MAX_STR_LEN];
    while(fgets(buff, MAX_STR_LEN, pf) != NULL){
        len=strlen(buff);
        buff[len-1]='\0';  // ȥ�����з�
        if(counter >= (offset * MAX_PAGE_LINES) && counter < ((offset + 1) * MAX_PAGE_LINES)) 
            printf("%s\n", buff);
        counter++;
        if(counter >= ((offset + 1) * MAX_PAGE_LINES)) break;
    }

    for(i=0;i<79;i++) printf("=");
    printf("\n");
    for(i=0;i<31;i++) printf(" ");
    printf("�� %d ҳ���� %d ҳ", offset + 1, totalpage + 1);
    for(i=0;i<31;i++) printf(" ");
    printf("\n");
    for(i=0;i<79;i++) printf("=");
    printf("\n");

    fclose(pf);
}

void PrintLine(Info info, char departure[], char terminal[], FILE *fp){
    fprintf(fp, "%-s %-15s %-15s", info.number, departure, terminal);
    char hr[2], min[2];
    hr[0] = info.start_time.hour/10 + '0';
    hr[1] = info.start_time.hour%10 + '0';
    min[0] = info.start_time.minute/10 + '0';
    min[1] = info.start_time.minute%10 + '0';
    fprintf(fp, "%c%c: %c%c   ", hr[0], hr[1], min[0], min[1]);
    hr[0] = info.end_time.hour/10 + '0';
    hr[1] = info.end_time.hour%10 + '0';
    min[0] = info.end_time.minute/10 + '0';
    min[1] = info.end_time.minute%10 + '0';
    fprintf(fp, "%c%c: %c%c   ", hr[0], hr[1], min[0], min[1]);
    fprintf(fp, "%-11d ", info.duration);
    fprintf(fp, "%-.2f\n", info.cost);
}
