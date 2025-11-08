/**
*******************************************************************************
* @file      :main_task.cpp
* @brief     :
* @history   :
*  Version     Date            Author          Note
*  V0.9.0      yyyy-mm-dd      <author>        1. <note>
*******************************************************************************
* @attention :
*******************************************************************************
*  Copyright (c) 2024 Hello World Team，Zhejiang University.
*  All Rights Reserved.
*******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main_task.hpp"
#include "system_user.hpp"

#include "DT7.hpp"
#include "HW_can.hpp"
#include "dm4310_drv.hpp"
#include "iwdg.h"
#include "math.h"
#include "control.hpp"
//常量定义区域
constexpr float MAXSPEED = 16000;
constexpr float W = 10;
constexpr float KI1 = 0.005f;
constexpr float KI2 = 0.005f;
constexpr float KI3 = 0.005f;
constexpr float KI4 = 0.005f;
constexpr float KP1 = 0.2f;
constexpr float KP2 = 0.2f;
constexpr float KP3 = 0.2f;
constexpr float KP4 = 0.2f;
constexpr float KD1 = 0.001f;
constexpr float KD2 = 0.001f;
constexpr float KD3 = 0.001f;
constexpr float KD4 = 0.001f;
//类定义区域
control::dipan dp;
control::pid pid_control(KP1,KI1,KD1,KP2,KI2,KD2,KP3,KI3,KD3,KP4,KI4,KD4);
//函数声明区域
void MODE4(void);
void MODE2(void);
void MODE1(void);
void MODE3(void);
/* Private macro -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
//函数声明区域
uint32_t tick = 0;

namespace remote_control = hello_world::devices::remote_control;
static const uint8_t kRxBufLen = remote_control::kRcRxDataLen;
static uint8_t rx_buf[kRxBufLen];
remote_control::DT7 *rc_ptr;
void RobotInit(void) { rc_ptr = new remote_control::DT7(); }

void MainInit(void) {
  RobotInit();

  // 开启CAN1和CAN2
  CanFilter_Init(&hcan1);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  CanFilter_Init(&hcan2);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);

  // 开启遥控器接收
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, kRxBufLen);

  // 开启定时器
  HAL_TIM_Base_Start_IT(&htim6);
}

void MainTask(void) { 
tick++;
remote_control::SwitchState temp_switch_l = rc_ptr->rc_l_switch();
remote_control::SwitchState temp_switch_r = rc_ptr->rc_r_switch();
if(temp_switch_l == remote_control::kSwitchStateUp){
  MODE4();//归0
}
else if(temp_switch_r == remote_control::kSwitchStateUp){
  MODE1();//分离
}
else if(temp_switch_r == remote_control::kSwitchStateMid){
  MODE2();//跟随
}
else if(temp_switch_r == remote_control::kSwitchStateDown){
  MODE3();//自旋
}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  if (htim == &htim6) {
    MainTask();
  }
}
uint8_t rx_data = 0;
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  if (huart == &huart3) {
    if (Size == remote_control::kRcRxDataLen) {
      // TODO:在这里刷新看门狗
      HAL_IWDG_Refresh(&hiwdg);
      rc_ptr->decode(rx_buf);
    }

    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rx_buf, kRxBufLen);
  }
}


void MODE2(void){
dp.set_data(0,rc_ptr->rc_lv(),rc_ptr->rc_lh(),MAXSPEED);
dp.calculate();
pid_control.set_purpose(dp.get_v1(),dp.get_v2(),dp.get_v3(),dp.get_v4());
pid_control.calculate();
CAN_Send_Msg(&hcan2,pid_control.get_data(),0x1FE,8);
}
void MODE4(void){
dp.set_data(0,0,0,0);
dp.calculate();
pid_control.set_purpose(dp.get_v1(),dp.get_v2(),dp.get_v3(),dp.get_v4());
pid_control.calculate();
CAN_Send_Msg(&hcan2,pid_control.get_data(),0x1FE,8);
}
void MODE1(void){
  
}
void MODE3(void){
  
}