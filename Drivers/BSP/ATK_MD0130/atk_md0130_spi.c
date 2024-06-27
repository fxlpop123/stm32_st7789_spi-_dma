#include "./BSP/ATK_MD0130/atk_md0130_spi.h"

SPI_HandleTypeDef g_spi_handle = {0};
DMA_HandleTypeDef hdma_spi2_tx = {0};

__IO uint8_t ucStatues = 10;

/**
 * @brief       ATK-MD0130模块SPI接口初始化
 * @param       无
 * @retval      无
 */
void atk_md0130_spi_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
    ATK_MD0130_SPI_CLK_ENABLE();
    ATK_MD0130_SPI_SCK_GPIO_CLK_ENABLE();
    ATK_MD0130_SPI_SDA_GPIO_CLK_ENABLE();
    
    /* 初始化SCK引脚 */
    gpio_init_struct.Pin        = ATK_MD0130_SPI_SCK_GPIO_PIN;
    gpio_init_struct.Mode       = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull       = GPIO_PULLUP;
    gpio_init_struct.Speed      = GPIO_SPEED_LOW;
    gpio_init_struct.Alternate  = ATK_MD0130_SPI_SCK_GPIO_AF;
    HAL_GPIO_Init(ATK_MD0130_SPI_SCK_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化SDA引脚 */
    gpio_init_struct.Pin        = ATK_MD0130_SPI_SDA_GPIO_PIN;
    gpio_init_struct.Mode       = GPIO_MODE_AF_PP;
    gpio_init_struct.Pull       = GPIO_PULLUP;
    gpio_init_struct.Speed      = GPIO_SPEED_LOW;
    gpio_init_struct.Alternate  = ATK_MD0130_SPI_SDA_GPIO_AF;
    HAL_GPIO_Init(ATK_MD0130_SPI_SDA_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化SPI */
    g_spi_handle.Instance               = ATK_MD0130_SPI_INTERFACE;
    g_spi_handle.Init.Mode              = SPI_MODE_MASTER;
    g_spi_handle.Init.Direction         = SPI_DIRECTION_2LINES;
    g_spi_handle.Init.DataSize          = SPI_DATASIZE_8BIT;
    g_spi_handle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
    g_spi_handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
    g_spi_handle.Init.NSS               = SPI_NSS_SOFT;
    g_spi_handle.Init.BaudRatePrescaler = ATK_MD0130_SPI_PRESCALER;
    g_spi_handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    g_spi_handle.Init.TIMode            = SPI_TIMODE_DISABLE;
    g_spi_handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    g_spi_handle.Init.CRCPolynomial     = 10;
	

#if USE_DMA

	__HAL_RCC_DMA2_CLK_ENABLE();
	
	hdma_spi2_tx.Instance 					= DMA2_Stream3;
    hdma_spi2_tx.Init.Request 				= DMA_REQUEST_SPI2_TX;
    hdma_spi2_tx.Init.Direction 			= DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc 			= DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc 				= DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment 	= DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.MemDataAlignment 		= DMA_MDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.Mode 					= DMA_NORMAL;
    hdma_spi2_tx.Init.Priority 				= DMA_PRIORITY_MEDIUM;
    hdma_spi2_tx.Init.FIFOMode 				= DMA_FIFOMODE_ENABLE;
    hdma_spi2_tx.Init.FIFOThreshold 		= DMA_FIFO_THRESHOLD_FULL;
    hdma_spi2_tx.Init.MemBurst 				= DMA_MBURST_SINGLE;
    hdma_spi2_tx.Init.PeriphBurst 			= DMA_PBURST_SINGLE;
	
	HAL_DMA_Init(&hdma_spi2_tx);
	
	__HAL_LINKDMA(&g_spi_handle, hdmatx, hdma_spi2_tx);
	
	HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	
	HAL_NVIC_SetPriority(SPI2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
	
#endif
	
    HAL_SPI_Init(&g_spi_handle);
}

/**
 * @brief       ATK-MD0130模块SPI接口发送数据
 * @param       无
 * @retval      无
 */
void atk_md0130_spi_send(uint8_t *buf, uint16_t len)
{
	HAL_SPI_Transmit(&g_spi_handle, buf, len, HAL_MAX_DELAY);
}


#if USE_DMA

/**
  * @brief Tx Transfer completed callback.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance == SPI2) ucStatues = 1;
}

/**
  * @brief This function handles SPI2 global interrupt.
  */
void SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&g_spi_handle);
}

/**
  * @brief This function handles DMA2 stream3 global interrupt.
  */
void DMA2_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi2_tx);
}
#endif 
