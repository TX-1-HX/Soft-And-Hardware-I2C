#include "stm32f10x.h"                  // Device header

void Hardware_I2C_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    I2C_InitTypeDef I2CInitStructure;
    I2CInitStructure.I2C_Ack = ENABLE;
    I2CInitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2CInitStructure.I2C_ClockSpeed = 50000;
    I2CInitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2CInitStructure.I2C_Mode = I2C_Mode_I2C;
    I2CInitStructure.I2C_OwnAddress1 = 0X00;
    I2C_Init(I2C2,&I2CInitStructure);

    I2C_Cmd(I2C2,ENABLE);
}

void HardwareI2C_WriteRegister(uint8_t regiseter,uint8_t data)
{
    I2C_GenerateSTART(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    I2C_Send7bitAddress(I2C2,0XD0,I2C_Direction_Transmitter);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
    I2C_SendData(I2C2,regiseter);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);
    I2C_SendData(I2C2,data);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
    I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t HardwareI2C_ReceiveRegister(uint8_t regiseter)
{
    uint8_t Receive_Data;
    I2C_GenerateSTART(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    I2C_Send7bitAddress(I2C2,0XD0,I2C_Direction_Transmitter);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
    I2C_SendData(I2C2,regiseter);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);

    I2C_GenerateSTART(I2C2,ENABLE);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
    I2C_Send7bitAddress(I2C2,0XD0,I2C_Direction_Receiver);
    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

    I2C_AcknowledgeConfig(I2C2,DISABLE);
    I2C_GenerateSTOP(I2C2,ENABLE);

    while(I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    Receive_Data = I2C_ReceiveData(I2C2);
    
    return Receive_Data;
}