#include "NationalTrafficConsult.h"

int GetDurationTime(Time t1, Time t2){
    // ���������Ļ�������д�������������ʱ��
    //t1 ��ʼʱ��  t2 ����ʱ��   
    //����ֵΪ������
    int duration;
    duration=(t2.hour-t1.hour)*60+(t2.minute-t1.minute);
    if(duration<0)
        duration+=24*60;//����
    return duration;
}

CityMap *EditTrain(CityMap *CMap){
    // ���̣�(�û�������ܲ��Ϸ�����������Ч�����������룡��)
    // ������Ҫִ�еĲ�����1/2��
    // 1. ��ӳ���
    // 2. ɾ������
    // ��������ʼվ
    // �������յ�վ
    // ���������ʱ��
    // �����뵽��ʱ��
    // ������Ʊ��
    // ------���ݵ�һ�����ʵ����ݣ���ת��AddTrain()��DelTrain()
    printf("��ѡ����Ҫִ�еĲ�����1/2��\n");
    printf("1.��ӳ���\n");
    printf("2.ɾ������\n");
    int choice;//1�������,2����ɾ��
    scanf("%d\n",&choice);//�����û��������ֺ��谴�س���
    printf("��������ʼվ\n");
    char departure;
    printf("�������յ�վ\n");
    char terminal;

}

CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *DelTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *EditFlight(CityMap *CMap){
    // ���̣�(�û�������ܲ��Ϸ�����������Ч�����������룡��)
    // ������Ҫִ�еĲ�����1/2��
    // 1. ��Ӻ���
    // 2. ɾ������
    // ��������ʼվ
    // �������յ�վ
    // ���������ʱ��
    // �����뵽��ʱ��
    // ������Ʊ��
    // ------���ݵ�һ�����ʵ����ݣ���ת��AddFlight()��DelFlight()
}

CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *DelFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

void InvalidInputs(void){
    printf("������Ч�����������룡");
    return;
}