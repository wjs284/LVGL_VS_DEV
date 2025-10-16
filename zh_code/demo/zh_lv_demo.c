/*********************
 *      INCLUDES
 *********************/
#if ZH_USE_IMG_BAR != 0

#include "zh_lv_img_bar.h"

#define MY_CLASS (&lv_img_bar_class)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_img_bar_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_img_bar_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj);
static void lv_img_bar_event(const lv_obj_class_t* class_p, lv_event_t* e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_bar_class = {
    .base_class = &lv_bar_class,
    .constructor_cb = lv_img_bar_constructor,
    .destructor_cb = lv_img_bar_destructor,
    .event_cb = lv_img_bar_event,
    .width_def = LV_DPI_DEF * 2,
    .height_def = LV_DPI_DEF / 10,
    .instance_size = sizeof(lv_img_bar_t),
    .base_class = &lv_obj_class,
    .name = "img_bar",
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t* lv_img_bar_create(lv_obj_t* parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t* obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_img_bar_constructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_img_bar_t* img_bar = (lv_img_bar_t*)obj;
    LV_ASSERT(img_bar);

    img_bar->min_idx = 0;
    img_bar->max_idx = 0;
    img_bar->value_idx = 0;
    img_bar->attr_addr = NULL;

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_img_bar_destructor(const lv_obj_class_t* class_p, lv_obj_t* obj)
{
    LV_UNUSED(class_p);

    lv_img_bar_t* img_bar = (lv_img_bar_t*)obj;
    LV_ASSERT(img_bar);
}

static void lv_img_bar_event(const lv_obj_class_t* class_p, lv_event_t* e)
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
        lv_img_bar_t* img_bar = (lv_img_bar_t*)obj;
        LV_ASSERT(img_bar);
        // if (img_bar->value_idx)
        //     lv_obj_data_unsubscribe(bar, img_bar->value_idx);
        // if (img_bar->max_idx)
        //     lv_obj_data_unsubscribe(bar, img_bar->max_idx);
        // if (img_bar->min_idx)
        //     lv_obj_data_unsubscribe(bar, img_bar->min_idx);
    }
}

#endif
