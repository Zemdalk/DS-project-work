# 题目

参照教材10.6.1 多关键字的排序。

# 数据结构

（？）

最多10000个记录，每个记录中有5个关键字，取值范围均为0到100（101个数！），由用户指定关键字的优先顺序（如何指定？）。

类比高考：最多10000名考生，最多5门功课，满分100分。

# 排序法

- LSD
  - 稳定的内部排序法
  - “分配”和收集的方法
    - 比较两种策略的时间花销（计算、输出程序执行时间）
- （选做）MSD
- （选做）比较LSD与MSD

# 细节

## 随机数生成

[Random Function in C](https://www.javatpoint.com/random-function-in-c)

The `srand()` function is a C library function that determines the initial point to generate different series of pseudo-random numbers. **A `srand()` function cannot be used without using a `rand()` function.** The `srand()` function is required to **set the value of the seed only once in a program** to generate the different results of random integers before calling the `rand()` function.

``` c
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> // use time.h header file to use time  
      
int main()  
{  
    int num, i;  
    time_t t1; // declare time variable  
      
    printf(" Enter a number to set the limit for a random number \n");  
    scanf (" %d", &num);  
      
    /* define the random number generator */  
    srand ( (unsigned) time (&t1)); // pass the srand() parameter  
    printf("\n"); // print the space  
    /* generate random number between 0 to 50 */  
    for (i = 0; i <num; i++)  
    {  
        printf( "%d \n", rand() % 50);  
    }  
     return 0;  
}  
```

**Output**: 

1st execution:

```
Enter a number to set the limit for a random number
10

44      32      23      35      6       33      1       4       22      18
```

2nd execution:

```
Enter a number to set the limit for a random number
15	

13      30      24      27      4       30      28      35      36      13      44      39      21      5       7
```

## 获取程序运行时间

[Find execution time of a C program](https://www.techiedelight.com/find-execution-time-c-program/)

We can use the `clock()` function provided by the `<time.h>` header file to calculate the CPU time consumed by a task within a C application. It returns the `clock_t` type, which stores the total number of clock ticks.

To compute the total number of seconds elapsed, we need to divide the total number of clock ticks elapsed by `CLOCKS_PER_SEC` macro (also present in `<time.h>`) as shown below:

``` c

#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
 
// main function to find the execution time of a C program
int main()
{
    // to store the execution time of code
    double time_spent = 0.0;
 
    clock_t begin = clock();
 
    // do some stuff here
    sleep(3);
 
    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
 
    return 0;
}
```

**Output**:

```
The elapsed time is 0.000014 seconds
```