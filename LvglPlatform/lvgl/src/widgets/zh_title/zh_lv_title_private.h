/**
 * @file zh_lv_title_private.h
 *
 */

#ifndef __ZH_LV_TITLE_PRIVATE_H__
#define __ZH_LV_TITLE_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../core/lv_obj_private.h"
#include "zh_lv_title.h"

#if LV_USE_ZH_TITLE != 0

/*********************
 *      DEFINES
 *********************/
LV_IMAGE_DECLARE(test_img_lvgl_logo_pngw233);
/**********************
 *      TYPEDEFS
 **********************/
typedef void (*Zh_Lv_Title_Custom_Cb_t)(lv_event_t *e);

typedef struct
{
    lv_obj_t obj;
    lv_obj_t *back_icon;
    lv_obj_t *desc_label;
    lv_obj_t *time_label;
    Zh_Lv_Title_Custom_Cb_t custom_cb;
} Zh_Lv_Title_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_ZH_TITLE != 0 */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__ZH_LV_TITLE_PRIVATE_H__*/
