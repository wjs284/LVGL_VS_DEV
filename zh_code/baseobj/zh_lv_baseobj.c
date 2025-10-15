/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

#if ZH_USE_BASEOBJ != 0

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS (&lv_baseobj_class)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_baseobj_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_baseobj_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_baseobj_event(const lv_obj_class_t* class_p, lv_event_t* e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_baseobj_class = {
    .constructor_cb = lv_baseobj_constructor,
    .destructor_cb = lv_baseobj_destructor,
    .event_cb = lv_baseobj_event,
    .width_def = LV_DPI_DEF * 2,
    .height_def = LV_DPI_DEF / 10,
    .instance_size = sizeof(lv_baseobj_t),
    .base_class = &lv_obj_class,
    .name = "baseobj",
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t* lv_baseobj_create(lv_obj_t* parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t* obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_baseobj_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->hidden_rule = HIDDEN_RULE_ALWAYS_ON;
    baseobj->ori_x = INT16_MAX;
    baseobj->ori_y = INT16_MAX;

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_baseobj_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);

    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    // TODO
    //  if (baseobj->bind_idx)
    //      lv_obj_data_unsubscribe(obj, baseobj->bind_idx);
    if (baseobj->id_tab)
        lv_free(baseobj->id_tab);
    if (baseobj->time)
        lv_free(baseobj->time);
    if (baseobj->timer)
        lv_timer_delete(baseobj->timer);
}

static void lv_baseobj_event(const lv_obj_class_t* class_p, lv_event_t* e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /*Call the ancestor's event handler*/
    res = lv_obj_event_base(MY_CLASS, e);
    if (res != LV_RESULT_OK)
        return;

    // lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t* obj = lv_event_get_current_target(e);
}

void lv_baseobj_align_to_ori_pos(lv_obj_t* obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;

    if (baseobj->ori_align == LV_ALIGN_CENTER)
        lv_obj_set_pos(obj, baseobj->ori_x - (lv_obj_get_width(obj) >> 1), baseobj->ori_y - (lv_obj_get_height(obj) >> 1));
    else if (baseobj->ori_align == LV_ALIGN_BOTTOM_LEFT)
        lv_obj_set_pos(obj, baseobj->ori_x, baseobj->ori_y - lv_obj_get_height(obj));
    else if (baseobj->ori_align == LV_ALIGN_LEFT_MID)
        lv_obj_set_pos(obj, baseobj->ori_x, baseobj->ori_y - (lv_obj_get_height(obj) >> 1));
    else if (baseobj->ori_align == LV_ALIGN_TOP_LEFT)
        lv_obj_set_pos(obj, baseobj->ori_x, baseobj->ori_y);
    else if (baseobj->ori_align == LV_ALIGN_TOP_MID)
        lv_obj_set_pos(obj, baseobj->ori_x - (lv_obj_get_width(obj) >> 1), baseobj->ori_y);
    else if (baseobj->ori_align == LV_ALIGN_BOTTOM_MID)
        lv_obj_set_pos(obj, baseobj->ori_x - (lv_obj_get_width(obj) >> 1), baseobj->ori_y - lv_obj_get_height(obj));
    else if (baseobj->ori_align == LV_ALIGN_BOTTOM_RIGHT)
        lv_obj_set_pos(obj, baseobj->ori_x - lv_obj_get_width(obj), baseobj->ori_y - lv_obj_get_height(obj));
    else if (baseobj->ori_align == LV_ALIGN_RIGHT_MID)
        lv_obj_set_pos(obj, baseobj->ori_x - lv_obj_get_width(obj), baseobj->ori_y - (lv_obj_get_height(obj) >> 1));
    else if (baseobj->ori_align == LV_ALIGN_TOP_RIGHT)
        lv_obj_set_pos(obj, baseobj->ori_x - lv_obj_get_width(obj), baseobj->ori_y);
}

// TODO
//  void lv_baseobj_bind_data(lv_obj_t* obj, uint16_t id, lv_obj_datasubs_cb_t cb)
//  {
//      LV_ASSERT_OBJ(obj, MY_CLASS);
//      lv_baseobj_t * baseobj = (lv_baseobj_t *)obj;

//     if (baseobj->bind_idx)
//         lv_obj_data_unsubscribe(obj, id);

//     lv_obj_data_subscribe(obj, id, cb);
// }

void lv_baseobj_create_refresh_task(lv_obj_t* obj, uint32_t period, lv_timer_cb_t task_cb)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    period = period == 0 ? 1000 : period;
    if (NULL == baseobj->timer)
        baseobj->timer = lv_timer_create(task_cb, period, obj);
    else
        lv_timer_set_period(baseobj->timer, period);

    lv_timer_set_cb(baseobj->timer, task_cb);
}

void lv_baseobj_refresh_start(lv_obj_t* obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    if (baseobj->timer) {
        lv_timer_resume(baseobj->timer);
        baseobj->timer->timer_cb(baseobj->timer);
    }
}

void lv_baseobj_refresh_stop(lv_obj_t* obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    if (baseobj->timer)
        lv_timer_pause(baseobj->timer);
}

void lv_baseobj_set_refresh_cb(lv_obj_t* obj, lv_baseobj_refresh_cb cb)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->cb = cb;
}

void lv_baseobj_set_source_id(lv_obj_t* obj, uint16_t* source_id, uint8_t num)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->id_num = num;
    baseobj->id_tab = lv_realloc(baseobj->id_tab, sizeof(uint16_t) * num);
    LV_ASSERT_NULL(baseobj->id_tab);
    lv_memcpy(baseobj->id_tab, source_id, sizeof(uint16_t) * num);
}

void lv_baseobj_set_ori_align(lv_obj_t* obj, uint8_t ori_align)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->ori_align = ori_align;
}

void lv_baseobj_set_data_type(lv_obj_t* obj, uint8_t data_type)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->data_type = data_type;
}

void lv_baseobj_set_ori_size(lv_obj_t* obj, int32_t w, int32_t h)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->ori_w = w;
    baseobj->ori_h = h;
}

void lv_baseobj_set_ori_pos(lv_obj_t* obj, int32_t x, int32_t y)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->ori_x = x;
    baseobj->ori_y = y;
}

void lv_baseobj_set_hidden_rule(lv_obj_t* obj, int32_t hidden_rule)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->hidden_rule = hidden_rule;
}

void lv_baseobj_set_range_value(lv_obj_t* obj, int32_t min, int32_t max)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->value_min = min;
    baseobj->value_max = max;
}

void lv_baseobj_set_range_scale(lv_obj_t* obj, int32_t min, int32_t max)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    baseobj->scale_min = min;
    baseobj->scale_max = max;
}

int32_t lv_baseobj_get_hidden_rule(lv_obj_t* obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    return baseobj->hidden_rule;
}

int32_t lv_baseobj_get_ori_align(lv_obj_t* obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)obj;
    LV_ASSERT(baseobj);

    return baseobj->ori_align;
}

#endif
