#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStrcture;
    GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStrcture.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_Init(GPIOB,&GPIO_InitStrcture);

    GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void MI2C_W_SCL(uint8_t value)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)value);
    Delay_us(10);

}

void MI2C_W_SDA(uint8_t value)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)value);
    Delay_us(10);
}

uint8_t MI2C_R_SDA(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
    return value;
}

void BaseConfig_Start(void)
{
    MI2C_W_SDA(1);
    MI2C_W_SCL(1);
    MI2C_W_SDA(0);
    MI2C_W_SCL(0);
}

void BaseConfig_Stop(void)
{
    MI2C_W_SDA(0);
    MI2C_W_SCL(0);
    MI2C_W_SCL(1);
    MI2C_W_SDA(1);
}

void BaseConfig_SendByte(uint8_t Byte)
{
    for(uint8_t i = 0; i<8; i++)
    {
        MI2C_W_SDA(Byte & (0X80>>i));
        MI2C_W_SCL(1);
        MI2C_W_SCL(0);
    }
}

uint8_t BaseConfig_ReceiveByte(void)
{
    uint8_t Byte = 0x00;
    MI2C_W_SDA(1);               //主机让出SDA控制权
    for(uint8_t i = 0; i<8; i++)
    {
        if(MI2C_R_SDA() == 1)
        {
            Byte = Byte|(0x80>>i);
        }
        MI2C_W_SCL(1);
        MI2C_W_SCL(0);
    }
    return Byte;
}

void BaseConfig_SendACK(uint8_t ACK)
{
    MI2C_W_SDA(ACK);
    MI2C_W_SCL(1);
    MI2C_W_SCL(0);
}

uint8_t BaseConfig_ReceiveACK(void)
{
    uint8_t ACK;
    MI2C_W_SDA(1);
    ACK = MI2C_R_SDA();
    MI2C_W_SCL(1);
    MI2C_W_SCL(0);
    return ACK;
}

