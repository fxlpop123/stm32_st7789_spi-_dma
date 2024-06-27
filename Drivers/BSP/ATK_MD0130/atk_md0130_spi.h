#ifndef __ATK_MD0130_SPI_H
#define __ATK_MD0130_SPI_H

#include "./SYSTEM/sys/sys.h"

#define 	USE_DMA			1

/* SPI接口定义 */
#define ATK_MD0130_SPI_INTERFACE                SPI2
#define ATK_MD0130_SPI_PRESCALER                SPI_BAUDRATEPRESCALER_8
#define ATK_MD0130_SPI_CLK_ENABLE()             do{ __HAL_RCC_SPI2_CLK_ENABLE(); }while(0)

/* 引脚定义 */
#define ATK_MD0130_SPI_SCK_GPIO_PORT            GPIOD
#define ATK_MD0130_SPI_SCK_GPIO_PIN             GPIO_PIN_3
#define ATK_MD0130_SPI_SCK_GPIO_AF              GPIO_AF5_SPI2
#define ATK_MD0130_SPI_SCK_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define ATK_MD0130_SPI_SDA_GPIO_PORT            GPIOB
#define ATK_MD0130_SPI_SDA_GPIO_PIN             GPIO_PIN_15
#define ATK_MD0130_SPI_SDA_GPIO_AF              GPIO_AF5_SPI2
#define ATK_MD0130_SPI_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* 操作函数 */
void atk_md0130_spi_init(void);                         		/* ATK-MD0130模块SPI接口初始化 */ 				/* ATK-MD0130模块SPI接口发送数据 */
void atk_md0130_spi_send(uint8_t *buf, uint16_t len);    /* ATK-MD0130模块SPI接口发送数据 */

#endif
