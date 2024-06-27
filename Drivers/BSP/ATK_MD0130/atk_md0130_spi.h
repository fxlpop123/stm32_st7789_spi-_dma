#ifndef __ATK_MD0130_SPI_H
#define __ATK_MD0130_SPI_H

#include "./SYSTEM/sys/sys.h"

#define 	USE_DMA			1

/* SPI�ӿڶ��� */
#define ATK_MD0130_SPI_INTERFACE                SPI2
#define ATK_MD0130_SPI_PRESCALER                SPI_BAUDRATEPRESCALER_8
#define ATK_MD0130_SPI_CLK_ENABLE()             do{ __HAL_RCC_SPI2_CLK_ENABLE(); }while(0)

/* ���Ŷ��� */
#define ATK_MD0130_SPI_SCK_GPIO_PORT            GPIOD
#define ATK_MD0130_SPI_SCK_GPIO_PIN             GPIO_PIN_3
#define ATK_MD0130_SPI_SCK_GPIO_AF              GPIO_AF5_SPI2
#define ATK_MD0130_SPI_SCK_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define ATK_MD0130_SPI_SDA_GPIO_PORT            GPIOB
#define ATK_MD0130_SPI_SDA_GPIO_PIN             GPIO_PIN_15
#define ATK_MD0130_SPI_SDA_GPIO_AF              GPIO_AF5_SPI2
#define ATK_MD0130_SPI_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* �������� */
void atk_md0130_spi_init(void);                         		/* ATK-MD0130ģ��SPI�ӿڳ�ʼ�� */ 				/* ATK-MD0130ģ��SPI�ӿڷ������� */
void atk_md0130_spi_send(uint8_t *buf, uint16_t len);    /* ATK-MD0130ģ��SPI�ӿڷ������� */

#endif
