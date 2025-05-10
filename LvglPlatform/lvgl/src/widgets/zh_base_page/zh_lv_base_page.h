/**
 * @file zh_lv_base_page.h
 *
 */

#ifndef __ZH_LV_BASE_PAGE_H__
#define __ZH_LV_BASE_PAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_ZH_BASE_PAGE != 0

#include "../../core/lv_obj.h"
#include "../../misc/lv_anim.h"
#include "../label/lv_label.h"
#include "../../lv_api_map_v8.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    BASE_PAGE_DIR_HOR,
    BASE_PAGE_DIR_VER,
    BASE_PAGE_DIR_MAX,
} Zh_Base_Page_Dir_e;


LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t zh_lv_base_page;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a page object
 * @param parent        pointer to an object, it will be the parent of the new page
 * @return              pointer to the created page
 */
lv_obj_t *Zh_Lv_Base_Page_Create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h);

lv_obj_t *Zh_Lv_Base_Page_Child_Create(void *base_page, lv_coord_t height);

uint8_t Zh_Lv_Base_Page_Get_Child_Num(void *base_page);
uint8_t Zh_Lv_Base_Page_Add_Child(void *base_page, lv_obj_t *child);
void Zh_Lv_Base_Page_Clear_Child(void *base_page);
void Zh_Lv_Base_Page_Set_Gesture_Cb(void *base_page, void *left_gesture, void *right_gesture, void *up_gesture, void *down_gesture);
void Zh_Lv_Base_Page_Set_Dir(void *base_page, Zh_Base_Page_Dir_e dir);
/*=====================
 * Setter functions
 *====================*/



/*=====================
 * Getter functions
 *====================*/


/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ZH_BASE_PAGE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__ZH_LV_BASE_PAGE_H__*/
