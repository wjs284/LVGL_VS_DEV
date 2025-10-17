/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "zh_lv_img_bar.h"
#if ZH_USE_IMG_BAR != 0

/*********************
 *  STATIC VARIABLES
 *********************/
int32_t ret = 5;

/*********************
 *  STATIC FUNCTIONS
 *********************/

/**
 * @brief 自定义刷新回调函数
 */
static int32_t custom_refresh_cb(lv_obj_t* obj, uint16_t* id_tab, uint8_t id_num)
{
    LV_LOG_USER("-----ret==%d-----", ret);
    return ret;
}

/**
 * @brief 开始测试按钮回调
 */
static void add_test_cb(lv_event_t* e)
{
    ret = ret < 5 ? ++ret : ret;
    LV_LOG_USER("-----ret==%d-----", ret);

    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_t* test_container = lv_obj_get_parent(lv_obj_get_parent(btn));
}

/**
 * @brief 停止测试按钮回调
 */
static void subtract_test_cb(lv_event_t* e)
{
    ret = ret > 0 ? --ret : ret;
    LV_LOG_USER("-----ret==%d-----", ret);

    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_t* test_container = lv_obj_get_parent(lv_obj_get_parent(btn));
}

/**
 * @brief 重置测试按钮回调
 */
static void reset_test_cb(lv_event_t* e)
{
    ret = 5;
    static uint8_t count = 0;
    count++;
    if (count == 4)
        count = 0;

    lv_obj_t* img_bar = lv_event_get_user_data(e);
    switch (count) {
    case 0:
        lv_img_bar_set_dir(img_bar, BAR_DIR_LEFT_TO_RIGHT);
        break;
    case 1:
        lv_img_bar_set_dir(img_bar, BAR_DIR_RIGTH_TO_LEFT);
        break;
    case 2:
        lv_img_bar_set_dir(img_bar, BAR_DIR_TOP_TO_BOTTOM);
        break;
    case 3:
        lv_img_bar_set_dir(img_bar, BAR_DIR_BOTTOM_TO_TOP);
        break;
    default:
        break;
    }


}

/*********************
 *  GLOBAL FUNCTIONS
 *********************/

lv_obj_t* lv_base_img_bar_test_create(lv_obj_t* parent)
{
    LV_IMG_DECLARE(img_render_lvgl_logo_xrgb8888);
    LV_IMG_DECLARE(img_render_lvgl_logo_rgb888);
    LV_IMG_DECLARE(img_render_lvgl_logo_rgb565);
    LV_IMG_DECLARE(img_render_lvgl_logo_argb8888);
    const void* srcs[] = {
        &img_render_lvgl_logo_argb8888,
        &img_render_lvgl_logo_xrgb8888,
        &img_render_lvgl_logo_rgb888,
        &img_render_lvgl_logo_rgb565,
    };

    // 创建测试容器
    lv_obj_t* test_container = lv_obj_create(parent);
    lv_obj_set_size(test_container, lv_pct(100), lv_pct(100));
    lv_obj_center(test_container);
    lv_obj_set_flex_flow(test_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(test_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);

    // 创建标题
    lv_obj_t* title_label = lv_label_create(test_container);
    lv_label_set_text(title_label, "baseobj test");
    lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(title_label, lv_pct(100));

    // 创建信息标签
    lv_obj_t* info_label = lv_label_create(test_container);
    lv_label_set_text(info_label, "test done");
    lv_obj_set_style_text_align(info_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(info_label, lv_pct(100));

    lv_obj_t* img = lv_image_create(test_container);
    lv_image_set_src(img, srcs[0]);

    lv_obj_t* img_bar = lv_img_bar_create(test_container);
    lv_obj_align(img_bar, LV_ALIGN_TOP_LEFT, 250, 500);
    lv_img_bar_set_src(img_bar, srcs[0]);
    lv_obj_add_flag(((lv_img_bar_t*)img_bar)->bar_img, LV_OBJ_FLAG_HIDDEN);
    lv_img_bar_set_indicator_src(img_bar, srcs[0]);
    lv_obj_set_style_border_width(img_bar, 1, 0);
    lv_obj_set_style_border_color(img_bar, lv_color_hex(0x00FF00), 0);

    lv_baseobj_set_refresh_cb(img_bar, custom_refresh_cb);
    lv_baseobj_create_refresh_task(img_bar, 300, lv_img_bar_refresh_task);
    lv_baseobj_set_range_value(img_bar, 0, 5);

    // 创建控制按钮面板
    lv_obj_t* btn_container = lv_obj_create(test_container);
    lv_obj_remove_style_all(btn_container);
    lv_obj_set_size(btn_container, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(btn_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // 创建开始按钮
    lv_obj_t* add_btn = lv_btn_create(btn_container);
    lv_obj_set_size(add_btn, 100, 40);
    lv_obj_t* start_label = lv_label_create(add_btn);
    lv_label_set_text(start_label, "add_btn");
    lv_obj_center(start_label);
    lv_obj_add_event_cb(add_btn, add_test_cb, LV_EVENT_CLICKED, NULL);

    // 创建停止按钮
    lv_obj_t* subtract_btn = lv_btn_create(btn_container);
    lv_obj_set_size(subtract_btn, 100, 40);
    lv_obj_set_style_bg_color(subtract_btn, lv_color_hex(0xe74c3c), 0);
    lv_obj_t* stop_label = lv_label_create(subtract_btn);
    lv_label_set_text(stop_label, "subtract_btn");
    lv_obj_center(stop_label);
    lv_obj_add_event_cb(subtract_btn, subtract_test_cb, LV_EVENT_CLICKED, NULL);

    // 创建重置按钮
    lv_obj_t* reset_btn = lv_btn_create(btn_container);
    lv_obj_set_size(reset_btn, 100, 40);
    lv_obj_set_style_bg_color(reset_btn, lv_color_hex(0xf39c12), 0);
    lv_obj_t* reset_label = lv_label_create(reset_btn);
    lv_label_set_text(reset_label, "reset_btn");
    lv_obj_center(reset_label);
    lv_obj_add_event_cb(reset_btn, reset_test_cb, LV_EVENT_CLICKED, img_bar);

    return test_container;
}
#endif
