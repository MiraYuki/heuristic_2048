//
//  main.cpp
//  heuristic_2048
//
//  Created by Mirai on 15/6/29.
//  Copyright (c) 2015年 Mirai. All rights reserved.
//

#include <iostream>
#include "en_2048.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //构造环境
    en_2048* matrix = new en_2048();
    matrix->initial_game();
    matrix->print_current();
    
    char input='w';
    
    while(!matrix->isGameEnd())
    {
        cin>>input;
        switch (input)
        {
            case 'w':
                matrix->move_up();
                break;
            case 'd':
                matrix->move_right();
                break;
            case 's':
                matrix->move_down();
                break;
            case 'a':
                matrix->move_left();
                break;
            case 'z':
                matrix->initial_game();
                break;
        }
    }
    
    
    return 0;
}
