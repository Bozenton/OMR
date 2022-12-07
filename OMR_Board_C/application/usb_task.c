/**
 * **************************************************************
 * @file usb_task.c
 * @author xiaobaige (buaaxiaobaige@163.com)
 * @brief USB传输任务
 * @version 0.1
 * @date 2022-12-07
 * 
 * @copyright Copyright (c) 2022
 * @todo    detect task
 * **************************************************************
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "usb_task.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "INS_task.h"

static void usb_printf(const char *fmt,...);

extern uint8_t usb_tx_buf[128];

void usb_task(void const *argument){
    MX_USB_DEVICE_Init();
    const fp32 * quat;
    const fp32 * angle;
    const fp32 * gyro;
    const fp32 * accel;
    const fp32 * mag;

    while(1){
        osDelay(1000);
        quat = get_INS_quat_point();
        angle = get_INS_angle_point();
        gyro = get_gyro_data_point();
        accel = get_accel_data_point();
        mag = get_mag_data_point();
        if(quat!=NULL && angle!=NULL && gyro!=NULL && accel!=NULL && mag!=NULL){
            usb_printf("============================\r\n\
            quat: %f, %f, %f, %f\r\n\
            angle: %f, %f, %f\r\n\
            gyro: %f, %f, %f\r\n\
            accel: %f, %f, %f\r\n\
            mag: %f, %f, %f \r\n", 
                quat[0], quat[1], quat[2], quat[3], 
                angle[0], angle[1], angle[2], 
                gyro[0], gyro[1], gyro[2], 
                accel[0], accel[1], accel[2], 
                mag[0], mag[1], mag[2]
            );
        }

    }
}


/**
 * @brief 通过USB CDC向上位机发送信息
 * 
 * @param fmt 
 * @param ... 
 */
static void usb_printf(const char *fmt,...)
{
    static va_list ap;
    uint16_t len = 0;
    va_start(ap, fmt);
    len = vsprintf((char *)usb_tx_buf, fmt, ap);
    va_end(ap);
    CDC_Transmit_FS(usb_tx_buf, len);
}

