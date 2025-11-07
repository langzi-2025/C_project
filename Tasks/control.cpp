/*
 * @Author: rogue-wave zhangjingjie@zju.edu.cn
 * @Date: 2025-11-06 21:12:54
 * @LastEditors: rogue-wave zhangjingjie@zju.edu.cn
 * @LastEditTime: 2025-11-07 21:48:24
 * @FilePath: \C_project\Tasks\control.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "control.hpp"
#include <math.h>
#include <stdint.h>
#include <cstdint>
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
void control::pid::calculate(void)//pid计算
{
    //一号电机pid控制，单速度环
    e1_last = e1;
    e1 = e1_purpose - v1;
    e1_sum += e1;
    if(e1_sum>1000) e1_sum=1000;
    if(e1_sum<-1000) e1_sum=-1000;
    output1 = kp1*e1 + ki1*e1_sum + kd1*(e1-e1_last);
    //二号电机pid控制，单速度环
    e2_last = e2;
    e2 = e2_purpose - v2;
    e2_sum += e2;
    if(e2_sum>1000) e2_sum=1000;
    if(e2_sum<-1000) e2_sum=-1000;
    output2 = kp2*e2 + ki2*e2_sum + kd2*(e2-e2_last);
    //三号电机pid控制，单速度环
    e3_last = e3;
    e3 = e3_purpose - v3;
    e3_sum += e3;
    if(e3_sum>1000) e3_sum=1000;
    if(e3_sum<-1000) e3_sum=-1000;
    output3 = kp3*e3 + ki3*e3_sum + kd3*(e3-e3_last);
    //四号电机pid控制，单速度环
    e4_last = e4;
    e4 = e4_purpose - v4;
    e4_sum += e4;
    if(e4_sum>1000) e4_sum=1000;
    if(e4_sum<-1000) e4_sum=-1000;
    output4 = kp4*e4 + ki4*e4_sum + kd4*(e4-e4_last);
    int16_t temp = (int16_t)output1;
    send_data[0] = (uint8_t)(temp>>8);
    send_data[1] = (uint8_t)(temp&0xff);
    temp = (int16_t)output2;
    send_data[2] = (uint8_t)(temp>>8);
    send_data[3] = (uint8_t)(temp&0xff);
    temp = (int16_t)output3;
    send_data[4] = (uint8_t)(temp>>8);
    send_data[5] = (uint8_t)(temp&0xff);
    temp = (int16_t)output4;
    send_data[6] = (uint8_t)(temp>>8);
    send_data[7] = (uint8_t)(temp&0xff);
}
