//
//  en_2048.cpp
//  heuristic_2048
//
//  Created by Mirai on 15/6/29.
//  Copyright (c) 2015年 Mirai. All rights reserved.
//

#include "en_2048.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Math.h>
#include <Time.h>
#include <list>

using namespace std;

typedef struct cross_2
{
    int x;
    int y;
} C_2;

en_2048::en_2048()
{
    //初始化两个矩阵
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            current_matrix_2048[i][j]=0;
            next_matrix_2048[i][j]=0;
        }
    }
    
    //初始化其它变量
    steps = 0;
    score = 0;
    
    isGo = false;
    isEnd = false;
    isLog = true;
    
}

en_2048::~en_2048()
{
    
}

void en_2048::print_current()
{
    cout<<"The current state of the game:"<<endl;
    cout<<"score:"<<score<<endl;
    cout<<"steps:"<<steps<<endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            cout<<current_matrix_2048[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"finish....."<<endl<<endl;
    
}

void en_2048::print_next()
{
    cout<<"The next state of the game:"<<endl;
    cout<<"score:"<<score<<endl;
    cout<<"steps:"<<steps<<endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            cout<<next_matrix_2048[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"finish....."<<endl<<endl;
    
}

void en_2048::initial_game()
{
    C_2 first;
    C_2 second;
    
    if(isLog)
    {
        cout<<"正在初始化游戏环境。。。。"<<endl;
    }
    //初始化随机因子
    srand((int)time(0));
    
    //初步筛选两个点
    first.x = (int)rand()%4;
    first.y = (int)rand()%4;
    second.x = (int)rand()%4;
    second.y = (int)rand()%4;
    
    //如果选出的两个点相同，那么第二个点重新选择
    while (first.x == second.x && first.y == second.y)
    {
        second.x = (int)rand()%4;
        second.y = (int)rand()%4;
    }
    
    next_matrix_2048[first.x][first.y] = ((int)rand()%2+1)*2;
    next_matrix_2048[second.x][second.y] = ((int)rand()%2+1)*2;
    copy_matrix();
    //forTestEnvironment();
}

void en_2048::forTestEnvironment()
{
    current_matrix_2048[0][0]=4;
    current_matrix_2048[0][1]=0;
    current_matrix_2048[0][2]=4;
    current_matrix_2048[0][3]=4;
}

void en_2048::copy_matrix()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            current_matrix_2048[i][j]=next_matrix_2048[i][j];
        }
    }
}

void en_2048::reverse_matrix()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            next_matrix_2048[i][j]=current_matrix_2048[i][j];
        }
    }
}

bool en_2048::compare_same()
{
    bool result = true;
    
    for(int i=0;i<4 && result==true;i++)
    {
        for(int j=0;j<4 && result==true;j++)
        {
            if(next_matrix_2048[i][j]!=current_matrix_2048[i][j])
                result = false;
        }
    }
    
    return result;
}

bool en_2048::checkEnd()
{
    bool result = true;
    for(int i=0;i<3 && result==true;i++)
    {
        for(int j=0;j<3 && result == true;j++)
        {
            if(current_matrix_2048[i][j] == current_matrix_2048[i][j+1])
                result = false;
            if(current_matrix_2048[i][j] == current_matrix_2048[i+1][j])
                result = false;
        }
    }
    return result;
}

void en_2048::operate(int direction)
{
    switch (direction)
    {
        case 1://up
            //按列处理
            if(isLog)
            {
                cout<<"玩家操作：向【上】滑动"<<endl;
            }
            for(int j=0;j<4;j++)
            {
                //在操作空间上，先进入的数据会往后进入的数据方向合并
                int p=0;
                for(int i=3;i>=0;i--)
                {
                    operateSpace[p]=&next_matrix_2048[i][j];
                    p++;
                }
                //处理这一组数据
                dealOperate();
            }
            break;
        case 2://right
            if(isLog)
            {
                cout<<"玩家操作：向【右】滑动"<<endl;
            }
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    operateSpace[j]=&next_matrix_2048[i][j];
                }
                dealOperate();
            }
            break;
        case 3:
            if(isLog)
            {
                cout<<"玩家操作：向【下】滑动"<<endl;
            }
            for(int j=0;j<4;j++)
            {
                //在操作空间上，先进入的数据会往后进入的数据方向合并
                for(int i=0;i<4;i++)
                {
                    operateSpace[i]=&next_matrix_2048[i][j];
                }
                //处理这一组数据
                dealOperate();
            }
            break;
        case 4:
            if(isLog)
            {
                cout<<"玩家操作：向【左】滑动"<<endl;
            }
            for(int i=0;i<4;i++)
            {
                int p=0;
                for(int j=3;j>=0;j--)
                {
                    operateSpace[p]=&next_matrix_2048[i][j];
                    p++;
                }
                dealOperate();
            }
            break;
    }
    
    if(!compare_same())
    {
        create_new_square();
        steps++;
        copy_matrix();
        if(!checkEnd())
        {
            if(isLog)
            {
                print_current();
            }
        }
        else
        {
            isEnd=true;
            if(isLog)
            {
                cout<<"游戏结束！Game Over!"<<endl;
            }
        }
    }
    else
    {
        if(isLog)
        {
            cout<<"错误的操作，这一次操作并有任何用"<<endl;
        }
        reverse_matrix();
    }
}

void en_2048::dealOperate()
{
    //先消去0
    for(int i=3;i>=0;i--)
    {
        if(*operateSpace[i]==0 && i!=0)
        {
            int j=1;
            while(*operateSpace[i-j]==0 && i-j!=0)
            {
                j++;
            }
            if(*operateSpace[i-j]!=0)
            {
                *operateSpace[i]=*operateSpace[i-j];
                *operateSpace[i-j]=0;
            }
                
        }
    }
    
    //在操作空间上将数据从位置0往位置3合并
    for(int i=3;i>0;i--)
    {
        //将两个相同的值合并
        //靠3得部分优先合并
        if(*operateSpace[i]==*operateSpace[i-1] && *operateSpace[i]!=0)
        {
            score+=*operateSpace[i];
            *operateSpace[i]=*operateSpace[i-1]*2;
            if(i!=1)
            {
                //位置后面的数字向前提
                for(int j=i-1;j>=1;j--)
                {
                    *operateSpace[j] = *operateSpace[j-1];
                }
            }
            *operateSpace[0]=0;
        }
    }
    //将0的位置消去
    for(int i=3;i>=0;i--)
    {
        if(*operateSpace[i]==0)
        {
            if(*operateSpace[i]==0 && i!=0)
            {
                int j=1;
                while(*operateSpace[i-j]==0 && i-j!=0)
                {
                    j++;
                }
                if(*operateSpace[i-j]!=0)
                {
                    *operateSpace[i]=*operateSpace[i-j];
                    *operateSpace[i-j]=0;
                }
                
            }
           
        }
    }
    
}

void en_2048::getEmptyList()
{
    
    int* initialPtr = emptyList;//将记录的指针指向堆中记录数组的第一个地址
    for (int i=0 ; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if(current_matrix_2048[i][j]==0)
            {
                initialPtr[0] = i*4+j;//每次在指针的第一个地址位置写入数据
                initialPtr++;//然后将指针指向下一个地址
            }
        }
    }
    initialPtr[0]=-1;//在最后的位置填下结束符-1
    
//    //打印空指针列表
//    int* printPtr = emptyList;//将便利地址指向内存堆空间的第一个位置
//    while(printPtr[0] != -1)
//    {
//        cout<<printPtr[0]<<","<<endl;
//        printPtr++;
//    }
}

void en_2048::create_new_square()
{
    int elemNum;
    int selected;
    int* emptyPtr;
    
    getEmptyList();
    emptyPtr = emptyList;
    elemNum = 0;
    while(emptyPtr[0]!=-1)
    {
        elemNum++;
        emptyPtr++;
    }
    
    srand((int)time(0));
    if(elemNum!=0)
    {
        selected =  emptyList[(int)rand()%elemNum];
    }
    else
    {
        isEnd = true;
        if(isLog)
        {
            cout<<"game over!"<<endl;
        }
    }
    if(isLog)
    {
        cout<<"new square is:("<<selected/4<<","<<selected%4<<")"<<endl;
    }
    next_matrix_2048[selected/4][selected%4]=((int)rand()%2+1)*2;
}

void en_2048::move_left()
{
    operate(4);
}

void en_2048::move_right()
{
    operate(2);
}
void en_2048::move_up()
{
    operate(1);
}
void en_2048::move_down()
{
    operate(3);
}

bool en_2048::isGameEnd()
{
    return isEnd;
}