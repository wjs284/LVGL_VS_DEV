/*********************
 *      INCLUDES
 *********************/
#if ZH_USE_BASEBAR != 0

#include "zh_lv_basebar.h"

#define MY_CLASS (&lv_basebar_class)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_basebar_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_basebar_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_basebar_event(const lv_obj_class_t* class_p, lv_event_t* e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_bar_class = {
    .base_class = &lv_bar_class,
    .constructor_cb = lv_basebar_constructor,
    .destructor_cb = lv_basebar_destructor,
    .event_cb = lv_basebar_event,
    .width_def = LV_DPI_DEF * 2,
    .height_def = LV_DPI_DEF / 10,
    .instance_size = sizeof(lv_basebar_t),
    .base_class = &lv_obj_class,
    .name = "basebar",
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t* lv_basebar_create(lv_obj_t* parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t* obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_basebar_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_basebar_t* basebar = (lv_basebar_t*)obj;
    LV_ASSERT(basebar);

    basebar->min_idx = 0;
    basebar->max_idx = 0;
    basebar->value_idx = 0;
    basebar->attr_addr = NULL;

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_basebar_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);

    lv_basebar_t* basebar = (lv_basebar_t*)obj;
    LV_ASSERT(basebar);
}

static void lv_basebar_event(const lv_obj_class_t* class_p, lv_event_t* e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /*Call the ancestor's event handler*/
    res = lv_obj_event_base(MY_CLASS, e);
    if (res != LV_RESULT_OK)
        return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_current_target(e);
    if (code == LV_EVENT_DELETE) {
        LV_ASSERT_OBJ(obj, MY_CLASS);
        lv_basebar_t* basebar = (lv_basebar_t*)obj;
        LV_ASSERT(basebar);
        // if (basebar->value_idx)
        //     lv_obj_data_unsubscribe(bar, basebar->value_idx);
        // if (basebar->max_idx)
        //     lv_obj_data_unsubscribe(bar, basebar->max_idx);
        // if (basebar->min_idx)
        //     lv_obj_data_unsubscribe(bar, basebar->min_idx);
    }
}

void lv_basebar_bind_attr(lv_obj_t* bar, const lv_basebar_attr_t* attr)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);
    lv_obj_set_size(bar, attr->w, attr->h);
    lv_obj_set_pos_ext(bar, attr->x, attr->y);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(attr->indic_color));
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_BG, LV_STATE_DEFAULT, lv_color_hex(attr->bg_color));
    lv_bar_set_range(bar, attr->min, attr->max);
    lv_obj_set_drag_parent(bar, true);
    lv_obj_set_drag(bar, true);
    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    ext->attr_addr = attr;
}

static void lv_basebar_subsdata_cb(lv_obj_t* bar, lv_obj_datasubs_t* data)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);

    if (data->idx == ext->max_idx)
        lv_bar_set_range(bar, ext->ext.min_value, *(int32_t*)data->data);
    else if (data->idx == ext->min_idx)
        lv_bar_set_range(bar, *(int32_t*)data->data, ext->ext.max_value);
    else if (data->idx == ext->value_idx)
        lv_bar_set_value(bar, *(int32_t*)data->data, LV_ANIM_OFF);
}

void lv_basebar_bind_data(lv_obj_t* bar, uint16_t value_idx, uint16_t max_idx, uint16_t min_idx)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    LV_ASSERT(ext);

    if (value_idx) {
        ext->value_idx = value_idx;
        lv_obj_data_subscribe(bar, value_idx, lv_basebar_subsdata_cb);
    }
    if (max_idx) {
        ext->max_idx = max_idx;
        lv_obj_data_subscribe(bar, max_idx, lv_basebar_subsdata_cb);
    }
    if (min_idx) {
        ext->min_idx = min_idx;
        lv_obj_data_subscribe(bar, min_idx, lv_basebar_subsdata_cb);
    }
}

uint16_t lv_basebar_get_value_idx(lv_obj_t* bar)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    LV_ASSERT(ext);

    return ext->value_idx;
}

uint16_t lv_basebar_get_max_idx(lv_obj_t* bar)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    LV_ASSERT(ext);

    return ext->max_idx;
}

uint16_t lv_basebar_get_min_idx(lv_obj_t* bar)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    LV_ASSERT(ext);

    return ext->min_idx;
}

void lv_basebar_refresh(lv_obj_t* bar)
{
    LV_ASSERT_OBJ(bar, MY_CLASS);

    lv_basebar_ext_t* ext = lv_obj_get_ext_attr(bar);
    LV_ASSERT(ext);

    if (ext->max_idx) {
        widgets_data_refresh(ext->max_idx);
    }

    if (ext->min_idx) {
        widgets_data_refresh(ext->min_idx);
    }

    if (ext->value_idx) {
        widgets_data_refresh(ext->value_idx);
    }
}

#endif
