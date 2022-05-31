#include "NationalTrafficConsult.h"

int GetDurationTime(Time t1, Time t2){
    // 你如果乐意的话，可以写这个函数来返回时长
    //t1 起始时间  t2 结束时间   
    //返回值为分钟数
    int duration;
    duration=(t2.hour-t1.hour)*60+(t2.minute-t1.minute);
    if(duration<0)
        duration+=24*60;//隔天
    return duration;
}

CityMap *EditTrain(CityMap *CMap){
    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请问您要执行的操作（1/2）
    // 1. 添加车次
    // 2. 删除车次
    // 请输入起始站
    // 请输入终点站
    // 请输入出发时间
    // 请输入到达时间
    // 请输入票价
    // ------根据第一次提问的内容，跳转到AddTrain()或DelTrain()
    printf("请选择您要执行的操作（1/2）\n");
    printf("1.添加车次\n");
    printf("2.删除车次\n");
    int choice;//1代表添加,2代表删除
    scanf("%d\n",&choice);//假设用户输入数字后需按回车键
    printf("请输入起始站\n");
    char departure;
    printf("请输入终点站\n");
    char terminal;

}

CityMap *AddTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *DelTrain(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *EditFlight(CityMap *CMap){
    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请问您要执行的操作（1/2）
    // 1. 添加航班
    // 2. 删除航班
    // 请输入起始站
    // 请输入终点站
    // 请输入出发时间
    // 请输入到达时间
    // 请输入票价
    // ------根据第一次提问的内容，跳转到AddFlight()或DelFlight()
}

CityMap *AddFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

CityMap *DelFlight(CityMap *CMap, char departure[], char terminal[], Time start_time, Time end_time, double cost){
    // ...
}

void InvalidInputs(void){
    printf("输入无效，请重新输入！");
    return;
}