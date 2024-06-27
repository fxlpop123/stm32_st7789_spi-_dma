/**
 * @file lv_port_indev_templ.c
 *
 */

 /*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev_template.h"
#include "../../lvgl.h"
#include "./BSP/KEY/key.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/



/* 键盘 */
static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

lv_indev_t * indev_keypad;      // 键盘


/**
 * @brief       初始化并注册输入设备
 * @param       无
 * @retval      无
 */
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    keypad_init();

    /* 注册键盘输入设备 */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

}


/**
 * @brief       初始化键盘
 * @param       无
 * @retval      无
 */
static void keypad_init(void)
{
    bsp_InitKey();
}

uint32_t g_last_key = 0;

/**
 * @brief       图形库的键盘读取回调函数
 * @param       indev_drv : 键盘设备
 *   @arg       data      : 输入设备数据结构体
 * @retval      无
 */
static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    /* 获取按键是否被按下，并保存键值 */
    uint32_t act_key = keypad_get_key();

    if(act_key != 0) 
    {
        data->state = LV_INDEV_STATE_PR;

        /* 将键值转换成 LVGL 的控制字符 */
        switch(act_key) 
        {
            case KEY_1_DOWN:
                act_key = LV_KEY_NEXT;
            break;
            
            case KEY_2_DOWN:
                act_key = LV_KEY_PREV;
            break;
            
            case KEY_3_DOWN:
                act_key = LV_KEY_ENTER;
            break;
        }
        g_last_key = act_key;
    } 
    else 
    {
        data->state = LV_INDEV_STATE_REL;
        g_last_key = 0;
    }
    data->key = g_last_key;
}

/**
 * @brief       获取当前正在按下的按键
 * @param       无
 * @retval      0 : 按键没有被按下
 */
static uint32_t keypad_get_key(void)
{
    return bsp_GetKey();
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
