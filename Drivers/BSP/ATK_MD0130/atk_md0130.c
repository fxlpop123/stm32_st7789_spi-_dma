#include "./BSP/ATK_MD0130/atk_md0130.h"
#include "./BSP/ATK_MD0130/atk_md0130_spi.h"
#include "./SYSTEM/delay/delay.h"

/* 定义ATK-MD0130模块LCD显存 */
#define ATK_MD0130_LCD_BUF_SIZE (ATK_MD0130_LCD_WIDTH * ATK_MD0130_LCD_HEIGHT)

uint16_t g_atk_md0130_lcd_buf[ATK_MD0130_LCD_BUF_SIZE] = {0};
extern SPI_HandleTypeDef g_spi_handle;
extern __IO uint8_t ucStatues;
/**
 * @brief       往ATK-MD0130模块写命令
 * @param       无
 * @retval      无
 */
static void atk_md0130_write_cmd(uint8_t cmd)
{
    ATK_MD0130_WR(0);
    atk_md0130_spi_send(&cmd, sizeof(uint8_t));
}

/**
 * @brief       往ATK-MD0130模块写数据
 * @param       无
 * @retval      无
 */
static void atk_md0130_write_dat(uint8_t dat)
{
    ATK_MD0130_WR(1);
    atk_md0130_spi_send(&dat, sizeof(uint8_t));
}

/**
 * @brief       往ATK-MD0130模块写16bit数据
 * @param       无
 * @retval      无
 */
static void atk_md0130_write_dat_16b(uint16_t dat)
{
    uint8_t buf[2] = {0};
	
	buf[0] = dat >> 8;
	buf[1] = dat;
	
    ATK_MD0130_WR(1);
	atk_md0130_spi_send(buf, 2);
}

/**
 * @brief       ATK-MD0130模块硬件初始化
 * @param       无
 * @retval      无
 */
static void atk_md0130_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
    ATK_MD0130_PWR_GPIO_CLK_ENABLE();
    ATK_MD0130_CS_GPIO_CLK_ENABLE();
    ATK_MD0130_WR_GPIO_CLK_ENABLE();
    ATK_MD0130_RST_GPIO_CLK_ENABLE();
    
    /* 初始化PWR引脚 */
    gpio_init_struct.Pin    = ATK_MD0130_PWR_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0130_PWR_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化CS引脚 */
    gpio_init_struct.Pin    = ATK_MD0130_CS_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0130_CS_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化WR引脚 */
    gpio_init_struct.Pin    = ATK_MD0130_WR_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0130_WR_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化RST引脚 */
    gpio_init_struct.Pin    = ATK_MD0130_RST_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0130_RST_GPIO_PORT, &gpio_init_struct);
    
    ATK_MD0130_CS(0);
}

/**
 * @brief       ATK-MD0130模块硬件复位
 * @param       无
 * @retval      无
 */
static void atk_md0130_hw_reset(void)
{
    ATK_MD0130_RST(0);
    delay_ms(10);
    ATK_MD0130_RST(1);
    delay_ms(120);
}

/**
 * @brief       ATK-MD0130模块寄存器初始化
 * @param       无
 * @retval      无
 */
static void atk_md0130_reg_init(void)
{
    /* Sleep Out */
    atk_md0130_write_cmd(0x11);
    delay_ms(120);
    /* Memory Data Access Control */
	atk_md0130_write_cmd(0x36);
	
	if(USE_HORIZONTAL == 0)
		atk_md0130_write_dat(0x00);
	else if(USE_HORIZONTAL == 1)
		atk_md0130_write_dat(0xC0);
	else if(USE_HORIZONTAL == 2)
		atk_md0130_write_dat(0x70);
	else
		atk_md0130_write_dat(0xA0);
    /* RGB 5-6-5-bit  */
    atk_md0130_write_cmd(0x3A);
    atk_md0130_write_dat(0x65);
    /* Porch Setting */
    atk_md0130_write_cmd(0xB2);
    atk_md0130_write_dat(0x0C);
    atk_md0130_write_dat(0x0C);
    atk_md0130_write_dat(0x00);
    atk_md0130_write_dat(0x33);
    atk_md0130_write_dat(0x33);
    /*  Gate Control */
    atk_md0130_write_cmd(0xB7);
    atk_md0130_write_dat(0x72);
    /* VCOM Setting */
    atk_md0130_write_cmd(0xBB);
    atk_md0130_write_dat(0x3D);
    /* LCM Control */
    atk_md0130_write_cmd(0xC0);
    atk_md0130_write_dat(0x2C);
    /* VDV and VRH Command Enable */
    atk_md0130_write_cmd(0xC2);
    atk_md0130_write_dat(0x01);
    /* VRH Set */
    atk_md0130_write_cmd(0xC3);
    atk_md0130_write_dat(0x19);
    /* VDV Set */
    atk_md0130_write_cmd(0xC4);
    atk_md0130_write_dat(0x20);
    /* Frame Rate Control in Normal Mode */
    atk_md0130_write_cmd(0xC6);
    atk_md0130_write_dat(0x0F);
    /* Power Control 1 */
    atk_md0130_write_cmd(0xD0);
    atk_md0130_write_dat(0xA4);
    atk_md0130_write_dat(0xA1);
    /* Positive Voltage Gamma Control */
    atk_md0130_write_cmd(0xE0);
    atk_md0130_write_dat(0xD0);
    atk_md0130_write_dat(0x04);
    atk_md0130_write_dat(0x0D);
    atk_md0130_write_dat(0x11);
    atk_md0130_write_dat(0x13);
    atk_md0130_write_dat(0x2B);
    atk_md0130_write_dat(0x3F);
    atk_md0130_write_dat(0x54);
    atk_md0130_write_dat(0x4C);
    atk_md0130_write_dat(0x18);
    atk_md0130_write_dat(0x0D);
    atk_md0130_write_dat(0x0B);
    atk_md0130_write_dat(0x1F);
    atk_md0130_write_dat(0x23);
    /* Negative Voltage Gamma Control */
    atk_md0130_write_cmd(0xE1);
    atk_md0130_write_dat(0xD0);
    atk_md0130_write_dat(0x04);
    atk_md0130_write_dat(0x0C);
    atk_md0130_write_dat(0x11);
    atk_md0130_write_dat(0x13);
    atk_md0130_write_dat(0x2C);
    atk_md0130_write_dat(0x3F);
    atk_md0130_write_dat(0x44);
    atk_md0130_write_dat(0x51);
    atk_md0130_write_dat(0x2F);
    atk_md0130_write_dat(0x1F);
    atk_md0130_write_dat(0x1F);
    atk_md0130_write_dat(0x20);
    atk_md0130_write_dat(0x23);
    /* Display Inversion On */
    atk_md0130_write_cmd(0x21);
    atk_md0130_write_cmd(0x29);
}

/**
 * @brief       设置ATK-MD0130模块行列地址
 * @param       xs: 列起始地址
 *              ys: 行起始地址
 *              xe: 列结束地址
 *              ye: 行结束地址
 * @retval      无
 */
void atk_md0130_set_address(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    if(USE_HORIZONTAL == 0)
	{
		atk_md0130_write_cmd(0x2A);
		atk_md0130_write_dat_16b(xs + 52);
		atk_md0130_write_dat_16b(xe + 52);
		atk_md0130_write_cmd(0x2B);
		atk_md0130_write_dat_16b(ys + 40);
		atk_md0130_write_dat_16b(ye + 40);
		atk_md0130_write_cmd(0x2C);
	}
	else if(USE_HORIZONTAL == 1)
	{
		atk_md0130_write_cmd(0x2A);
		atk_md0130_write_dat_16b(xs + 53);
		atk_md0130_write_dat_16b(xe + 53);
		atk_md0130_write_cmd(0x2B);
		atk_md0130_write_dat_16b(ys + 40);
		atk_md0130_write_dat_16b(ye + 40);
		atk_md0130_write_cmd(0x2C);
	}
	else if(USE_HORIZONTAL == 2)
	{
		atk_md0130_write_cmd(0x2A);
		atk_md0130_write_dat_16b(xs + 40);
		atk_md0130_write_dat_16b(xe + 40);
		atk_md0130_write_cmd(0x2B);
		atk_md0130_write_dat_16b(ys + 53);
		atk_md0130_write_dat_16b(ye + 53);
		atk_md0130_write_cmd(0x2C);
	}
	else
	{
		atk_md0130_write_cmd(0x2A);
		atk_md0130_write_dat_16b(xs + 40);
		atk_md0130_write_dat_16b(xe + 40);
		atk_md0130_write_cmd(0x2B);
		atk_md0130_write_dat_16b(ys + 52);
		atk_md0130_write_dat_16b(ye + 52);
		atk_md0130_write_cmd(0x2C);
	}
}

/**
 * @brief       ATK-MD0130模块初始化
 * @param       无
 * @retval      无
 */
void atk_md0130_init(void)
{
    atk_md0130_hw_init();
    atk_md0130_hw_reset();
    atk_md0130_spi_init();
    atk_md0130_reg_init();
    atk_md0130_display_on();
}

/**
 * @brief       开启ATK-MD0130模块LCD背光
 * @param       无
 * @retval      无
 */
void atk_md0130_display_on(void)
{
    ATK_MD0130_PWR(1);
}

/**
 * @brief       关闭ATK-MD0130模块LCD背光
 * @param       无
 * @retval      无
 */
void atk_md0130_display_off(void)
{
    ATK_MD0130_PWR(0);
}

/**
 * @brief       ATK-MD0130模块LCD区域填充
 * @param       xs   : 区域起始X坐标
 *              ys   : 区域起始Y坐标
 *              xe   : 区域终止X坐标
 *              ye   : 区域终止Y坐标
 *              color: 区域填充颜色
 * @retval      无
 */
void atk_md0130_fill_block(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color)
{
    uint32_t area_size;
    uint32_t area_remain = 0;
    uint16_t buf_index;
    
    area_size = (xe - xs + 1) * (ye - ys + 1);
    if (area_size > ATK_MD0130_LCD_BUF_SIZE)
    {
        area_remain = area_size - ATK_MD0130_LCD_BUF_SIZE;
        area_size = ATK_MD0130_LCD_BUF_SIZE;
    }
    atk_md0130_set_address(xs, ys, xe, ye);
    ATK_MD0130_WR(1);
	
	g_spi_handle.Init.DataSize = SPI_DATASIZE_16BIT;
	
	HAL_SPI_Init(&g_spi_handle);
	
    while (1)
    {
        for (buf_index=0; buf_index < area_size; buf_index++)
        {
            g_atk_md0130_lcd_buf[buf_index] = *(color++);	
        } 
#if USE_DMA		
		ucStatues = 0;
		HAL_SPI_Transmit_DMA(&g_spi_handle, (uint8_t *)g_atk_md0130_lcd_buf, area_size);
		while(ucStatues == 0){};
#else
		HAL_SPI_Transmit(&g_spi_handle, (uint8_t *)g_atk_md0130_lcd_buf, area_size, HAL_MAX_DELAY);
#endif
        if (area_remain == 0)
        {
            break;
        }
        
        if (area_remain > ATK_MD0130_LCD_BUF_SIZE)
        {
            area_remain = area_remain - ATK_MD0130_LCD_BUF_SIZE;
        }
        else
        {
            area_size = area_remain;
            area_remain = 0;
        }
    }
	g_spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&g_spi_handle);
}

