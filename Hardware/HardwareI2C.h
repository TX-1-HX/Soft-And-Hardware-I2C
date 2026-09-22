#ifndef __HARDWAREI2C_H
#define __HARDWAREI2C_H

void Hardware_I2C_Init(void);
void HardwareI2C_WriteRegister(uint8_t regiseter,uint8_t data);
uint8_t HardwareI2C_ReceiveRegister(uint8_t regiseter);

#endif

