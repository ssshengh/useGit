#ifndef  COORDIN_H
/**
 * 这东西的作用是：
 * 同一个文件中只能包含一次头文件，但有时候不知情下会包含多次：使用了某个包含所使用的另一个头文件的头文件
 * if not define
 * 这段代码意味着，仅当以前没有通过预处理器编译指令#difine名称时，才处理代码中间的语句
*/
#define COORDIN_H

struct polar
{
    double distance;
    double angle;
};

struct rect
{
    double x;
    double y;
};


polar rectToPolar( rect xypos);
void showPolar(polar dapos);


double waring = 0.3;
const int aa = 10;

#endif