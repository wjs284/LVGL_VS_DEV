/**
 * @file lvsf_baseobj.h
 * 
 */

#ifndef ZH_LV_BASEOBJ_H
#define ZH_LV_BASEOBJ_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZH_USE_BASEOBJ 1

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if ZH_USE_BASEOBJ != 0

#include "../../core/lv_obj.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    HIDDEN_RULE_ALWAYS_ON = INT32_MAX,
    HIDDEN_RULE_UNIT_MISMATCH = INT32_MAX - 1,
    HIDDEN_RULE_OUT_RANGE = INT32_MAX - 2,
    HIDDEN_RULE_INVALID = INT32_MAX - 3,
    HIDDEN_RULE_NULL_STATE = INT32_MAX - 4,
};
typedef int32_t baseobj_hidden_rule_t;

typedef int32_t (*lv_baseobj_refresh_cb)(struct _lv_obj_t * obj, uint16_t * id_tab, uint8_t id_num);

/*Data of baseobj*/
typedef struct {
    lv_obj_t obj;

    uint8_t     ori_align;      /*align to original pos*/
    uint8_t     data_type;      /*data type from database_type_t*/
    uint8_t     id_num;         /*Record the length of the id_tab*/
    uint16_t    bind_idx;       /*for data subscribe*/
    int32_t  ori_x;          /*The original x-coordinate*/
    int32_t  ori_y;          /*The original y-coordinate*/
    int32_t  ori_w;          /*The original width*/
    int32_t  ori_h;          /*The original height*/

    int32_t     hidden_rule;    /*Under what circumstances can it be hidden, baseobj_hidden_rule_t*/
    int32_t     value_min;      /*Range of bound data changes, Q24.8*/
    int32_t     value_max;      /*Range of bound data changes, Q24.8*/
    int32_t     scale_min;      /*scale, e.g: percent for label; angle for pointer*/
    int32_t     scale_max;      /*scale, e.g: percent for label; angle for pointer*/

    uint16_t  * id_tab;         /*for watchface tool*/
    void      * time;           /*record time*/
    lv_timer_t * timer;         /*refresh timer*/
    lv_baseobj_refresh_cb cb;   /*refresh callback*/
} lv_baseobj_t;

/*Base object class*/
extern const lv_obj_class_t lv_baseobj_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a base object
 * @param parent    pointer to an object, it will be the parent of the new base object
 * @return          pointer to the created base object
 */
lv_obj_t * lv_baseobj_create(lv_obj_t * parent);

/**
 * Align object to its original position
 * @param obj       pointer to a base object
 */
void lv_baseobj_align_to_ori_pos(lv_obj_t * obj);

// /**
//  * Bind data to base object
//  * @param obj       pointer to a base object
//  * @param id        data id
//  * @param cb        data subscription callback
//  */
// void lv_baseobj_bind_data(lv_obj_t * obj, uint16_t id, lv_obj_datasubs_cb_t cb);

/**
 * Create refresh timer for base object
 * @param obj       pointer to a base object
 * @param period    timer period in milliseconds
 * @param timer_cb  timer callback function
 */
void lv_baseobj_create_refresh_timer(lv_obj_t * obj, uint32_t period, lv_timer_cb_t timer_cb);

/**
 * Start refresh timer
 * @param obj       pointer to a base object
 */
void lv_baseobj_refresh_start(lv_obj_t * obj);

/**
 * Stop refresh timer
 * @param obj       pointer to a base object
 */
void lv_baseobj_refresh_stop(lv_obj_t * obj);

/**
 * Set original alignment
 * @param obj       pointer to a base object
 * @param ori_align alignment type
 */
void lv_baseobj_set_ori_align(lv_obj_t * obj, uint8_t ori_align);

/**
 * Set data type
 * @param obj       pointer to a base object
 * @param data_type data type
 */
void lv_baseobj_set_data_type(lv_obj_t * obj, uint8_t data_type);

/**
 * Set original size
 * @param obj       pointer to a base object
 * @param w         width
 * @param h         height
 */
void lv_baseobj_set_ori_size(lv_obj_t * obj, int32_t w, int32_t h);

/**
 * Set original position
 * @param obj       pointer to a base object
 * @param x         x coordinate
 * @param y         y coordinate
 */
void lv_baseobj_set_ori_pos(lv_obj_t * obj, int32_t x, int32_t y);

/**
 * Set hidden rule
 * @param obj       pointer to a base object
 * @param hidden_rule hidden rule
 */
void lv_baseobj_set_hidden_rule(lv_obj_t * obj, int32_t hidden_rule);

/**
 * Set value range
 * @param obj       pointer to a base object
 * @param min       minimum value
 * @param max       maximum value
 */
void lv_baseobj_set_range_value(lv_obj_t * obj, int32_t min, int32_t max);

/**
 * Set scale range
 * @param obj       pointer to a base object
 * @param min       minimum scale
 * @param max       maximum scale
 */
void lv_baseobj_set_range_scale(lv_obj_t * obj, int32_t min, int32_t max);

/**
 * Set source IDs
 * @param obj       pointer to a base object
 * @param source_id array of source IDs
 * @param num       number of source IDs
 */
void lv_baseobj_set_source_id(lv_obj_t * obj, uint16_t * source_id, uint8_t num);

/**
 * Set refresh callback
 * @param obj       pointer to a base object
 * @param cb        refresh callback function
 */
void lv_baseobj_set_refresh_cb(lv_obj_t * obj, lv_baseobj_refresh_cb cb);

/**
 * Get hidden rule
 * @param obj       pointer to a base object
 * @return          hidden rule
 */
int32_t lv_baseobj_get_hidden_rule(lv_obj_t * obj);

/**
 * Get original alignment
 * @param obj       pointer to a base object
 * @return          original alignment
 */
int32_t lv_baseobj_get_ori_align(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#endif /*ZH_USE_BASEOBJ*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*ZH_LV_BASEOBJ_H*/
