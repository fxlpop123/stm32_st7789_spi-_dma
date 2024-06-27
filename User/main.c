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
    sys_cache_enable();                 /* ��L1-Cache */
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(100, 3, 2, 4); /* ����ʱ��, 400Mhz */
	mpu_memory_protection();            /* ������ش洢���� */
    delay_init(400);                    /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ�� */
	
	lv_init(); 							/* lvgl ϵͳ��ʼ�� */
	lv_port_disp_init(); 				/* lvgl ��ʾ�ӿڳ�ʼ��,���� lv_init()�ĺ��� */
	lv_port_indev_init();               /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */
	
	//lv_demo_stress();
	//lv_demo_benchmark();
	//lv_demo_widgets();
	//lv_demo_keypad_encoder();

	while(1)
	{
		lv_timer_handler(); 			/* LVGL �������൱�� RTOS ����������Ⱥ��� */
		delay_ms(5);
	}
}
