#include "stm32f10x.h"      
#include "OLED.h"
#include "MPU6050.h"
#include "HardwareI2C.h"

int main(void)
{
	OLED_Init();
	Hardware_I2C_Init();
	MPU6050_Hardware_Init();
	
	int16_t AX,AY,AZ,GX,GY,GZ;

	while(1)
	{
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		OLED_ShowSignedNum(1,1,AX,6);
		OLED_ShowSignedNum(2,1,AY,6);
		OLED_ShowSignedNum(3,1,AZ,6);
		OLED_ShowSignedNum(1,10,GX,6);
		OLED_ShowSignedNum(2,10,GY,6);
		OLED_ShowSignedNum(3,10,GZ,6);

	}
}

