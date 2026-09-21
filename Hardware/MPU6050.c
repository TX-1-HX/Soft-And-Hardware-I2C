#include "stm32f10x.h"                  // Device header
#include"I2C.h"
#include"MPU6050_Register.h"

void MPU6050_WriteRegister(uint8_t Address,uint8_t Data)
{
    BaseConfig_Start();
    BaseConfig_SendByte(0XD0);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Address);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Data);
    BaseConfig_ReceiveACK();
    BaseConfig_Stop;
}

uint8_t MPU6050_ReadRegister(uint8_t Address)
{
    uint8_t Rec_Data;
    BaseConfig_Start();
    BaseConfig_SendByte(0XD0);
    BaseConfig_ReceiveACK();
    BaseConfig_SendByte(Address);
    BaseConfig_ReceiveACK();

    BaseConfig_Start();
    BaseConfig_SendByte(0XD0 | 0X01);
    BaseConfig_ReceiveACK();
    Rec_Data = BaseConfig_ReceiveByte();
    BaseConfig_SendACK(1);
    BaseConfig_Stop();

    return Rec_Data;
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
    static int16_t Data_H,Data_L;

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
}