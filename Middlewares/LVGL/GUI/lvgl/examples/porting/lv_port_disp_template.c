/**
 * @file lv_port_disp_templ.c
 *
 */

 /*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_template.h"
#include "../../lvgl.h"
/* ����lcd����ͷ�ļ� */
#include "./BSP/ATK_MD0130/atk_md0130.h"
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES (240)   /* ��Ļ��� */
#define MY_DISP_VER_RES (135)   /* ��Ļ�߶� */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/* ��ʾ�豸��ʼ������ */
static void disp_init(void);

/* ��ʾ�豸ˢ�º��� */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief       ��ʼ����ע����ʾ�豸
 * @param       ��
 * @retval      ��
 */
void lv_port_disp_init(void)
{
    /*-------------------------
     * ��ʼ����ʾ�豸
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * ����һ����ͼ������
     *----------------------------*/

    /**
     * LVGL ��Ҫһ����������������С����
     * �����������������ݻ�ͨ����ʾ�豸�� `flush_cb`(��ʾ�豸ˢ�º���) ���Ƶ���ʾ�豸��
     * ����������Ĵ�С��Ҫ������ʾ�豸һ�еĴ�С
     *
     * ������3�л�������:
     * 1. ��������:
     *      LVGL �Ὣ��ʾ�豸�����ݻ��Ƶ����������д����ʾ�豸��
     *
     * 2. ˫������:
     *      LVGL �Ὣ��ʾ�豸�����ݻ��Ƶ�����һ����������������д����ʾ�豸��
     *      ��Ҫʹ�� DMA ��Ҫ��ʾ����ʾ�豸������д�뻺������
     *      �����ݴӵ�һ������������ʱ������ʹ LVGL �ܹ�����Ļ����һ���ֻ��Ƶ���һ����������
     *      ����ʹ����Ⱦ��ˢ�¿��Բ���ִ�С�
     *
     * 3. ȫ�ߴ�˫������
     *      ����������Ļ��С��ȫ�ߴ绺�������������� disp_drv.full_refresh = 1��
     *      ������LVGL��ʼ���� 'flush_cb' ����ʽ�ṩ������Ⱦ��Ļ����ֻ�����֡�������ĵ�ַ��
     */

    /* ��������ʾ��) */
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    static lv_color_t buf_1[MY_DISP_HOR_RES * 135];                                 /* ���û������Ĵ�С */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 135);     /* ��ʼ����ʾ������ */
 
    /*-----------------------------------
     * �� LVGL ��ע����ʾ�豸
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                  /* ��ʾ�豸�������� */
    lv_disp_drv_init(&disp_drv);                    /* ��ʼ��ΪĬ��ֵ */

    /* ����������ʾ�豸�ĺ���  */

    /* ������ʾ�豸�ķֱ���
     * ����Ϊ����������ԭ�ӵĶ����Ļ�������˶�̬��ȡ�ķ�ʽ��
     * ��ʵ����Ŀ�У�ͨ����ʹ�õ���Ļ��С�ǹ̶��ģ���˿���ֱ������Ϊ��Ļ�Ĵ�С */
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 135;

    /* �����������������ݸ��Ƶ���ʾ�豸 */
    disp_drv.flush_cb = disp_flush;

    /* ������ʾ������ */
    disp_drv.draw_buf = &draw_buf_dsc_1;

    /* ע����ʾ�豸 */
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief       ��ʼ����ʾ�豸�ͱ�Ҫ����Χ�豸
 * @param       ��
 * @retval      ��
 */
static void disp_init(void)
{
    /*You code here*/
    atk_md0130_init();
}

/**
 * @brief       ���ڲ�������������ˢ�µ���ʾ���ϵ��ض�����
 *   @note      ����ʹ�� DMA �����κ�Ӳ���ں�̨����ִ���������
 *              ���ǣ���Ҫ��ˢ����ɺ���ú��� 'lv_disp_flush_ready()'
 *
 * @param       disp_drv    : ��ʾ�豸
 *   @arg       area        : Ҫˢ�µ����򣬰����������εĶԽ�����
 *   @arg       color_p     : ��ɫ����
 *
 * @retval      ��
 */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{

	atk_md0130_fill_block(area->x1, area->y1, area->x2, area->y2, (uint16_t *)color_p);  
     /* ֪ͨͼ�ο⣬�Ѿ�ˢ������� */
    lv_disp_flush_ready(disp_drv);
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
