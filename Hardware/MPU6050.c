#include "stm32f10x.h"                  // Device header
#include"I2C.h"

void MPU6050_Init(void)
{
    MI2C_Init();
}

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