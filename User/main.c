#include "stm32f10x.h"      
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
	OLED_Init();
	MPU6050_Init();

	int16_t AX,AY,AZ,GX,GY,GZ;

	while(1)
	{
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		OLED_ShowNum(1,1,AX,4);
		OLED_ShowNum(2,1,AY,4);
		OLED_ShowNum(3,1,AZ,4);
		OLED_ShowNum(1,6,GX,4);
		OLED_ShowNum(2,6,GY,4);
		OLED_ShowNum(3,6,GZ,4);

	}
}

