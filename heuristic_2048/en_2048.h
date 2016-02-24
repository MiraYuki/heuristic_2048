//
//  en_2048.h
//  heuristic_2048
//
//  Created by Mirai on 15/6/29.
//  Copyright (c) 2015年 Mirai. All rights reserved.
//

#ifndef __heuristic_2048__en_2048__
#define __heuristic_2048__en_2048__

#include <stdlib.h>
#include <stdio.h>
#include <list>

using namespace std;
class en_2048
{
private:
    
    bool isEnd;//标示游戏是否已经结束
    bool isLog;//是否打印Log
    
    
    
    int current_matrix_2048[4][4];//当前结果
    int next_matrix_2048[4][4];//存储下一个结果
    bool isGo;//下一次的结果是否已经被实际存储过
    int steps;
    long score;
    int emptyList[16];//在内存栈上创建空间，用于记录目前空白的格子
    int* operateSpace[4];//在内存栈上创建一片空间，这篇空间存储了操作数据的地址
    
    
    void count_result();//计算操作结果，计算结果会存储到下一结果中
    void copy_matrix();//将当前下一个结果存储到当前结果中
    void reverse_matrix();//将当前结果复制回上一次结果中
    
    void operate(int direction);//进行一次方向操作
                                //1. up
                                //2. right
                                //3. down
                                //4. left
    void create_new_square();//再一次操作之后创建一个新的方格
    void getEmptyList();//获取当前结果中空白的没有数据的区域
    void dealOperate();//对操作空间的数据进行操作，做一次合并操作
    bool compare_same();//对比下一步的矩阵和当前矩阵是否一致
    bool checkEnd();
    
    void forTestEnvironment();//创建一个特定数据的环境用于测试
    
public:
    //初始化相关
    en_2048();
    ~en_2048();
    
    void initial_game();
    
    bool isGameEnd();
    
    //操作相关
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    
    void print_current();
    void print_next();
    
};

#endif /* defined(__heuristic_2048__en_2048__) */
