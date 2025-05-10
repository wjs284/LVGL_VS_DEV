/**
 * @file zh_lv_title.h
 *
 */

#ifndef __ZH_LV_TITLE_H__
#define __ZH_LV_TITLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_ZH_TITLE != 0

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

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t zh_lv_title;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a title object
 * @param parent        pointer to an object, it will be the parent of the new title
 * @return              pointer to the created title
 */
lv_obj_t *Zh_Lv_Title_Create(lv_obj_t *parent, lv_coord_t height, const char *title_str, bool has_back_icon, bool has_timestamp, void *custom_cb);
/*=====================
 * Setter functions
 *====================*/



/*=====================
 * Getter functions
 *====================*/


/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ZH_TITLE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__ZH_LV_TITLE_H__*/
