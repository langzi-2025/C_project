#ifndef CONTROL_HPP
#define CONTROL_HPP

namespace control
{
//常量定义区
constexpr float max_v = 300;
//类定义区
class pid{

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