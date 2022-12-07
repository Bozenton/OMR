/**
 * **************************************************************
 * @file AHRS.c
 * @author xiaobaige (buaaxiaobaige@163.com)
 * @brief 对于MahonyAHRS的封装
 * @version 0.1
 * @date 2022-12-07
 * 
 * @copyright Copyright (c) 2022
 * 
 * **************************************************************
 */

#include <math.h>
#include "AHRS.h"
#include "MahonyAHRS.h"


/**
  * @brief          根据加速度的数据，磁力计的数据进行四元数初始化
  * @param[in]      需要初始化的四元数数组,(w, x, y, z)
  * @param[in]      用于初始化的加速度计,(x,y,z)不为空 单位 m/s2 
  * @param[in]      用于初始化的磁力计计,(x,y,z)不为空 单位 uT
  * @retval         返回空
  */
void AHRS_init(fp32 quat[4], fp32 accel[3], fp32 mag[3])
{
    quat[0] = 1.0f;
    quat[1] = 0.0f;
    quat[2] = 0.0f;
    quat[3] = 0.0f;
}

/**
  * @brief          根据陀螺仪的数据，加速度的数据，磁力计的数据进行四元数更新
  * @param[in]      需要更新的四元数数组
  * @param[in]      更新定时时间，固定定时调用，例如1000Hz，传入的数据为0.001f,
  * @param[in]      用于更新的陀螺仪数据,数组顺序(x,y,z) 单位 rad
  * @param[in]      用于初始化的加速度数据,数组顺序(x,y,z) 单位 m/s2 
  * @param[in]      用于初始化的磁力计数据,数组顺序(x,y,z) 单位 uT
  * @retval         1:更新成功, 0:更新失败
  */
void AHRS_update(fp32 quat[4], const fp32 timing_time, const fp32 gyro[3], const fp32 accel[3], const fp32 mag[3])
{
    MahonyAHRSupdate(quat, gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], mag[0], mag[1], mag[2]);
}


/**
  * @brief          根据四元数大小计算对应的欧拉角yaw，pitch，roll
  * @param[in]      四元数数组，不为NULL
  * @param[in]      返回的偏航角yaw 单位 rad
  * @param[in]      返回的俯仰角pitch  单位 rad
  * @param[in]      返回的横滚角roll 单位 rad
  */
void get_angle(const fp32 q[4], fp32 *yaw, fp32 *pitch, fp32 *roll)
{
    *yaw = atan2(2.0f*(q[0]*q[3]+q[1]*q[2]), 2.0f*(q[0]*q[0]+q[1]*q[1])-1.0f);
    *pitch = asin(-2.0f*(q[1]*q[3]-q[0]*q[2]));
    *roll = atan2(2.0f*(q[0]*q[1]+q[2]*q[3]),2.0f*(q[0]*q[0]+q[3]*q[3])-1.0f);
}

