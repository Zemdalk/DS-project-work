#include "NationalTrafficConsult.h"
//CityMap *TestData();

int main(){
    // ����д���ÿ��Ļ�ӭ���棬��Ҫ��������Ϣ
    printf("----------------------------------------------------------��ӭʹ��������12306--------------------------------------------------------\n");
    printf("\t\t\t\t\t\t������Ա����������������Ž�\n");
    printf("�����������Ϥ���������Ȳ���˵���ֲ�\n");
    printf("ϣ����������Ϊ���ĳ����ṩ����\n");
    printf("ף��ƽ�����У���;���!\n");

    printf("\n");
    
    char TTable[MAX_STR_LEN] = "TrainTable.txt";
    char FTable[MAX_STR_LEN] = "FlightTable.txt";

    // next few lines are used for test (noted by lxy)
    // CityMap *CMap = TestData();                 // ʹ�ò�������TestData.c

    // next line is used for release file (noted by lxy)
    CityMap *CMap = GetMap(TTable, FTable);  // ���ļ��г�ʼ����ͨͼ

    //�û�����չʾ
    

    while(1){
        SetMap(CMap, TTable, FTable);
        printf("��ѡ���ܣ�(1: ��ʾ�г�ʱ�̱�  2: ��ʾ�ɻ������  3: �༭�г�ʱ�̱�  4: �༭�ɻ������  5: ����·�߹滮)\n");
        int func;
        scanf("%d",&func);
        getchar();
        switch (func){
            case 1:
                ShowTrainTable(CMap, TTable);
                break;
            case 2:
                ShowFlightTable(CMap, FTable);
                break;
            case 3:
                CMap = EditTrain(CMap);
                break;
            case 4:
                CMap = EditFlight(CMap);
                break;
            case 5:
                Decision(CMap);
                break;
            default:
                InvalidInputs();
                func=0;
                continue;
        }
        printf("���Ƿ�Ҫ������(Y: ���� N: �˳�)\n");
        char c = getchar();
        getchar();
        if(c=='N') break;
    }
}