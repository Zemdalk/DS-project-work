#include "NationalTrafficConsult.h"

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