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
/* 导入lcd驱动头文件 */
#include "./BSP/ATK_MD0130/atk_md0130.h"
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES (240)   /* 屏幕宽度 */
#define MY_DISP_VER_RES (135)   /* 屏幕高度 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/* 显示设备初始化函数 */
static void disp_init(void);

/* 显示设备刷新函数 */
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
 * @brief       初始化并注册显示设备
 * @param       无
 * @retval      无
 */
void lv_port_disp_init(void)
{
    /*-------------------------
     * 初始化显示设备
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * 创建一个绘图缓冲区
     *----------------------------*/

    /**
     * LVGL 需要一个缓冲区用来绘制小部件
     * 随后，这个缓冲区的内容会通过显示设备的 `flush_cb`(显示设备刷新函数) 复制到显示设备上
     * 这个缓冲区的大小需要大于显示设备一行的大小
     *
     * 这里有3中缓冲配置:
     * 1. 单缓冲区:
     *      LVGL 会将显示设备的内容绘制到这里，并将他写入显示设备。
     *
     * 2. 双缓冲区:
     *      LVGL 会将显示设备的内容绘制到其中一个缓冲区，并将他写入显示设备。
     *      需要使用 DMA 将要显示在显示设备的内容写入缓冲区。
     *      当数据从第一个缓冲区发送时，它将使 LVGL 能够将屏幕的下一部分绘制到另一个缓冲区。
     *      这样使得渲染和刷新可以并行执行。
     *
     * 3. 全尺寸双缓冲区
     *      设置两个屏幕大小的全尺寸缓冲区，并且设置 disp_drv.full_refresh = 1。
     *      这样，LVGL将始终以 'flush_cb' 的形式提供整个渲染屏幕，您只需更改帧缓冲区的地址。
     */

    /* 单缓冲区示例) */
    static lv_disp_draw_buf_t draw_buf_dsc_1;
    static lv_color_t buf_1[MY_DISP_HOR_RES * 135];                                 /* 设置缓冲区的大小 */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 135);     /* 初始化显示缓冲区 */
 
    /*-----------------------------------
     * 在 LVGL 中注册显示设备
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                  /* 显示设备的描述符 */
    lv_disp_drv_init(&disp_drv);                    /* 初始化为默认值 */

    /* 建立访问显示设备的函数  */

    /* 设置显示设备的分辨率
     * 这里为了适配正点原子的多款屏幕，采用了动态获取的方式，
     * 在实际项目中，通常所使用的屏幕大小是固定的，因此可以直接设置为屏幕的大小 */
    disp_drv.hor_res = 240;
    disp_drv.ver_res = 135;

    /* 用来将缓冲区的内容复制到显示设备 */
    disp_drv.flush_cb = disp_flush;

    /* 设置显示缓冲区 */
    disp_drv.draw_buf = &draw_buf_dsc_1;

    /* 注册显示设备 */
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief       初始化显示设备和必要的外围设备
 * @param       无
 * @retval      无
 */
static void disp_init(void)
{
    /*You code here*/
    atk_md0130_init();
}

/**
 * @brief       将内部缓冲区的内容刷新到显示屏上的特定区域
 *   @note      可以使用 DMA 或者任何硬件在后台加速执行这个操作
 *              但是，需要在刷新完成后调用函数 'lv_disp_flush_ready()'
 *
 * @param       disp_drv    : 显示设备
 *   @arg       area        : 要刷新的区域，包含了填充矩形的对角坐标
 *   @arg       color_p     : 颜色数组
 *
 * @retval      无
 */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{

	atk_md0130_fill_block(area->x1, area->y1, area->x2, area->y2, (uint16_t *)color_p);  
     /* 通知图形库，已经刷新完毕了 */
    lv_disp_flush_ready(disp_drv);
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
