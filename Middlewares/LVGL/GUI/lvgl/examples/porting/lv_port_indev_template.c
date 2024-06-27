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



/* ���� */
static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

lv_indev_t * indev_keypad;      // ����


/**
 * @brief       ��ʼ����ע�������豸
 * @param       ��
 * @retval      ��
 */
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    keypad_init();

    /* ע����������豸 */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);

}


/**
 * @brief       ��ʼ������
 * @param       ��
 * @retval      ��
 */
static void keypad_init(void)
{
    bsp_InitKey();
}

uint32_t g_last_key = 0;

/**
 * @brief       ͼ�ο�ļ��̶�ȡ�ص�����
 * @param       indev_drv : �����豸
 *   @arg       data      : �����豸���ݽṹ��
 * @retval      ��
 */
static void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    /* ��ȡ�����Ƿ񱻰��£��������ֵ */
    uint32_t act_key = keypad_get_key();

    if(act_key != 0) 
    {
        data->state = LV_INDEV_STATE_PR;

        /* ����ֵת���� LVGL �Ŀ����ַ� */
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
 * @brief       ��ȡ��ǰ���ڰ��µİ���
 * @param       ��
 * @retval      0 : ����û�б�����
 */
static uint32_t keypad_get_key(void)
{
    return bsp_GetKey();
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
