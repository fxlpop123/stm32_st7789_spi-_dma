#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MPU/mpu.h"

#include "./BSP/ATK_MD0130/atk_md0130.h"

#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demo_keypad_encoder.h"
#include "lv_demo_stress.h"
#include "lv_demo_benchmark.h"
#include "lv_demo_widgets.h"
#include "lvgl.h"





int main(void)
{
    sys_cache_enable();                 /* 打开L1-Cache */
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(100, 3, 2, 4); /* 设置时钟, 400Mhz */
	mpu_memory_protection();            /* 保护相关存储区域 */
    delay_init(400);                    /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化 */
	
	lv_init(); 							/* lvgl 系统初始化 */
	lv_port_disp_init(); 				/* lvgl 显示接口初始化,放在 lv_init()的后面 */
	lv_port_indev_init();               /* lvgl输入接口初始化,放在lv_init()的后面 */
	
	//lv_demo_stress();
	//lv_demo_benchmark();
	//lv_demo_widgets();
	//lv_demo_keypad_encoder();

	while(1)
	{
		lv_timer_handler(); 			/* LVGL 管理函数相当于 RTOS 触发任务调度函数 */
		delay_ms(5);
	}
}
