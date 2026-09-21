#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_Init(void);
void MPU6050_WriteRegister(uint8_t Address,uint8_t Data);
uint8_t MPU6050_ReadRegister(uint8_t Address);

#endif
