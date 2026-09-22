#include "stm32f10x.h"                  // Device header
#include "I2C.h"
#include "MPU6050_Register.h"

void MPU6050_WriteRegister(uint8_t Address,uint8_t Data)
{
    BaseConfig_Start();
    BaseConfig_SendByte(0XD0);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Address);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Data);
    BaseConfig_ReceiveACK();
    BaseConfig_Stop();
}
/*                实现用I2C读取连续的一片地址来获取MPU6050的数值特征               */
void MPU6050_ReadRegister(uint8_t Address, int16_t *MPU6050_Data)
{
    BaseConfig_Start();
    BaseConfig_SendByte(0XD0);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Address);
    BaseConfig_ReceiveACK();

    BaseConfig_Start();
    BaseConfig_SendByte(0XD0 | 0X01);
    BaseConfig_ReceiveACK();
    for(uint8_t i = 0; i<14; i++)
    {
        if(i < 13)
        {
            MPU6050_Data[i] = BaseConfig_ReceiveByte();
            BaseConfig_SendACK(0);
        }
        else
        {
            MPU6050_Data[i] = BaseConfig_ReceiveByte();
            BaseConfig_SendACK(1);
        }
        
    }

    BaseConfig_Stop();

}

void MPU6050_Init(void)
{
    MI2C_Init();
    MPU6050_WriteRegister(MPU6050_PWR_MGMT_1,0X01);
    MPU6050_WriteRegister(MPU6050_PWR_MGMT_2,0x00);
    MPU6050_WriteRegister(MPU6050_SMPLRT_DIV,0x09);
    MPU6050_WriteRegister(MPU6050_CONFIG,0x06);
    MPU6050_WriteRegister(MPU6050_GYRO_CONFIG,0x18);
    MPU6050_WriteRegister(MPU6050_ACCEL_CONFIG,0x18);
    
}

void MPU6050_GetData(int16_t *AX,int16_t *AY,int16_t *AZ,int16_t *GX,int16_t *GY,int16_t *GZ)
{
    int16_t MPU6050_ReceiveData[14];
    MPU6050_ReadRegister(MPU6050_ACCEL_XOUT_H,MPU6050_ReceiveData);
    *AX = (MPU6050_ReceiveData[1-1]<<8) | MPU6050_ReceiveData[2-1];
    *AY = (MPU6050_ReceiveData[3-1]<<8) | MPU6050_ReceiveData[4-1];
    *AZ = (MPU6050_ReceiveData[5-1]<<8) | MPU6050_ReceiveData[6-1];
    *GX = (MPU6050_ReceiveData[9-1]<<8) | MPU6050_ReceiveData[10-1];
    *GY = (MPU6050_ReceiveData[11-1]<<8) | MPU6050_ReceiveData[12-1];
    *GZ = (MPU6050_ReceiveData[13-1]<<8) | MPU6050_ReceiveData[14-1];
/*
    Data_H = MPU6050_ReadRegister(MPU6050_ACCEL_XOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_ACCEL_XOUT_L);
    *AX = (Data_H<<8) | Data_L;

    Data_H = MPU6050_ReadRegister(MPU6050_ACCEL_YOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_ACCEL_YOUT_L);
    *AY = (Data_H<<8) | Data_L;

    Data_H = MPU6050_ReadRegister(MPU6050_ACCEL_ZOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_ACCEL_ZOUT_L);
    *AZ = (Data_H<<8) | Data_L;

    Data_H = MPU6050_ReadRegister(MPU6050_GYRO_XOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_GYRO_XOUT_L);
    *GX = (Data_H<<8) | Data_L;

    Data_H = MPU6050_ReadRegister(MPU6050_GYRO_YOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_GYRO_YOUT_L);
    *GY = (Data_H<<8) | Data_L;

    Data_H = MPU6050_ReadRegister(MPU6050_GYRO_ZOUT_H);
    Data_L = MPU6050_ReadRegister(MPU6050_GYRO_ZOUT_L);
    *GZ = (Data_H<<8) | Data_L;
*/


}
