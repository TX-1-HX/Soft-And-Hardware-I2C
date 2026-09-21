#ifndef __I2C_H
#define __I2C_H

void MI2C_Init(void);
void MI2C_W_SCL(uint8_t value);
void MI2C_W_SDA(uint8_t value);
uint8_t MI2C_R_SDA(void);
void BaseConfig_Start(void);
void BaseConfig_Stop(void);
void BaseConfig_SendByte(uint8_t Byte);
uint8_t BaseConfig_ReceiveByte(void);
void BaseConfig_SendACK(uint8_t ACK);
uint8_t BaseConfig_ReceiveACK(void);

#endif
