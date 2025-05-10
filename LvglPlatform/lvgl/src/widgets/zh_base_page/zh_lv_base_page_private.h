/**
 * @file zh_lv_base_page_private.h
 *
 */

#ifndef __ZH_LV_BASE_PAGE_PRIVATE_H__
#define __ZH_LV_BASE_PAGE_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../core/lv_obj_private.h"
#include "zh_lv_base_page.h"

#if LV_USE_ZH_BASE_PAGE != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef bool (*Zh_Lv_Gesture_Cb_t)(lv_event_t *e);

typedef struct Zh_Lv_Base_Page_Child_Node
{
    lv_obj_t *child;
    struct Zh_Lv_Base_Page_Child_Node *next;
} Zh_Lv_Base_Page_Child_Node_t;

typedef struct
{
    lv_obj_t obj;
    Zh_Base_Page_Dir_e dir;
    Zh_Lv_Base_Page_Child_Node_t *child_head;
    lv_style_t scrollbar_style;
    lv_point_t last_pos;
    Zh_Lv_Gesture_Cb_t gesture_cb[4];
    lv_anim_t anim;
} Zh_Lv_Base_Page_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_ZH_BASE_PAGE != 0 */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__ZH_LV_BASE_PAGE_PRIVATE_H__*/
