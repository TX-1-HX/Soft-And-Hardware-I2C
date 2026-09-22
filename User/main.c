#include "stm32f10x.h"      
#include "OLED.h"
#include "MPU6050.h"
#include "I2C.h"
int main(void)
{
	OLED_Init();
	MPU6050_Init();
	uint8_t ack;
	OLED_ShowChar(1,1,'a');
	BaseConfig_Start();
	BaseConfig_SendByte(0XD0);
	ack = BaseConfig_ReceiveACK();
	BaseConfig_Stop();
	MPU6050_Init();

	uint8_t data;
	MPU6050_WriteRegister(0X6B,0X01);
	MPU6050_WriteRegister(0X19,0XAA);
	data = MPU6050_ReadRegister(0X19);

	OLED_ShowHexNum(3,1,data,2);


	OLED_ShowNum(2,1,ack,2);
	while(1)
	{

	}
}