#include "stm32f10x.h"      
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
	OLED_Init();
	MPU6050_Init();

	uint8_t data;
	MPU6050_WriteRegister(0X6B,0X01);
	MPU6050_WriteRegister(0X19,0XAA);
	data = MPU6050_ReadRegister(0X19);

	OLED_ShowHexNum(2,1,data,2);


	while(1)
	{

	}
}

