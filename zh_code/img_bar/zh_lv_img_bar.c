/*********************
 *      INCLUDES
 *********************/
#include "zh_lv_img_bar.h"
#include "../image/lv_image.h"

#if ZH_USE_IMG_BAR != 0

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
const lv_obj_class_t lv_img_bar_class = {
    .constructor_cb = lv_img_bar_constructor,
    .destructor_cb = lv_img_bar_destructor,
    .event_cb = lv_img_bar_event,
    .width_def = LV_DPI_DEF * 2,
    .height_def = LV_DPI_DEF / 10,
    .instance_size = sizeof(lv_img_bar_t),
    .base_class = &lv_baseobj_class,
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
    img_bar->last_ret = HIDDEN_RULE_INVALID;

    img_bar->bar_img = NULL;     
    img_bar->indicator_img = NULL;
    img_bar->dir = BAR_DIR_LEFT_TO_RIGHT; 

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
    }
}

/**
 * @brief 刷新进度条显示处理函数
 * @param img: 图片进度条对象指针
 * @param ret: 当前进度值
 *
 * 功能：根据当前进度值计算并更新进度条的显示尺寸和指示器位置
 *       支持四种方向的进度显示和Q24.8定点数数据处理
 */
static void refresh_handle(lv_obj_t* img, int32_t ret)
{
    int32_t ret_int = 0, ret_dou = 0;
    int32_t size, ori_size;

    lv_img_bar_t* img_bar = (lv_img_bar_t*)img;
    lv_baseobj_t* baseobj = (lv_baseobj_t*)img_bar;

    if (img_bar->last_ret == ret) {
        return;
    }
    if (baseobj->hidden_rule == HIDDEN_RULE_UNIT_MISMATCH && ret == HIDDEN_RULE_UNIT_MISMATCH) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    if (img_bar->dir & 0x10)
        ori_size = baseobj->ori_h;
    else
        ori_size = baseobj->ori_w;

    // if (baseobj->data_type == DATABASE_TYPE_Q24_8)
    //     ret_int = (int32_t)Q24_Q_TO_DOUBLE(ret);
    // else
        ret_int = ret;

    if (ret_int > baseobj->value_max)
        size = ori_size;
    if (ret_int < baseobj->value_min)
        size = 0;
    else
        size = (ret_int - baseobj->value_min) * ori_size / (baseobj->value_max - baseobj->value_min);

    if (BAR_DIR_LEFT_TO_RIGHT == img_bar->dir) {
        lv_obj_set_width(img, size);
        if (img_bar->indicator_img)
            lv_obj_align_to(img_bar->indicator_img, img, LV_ALIGN_OUT_RIGHT_MID, -(lv_obj_get_width(img_bar->indicator_img) >> 1), 0);
    } else if (BAR_DIR_RIGTH_TO_LEFT == img_bar->dir) {
        lv_obj_set_width(img, size);
        lv_obj_set_x(img, ori_size - size);
        lv_obj_set_x(img_bar->bar_img, -ori_size + size);
        if (img_bar->indicator_img)
            lv_obj_align_to(img_bar->indicator_img, img, LV_ALIGN_OUT_LEFT_MID, (lv_obj_get_width(img_bar->indicator_img) >> 1), 0);
    } else if (BAR_DIR_TOP_TO_BOTTOM == img_bar->dir) {
        lv_obj_set_height(img, size);
        if (img_bar->indicator_img)
            lv_obj_align_to(img_bar->indicator_img, img, LV_ALIGN_OUT_BOTTOM_MID, 0, -(lv_obj_get_height(img_bar->indicator_img) >> 1));
    } else if (BAR_DIR_BOTTOM_TO_TOP == img_bar->dir) {
        lv_obj_set_height(img, size);
        lv_obj_set_y(img, ori_size - size);
        lv_obj_set_y(img_bar->bar_img, -ori_size + size);
        if (img_bar->indicator_img)
            lv_obj_align_to(img_bar->indicator_img, img, LV_ALIGN_OUT_TOP_MID, 0, (lv_obj_get_height(img_bar->indicator_img) >> 1));
    }
}

/**
 * @brief 进度条刷新任务函数
 * @param task: 任务对象指针，包含用户数据为图片进度条对象
 *
 * 功能：定时任务函数，通过回调函数获取当前进度值并刷新显示
 *       该函数由LVGL任务系统定期调用
 */
void lv_img_bar_refresh_task(lv_timer_t* timer)
{
    lv_obj_t* img_bar = (lv_obj_t*)timer->user_data;
    lv_baseobj_t* baseobj = (lv_baseobj_t*)img_bar;
    LV_ASSERT(baseobj);

    if (baseobj->cb) {
        int32_t ret = baseobj->cb(img_bar, baseobj->id_tab, baseobj->id_num);
        refresh_handle(img_bar, ret);
    }
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief 设置进度条填充方向
 * @param img: 图片进度条对象指针
 * @param dir: 填充方向枚举值
 *
 * 功能：设置进度条的填充方向，支持四个方向：
 *       - 从左到右、从右到左、从上到下、从下到上
 *       方向设置影响进度条的尺寸变化和指示器位置
 */
void lv_img_bar_set_dir(lv_obj_t* img, lv_img_bar_dir_t dir)
{
    LV_ASSERT_OBJ(img, MY_CLASS);
    lv_img_bar_t* img_bar = (lv_img_bar_t*)img;
    LV_ASSERT(img_bar);

    img_bar->dir = dir;
}

/**
 * @brief 设置进度条图片资源
 * @param img: 图片进度条对象指针
 * @param src_img: 进度条图片资源描述符指针
 *
 * 功能：设置进度条的主体图片，控件大小会根据图片大小自动调整
 *       如果进度条图片对象不存在，会自动创建
 */
void lv_img_bar_set_src(lv_obj_t* img, const void* src_img)
{
    LV_ASSERT_OBJ(img, MY_CLASS);
    lv_img_bar_t* img_bar = (lv_img_bar_t*)img;
    LV_ASSERT(img_bar);

    if (NULL == img_bar->bar_img) {
        img_bar->bar_img = lv_image_create(img);
    }
    lv_image_set_src(img_bar->bar_img, src_img);
    lv_obj_set_size(img, lv_obj_get_width(img_bar->bar_img), lv_obj_get_height(img_bar->bar_img));
    lv_baseobj_set_ori_size(img, lv_obj_get_width(img_bar->bar_img), lv_obj_get_height(img_bar->bar_img));
}

/**
 * @brief 设置进度指示器图片资源
 * @param img: 图片进度条对象指针
 * @param src_img: 指示器图片资源描述符指针
 *
 * 功能：设置进度指示器图片，该图片会随着进度值移动显示当前进度位置
 *       指示器图片创建在进度条的父对象中，以便正确显示位置
 */
void lv_img_bar_set_indicator_src(lv_obj_t* img, const void* src_img)
{
    LV_ASSERT_OBJ(img, MY_CLASS);
    lv_img_bar_t* img_bar = (lv_img_bar_t*)img;
    LV_ASSERT(img_bar);

    if (NULL == img_bar->indicator_img) {
        img_bar->indicator_img = lv_image_create(img);//TODO
    }
    lv_image_set_src(img_bar->indicator_img, src_img);
}

#endif
