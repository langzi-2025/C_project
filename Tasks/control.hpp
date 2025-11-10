/*
 * @Author: rogue-wave zhangjingjie@zju.edu.cn
 * @Date: 2025-11-06 21:12:30
 * @LastEditors: rogue-wave zhangjingjie@zju.edu.cn
 * @LastEditTime: 2025-11-07 21:48:52
 * @FilePath: \C_project\Tasks\control.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef CONTROL_HPP
#define CONTROL_HPP
#include <stdint.h>
namespace control
{
//常量定义区
constexpr float max_v = 300;
//类定义区
class pid{
private:
float ki1 = 0, ki2 = 0,ki3 = 0,ki4 = 0;
float kp1 = 0, kp2 = 0,kp3 = 0,kp4 = 0;
float kd1 = 0, kd2 = 0,kd3 = 0,kd4 = 0;
float e1 = 0, e2 = 0,e3 = 0,e4 = 0;
float e1_last = 0, e2_last = 0,e3_last = 0,e4_last = 0;
float e1_sum = 0, e2_sum = 0,e3_sum = 0,e4_sum = 0;
float e1_purpose = 0, e2_purpose = 0,e3_purpose = 0,e4_purpose = 0;
float v1 = 0, v2 = 0,v3 = 0,v4 = 0;
float output1 = 0, output2 = 0,output3 = 0,output4 = 0;
uint8_t send_data[8] = {0};
public:
pid(float kp1,float ki1,float kd1,float kp2,float ki2,float kd2,float kp3,float ki3,float kd3,float kp4,float ki4,float kd4){
    this->kp1 = kp1;
    this->ki1 = ki1;
    this->kd1 = kd1;
    this->kp2 = kp2;
    this->ki2 = ki2;
    this->kd2 = kd2;
    this->kp3 = kp3;
    this->ki3 = ki3;
    this->kd3 = kd3;
    this->kp4 = kp4;
    this->ki4 = ki4;
    this->kd4 = kd4;
}
float OUTPUT(void)
{
    return output1;
}
void set_purpose(float e1_purpose,float e2_purpose,float e3_purpose,float e4_purpose)
{
    this->e1_purpose = e1_purpose;
    this->e2_purpose = e2_purpose;
    this->e3_purpose = e3_purpose;
    this->e4_purpose = e4_purpose;
}
void set_su_du(float v1,float v2,float v3,float v4)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v4 = v4;
}
void calculate(void);
uint8_t* get_data(void)
{
    return send_data; 
}
};
class dipan{
public:
dipan()
{};
void calculate(void);
void set_data(float w,float v_y,float v_x,float max_speed)//输入数据
{
    this->w = w;
    this->v_y = v_y * max_speed;
    this->v_x = v_x * max_speed;
}
float get_v1(void)
{
    return v_1;
}
float get_v2(void)
{
    return v_2;
}
float get_v3(void)
{
    return v_3;
}
float get_v4(void) 
{
    return v_4;
}
private:
float w = 0;
float v_y = 0;
float v_x = 0;
float v_1 = 0;//分别对应四个底盘电机的速度
float v_2 = 0;
float v_3 = 0;
float v_4 = 0;
};

}

#endif // CONTROL_HPP