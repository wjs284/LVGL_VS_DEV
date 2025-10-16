/*********************
 *      INCLUDES
 *********************/
#ifndef ZH_LV_IMG_BAR_H
#define ZH_LV_IMG_BAR_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZH_USE_IMG_BAR 1

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if ZH_USE_IMG_BAR != 0

#include "../baseobj/zh_lv_baseobj.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
enum
{
    BAR_DIR_LEFT_TO_RIGHT = 0x0,
    BAR_DIR_RIGTH_TO_LEFT = 0x1,
    BAR_DIR_TOP_TO_BOTTOM = 0x10,
    BAR_DIR_BOTTOM_TO_TOP = 0x11,
};
typedef uint8_t lv_img_bar_dir_t;

typedef struct {
    lv_baseobj_t lv_baseobj;
    
    int32_t last_ret;
    lv_img_bar_dir_t dir;
    lv_obj_t *bar_img;
    lv_obj_t *indicator_img;
} lv_img_bar_t;

void lv_img_bar_refresh_task(lv_timer_t* timer);
lv_obj_t *lv_img_bar_create(lv_obj_t *parent);
void lv_img_bar_set_dir(lv_obj_t *img, lv_img_bar_dir_t dir);
void lv_img_bar_set_src(lv_obj_t *img, const void * src_img);
void lv_img_bar_set_indicator_src(lv_obj_t *img, const void * src_img);

/**********************
 *      MACROS
 **********************/

#endif /*ZH_USE_IMG_BAR*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ZH_LV_IMG_BAR_H */
