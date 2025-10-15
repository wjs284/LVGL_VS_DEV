/*********************
 *      INCLUDES
 *********************/
#ifndef ZH_LV_BASEBAR_H
#define ZH_LV_BASEBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZH_USE_BASEBAR 1

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if ZH_USE_BASEBAR != 0

#include "../bar/lv_bar.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct
{
    const char id[16];
    lv_coord_t x;
    lv_coord_t y;
    lv_coord_t w;
    lv_coord_t h;
    uint32_t bg_color;
    uint32_t indic_color;
    int16_t min;
    int16_t max;
} lv_basebar_attr_t;

typedef struct {
    lv_bar_t bar;

    uint16_t value_idx;
    uint16_t max_idx;
    uint16_t min_idx;
    const lv_basebar_attr_t* attr_addr;
} lv_basebar_t;

lv_obj_t* lv_basebar_create(lv_obj_t* par, const lv_obj_t* copy);
void lv_basebar_bind_attr(lv_obj_t* bar, const lv_basebar_attr_t* attr);

void lv_basebar_bind_data(lv_obj_t* bar, uint16_t value_idx, uint16_t max_idx, uint16_t min_idx);

uint16_t lv_basebar_get_value_idx(lv_obj_t* bar);
uint16_t lv_basebar_get_max_idx(lv_obj_t* bar);
uint16_t lv_basebar_get_min_idx(lv_obj_t* bar);

void lv_basebar_refresh(lv_obj_t* bar);

/**********************
 *      MACROS
 **********************/

#endif /*ZH_USE_BASEBAR*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ZH_LV_BASEBAR_H */
