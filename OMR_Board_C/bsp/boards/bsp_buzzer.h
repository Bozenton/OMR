/**
 * @file bsp_buzzer.h
 * @author xiaobaige (buaaxiaobaige@163.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BSP_BUZZER_H
#define BSP_BUZZER_H
#include "struct_typedef.h"
extern void buzzer_on(uint16_t psc, uint16_t pwm);
extern void buzzer_off(void);

#endif
