#include "stm32f10x.h"      
#include "OLED.h"
#include "I2C.h"

int main(void)
{
	OLED_Init();
	MI2C_Init();
	uint8_t ack;
	OLED_ShowChar(1,1,'a');
	BaseConfig_Start();
	BaseConfig_SendByte(0XD0);
	ack = BaseConfig_ReceiveACK();
	BaseConfig_Stop();

	OLED_ShowNum(2,1,ack,2);
	while(1)
	{

	}
}

