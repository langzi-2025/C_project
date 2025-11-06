#include "control.hpp"
#include <math.h>
//以下单位为mm/s
#define MAX(a,b) (a)>(b)?(a):(b)//取最大值
void control::dipan::calculate(void)//底盘速度计算
{
    v_1 = -(w*216.91+sqrt(2)/2*v_y+sqrt(2)/2*v_x)/77.86;//左前，单位：转速
    v_2 = -(w*216.91-sqrt(2)/2*v_y+sqrt(2)/2*v_x)/77.86;//右前
    v_4 = -(w*216.91-sqrt(2)/2*v_y-sqrt(2)/2*v_x)/77.86;//右后
    v_3 = -(w*216.91+sqrt(2)/2*v_y-sqrt(2)/2*v_x)/77.86;//左后
    float v_max = 0;
    v_max = MAX(MAX(MAX(abs(v_1),abs(v_2)),abs(v_3)),abs(v_4));
    if(v_max > control::max_v)
    {
        v_1 = v_1/v_max*control::max_v;
        v_2 = v_2/v_max*control::max_v;
        v_3 = v_3/v_max*control::max_v;
        v_4 = v_4/v_max*control::max_v;
    }
}

