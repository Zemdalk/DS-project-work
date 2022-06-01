#include "NationalTrafficConsult.h"

void Decision(CityMap *CMap){
    // 流程：(用户输入可能不合法，“输入无效，请重新输入！”)
    // 请输入交通工具
    // 请输入起始站
    // 请输入终点站
    // 您希望的决策方式？(1/2/3)
    // 1. 乘坐时间最短
    // 2. 花费最少
    // 3. 中转次数最少
    // ------然后跳转到下面三个函数之一
}

void LeastDurationTime(CityMap *CMap, char departure[], char terminal[], int transportation){
    // ...
}

void LeastCost(CityMap *CMap, char departure[], char terminal[], int transportation){
    // ...
}

void LeastExchange(CityMap *CMap, char departure[], char terminal[], int transportation){
    // ...
}