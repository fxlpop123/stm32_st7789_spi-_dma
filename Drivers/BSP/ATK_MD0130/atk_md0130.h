#ifndef __ATK_MD0130_H
#define __ATK_MD0130_H

#include "./SYSTEM/sys/sys.h"

#define USE_HORIZONTAL	2

#if (USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1)
/* 定义ATK-MD0130模块LCD尺寸 */
#define ATK_MD0130_LCD_WIDTH                240
#define ATK_MD0130_LCD_HEIGHT               135
#else
#define ATK_MD0130_LCD_WIDTH                240
#define ATK_MD0130_LCD_HEIGHT               135
#endif


/* 引脚定义 */
#define ATK_MD0130_PWR_GPIO_PORT            GPIOC
#define ATK_MD0130_PWR_GPIO_PIN             GPIO_PIN_13
#define ATK_MD0130_PWR_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)
#define ATK_MD0130_CS_GPIO_PORT             GPIOD
#define ATK_MD0130_CS_GPIO_PIN              GPIO_PIN_15
#define ATK_MD0130_CS_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)
#define ATK_MD0130_WR_GPIO_PORT             GPIOB
#define ATK_MD0130_WR_GPIO_PIN              GPIO_PIN_14
#define ATK_MD0130_WR_GPIO_CLK_ENABLE()     do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define ATK_MD0130_RST_GPIO_PORT            GPIOD
#define ATK_MD0130_RST_GPIO_PIN             GPIO_PIN_10
#define ATK_MD0130_RST_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)

/* IO操作 */
#define ATK_MD0130_PWR(x)                   do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MD0130_PWR_GPIO_PORT, ATK_MD0130_PWR_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(ATK_MD0130_PWR_GPIO_PORT, ATK_MD0130_PWR_GPIO_PIN, GPIO_PIN_RESET);   \
                                            }while(0)
#define ATK_MD0130_CS(x)                    do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MD0130_CS_GPIO_PORT, ATK_MD0130_CS_GPIO_PIN, GPIO_PIN_SET) :      \
                                                HAL_GPIO_WritePin(ATK_MD0130_CS_GPIO_PORT, ATK_MD0130_CS_GPIO_PIN, GPIO_PIN_RESET);     \
                                            }while(0)
#define ATK_MD0130_WR(x)                    do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MD0130_WR_GPIO_PORT, ATK_MD0130_WR_GPIO_PIN, GPIO_PIN_SET) :      \
                                                HAL_GPIO_WritePin(ATK_MD0130_WR_GPIO_PORT, ATK_MD0130_WR_GPIO_PIN, GPIO_PIN_RESET);     \
                                            }while(0)
#define ATK_MD0130_RST(x)                   do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MD0130_RST_GPIO_PORT, ATK_MD0130_RST_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(ATK_MD0130_RST_GPIO_PORT, ATK_MD0130_RST_GPIO_PIN, GPIO_PIN_RESET);   \
                                            }while(0)


/* 操作函数 */
void atk_md0130_init(void);                                                                                                                        
void atk_md0130_display_on(void);                                                                                                                     
void atk_md0130_display_off(void);                                                                                                                     
void atk_md0130_fill_block(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color);


#endif
