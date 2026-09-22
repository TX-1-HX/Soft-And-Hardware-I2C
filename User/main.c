#include "stm32f10x.h"      
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
	OLED_Init();
	MPU6050_Init();



	int16_t AX,AY,AZ,GX,GY,GZ;
/*           对MPU6050实现滤波的功,均值滤波           */

	while(1)
	{
		for(uint8_t i = 0; i<20; i++)
		{
			static int32_t temp_ax, temp_ay, temp_az, temp_ga, temp_gy, temp_gz = 0;
			MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
			temp_ax += AX; temp_ay += AY; temp_az += AZ; temp_ga += GX; temp_gy += GY; temp_gz += GZ;
			if(i == 19)
			{
				AX = temp_ax/20; AY = temp_ay/20; AZ = temp_az/20; GX = temp_ga/20; GY = temp_gy/20; GZ = temp_gz/20;
				temp_ax = 0; temp_ay = 0; temp_az = 0; temp_ga = 0; temp_gy = 0; temp_gz = 0;
			}
		}
		OLED_ShowSignedNum(1,1,AX,6);
		OLED_ShowSignedNum(2,1,AY,6);
		OLED_ShowSignedNum(3,1,AZ,6);
		OLED_ShowSignedNum(1,10,GX,6);
		OLED_ShowSignedNum(2,10,GY,6);
		OLED_ShowSignedNum(3,10,GZ,6);

	}
}

