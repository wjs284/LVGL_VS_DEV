/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "zh_lv_img_bar.h"
#if ZH_USE_IMG_BAR != 0

/*********************
 *  STATIC VARIABLES
 *********************/
static uint32_t g_refresh_count = 0;
char buf[128];
/*********************
 *  STATIC FUNCTIONS
 *********************/

/**
 * @brief 刷新定时器回调函数
 */
static void refresh_timer_cb(lv_timer_t* timer)
{
    LV_LOG_USER("refresh_timer_cb is running");
    lv_obj_t* test_baseobj = lv_timer_get_user_data(timer);
    lv_baseobj_t* baseobj = (lv_baseobj_t*)test_baseobj;

    g_refresh_count++;

    if (baseobj->cb) {
        baseobj->cb(test_baseobj, baseobj->id_tab, baseobj->id_num);
    }
    // 更新状态信息
    lv_obj_t* status_label = lv_obj_get_child(test_baseobj, 0); // 获取状态标签
    lv_snprintf(buf, sizeof(buf),
        "count: %lu\n"
        "num: %ld\n"
        "align: %d",
        g_refresh_count,
        baseobj->value_min + (g_refresh_count % 100),
        baseobj->ori_align);

    lv_label_set_text(status_label, buf);

    // // 每3次刷新切换显示状态
    // if (g_refresh_count % 5 == 0) {
    //     static bool visible = true;
    //     lv_obj_t* info_label = lv_obj_get_child(lv_obj_get_parent(test_baseobj), 1); // 获取信息标签

    //     if (visible) {
    //         lv_obj_add_flag(test_baseobj, LV_OBJ_FLAG_HIDDEN);
    //         lv_label_set_text(info_label, "hidden");
    //     } else {
    //         lv_obj_clear_flag(test_baseobj, LV_OBJ_FLAG_HIDDEN);
    //         lv_label_set_text(info_label, "display");
    //     }
    //     visible = !visible;
    // }
}

/**
 * @brief 自定义刷新回调函数
 */
static int32_t custom_refresh_cb(lv_obj_t* obj, uint16_t* id_tab, uint8_t id_num)
{
    // 每5次刷新切换对齐方式
    LV_LOG_USER("id_tab[0]=%ld, id_num=%d", id_tab[0], id_num);
    if (g_refresh_count % 5 == 0) {
        LV_LOG_USER("custom_refresh_cb is running");
        lv_obj_add_flag(obj, LV_OBJ_FLAG_IGNORE_LAYOUT);
        static uint8_t align_index = 0;
        lv_align_t aligns[] = {
            LV_ALIGN_TOP_LEFT, LV_ALIGN_TOP_MID, LV_ALIGN_TOP_RIGHT,
            LV_ALIGN_CENTER, LV_ALIGN_BOTTOM_LEFT, LV_ALIGN_BOTTOM_MID,
            LV_ALIGN_BOTTOM_RIGHT, LV_ALIGN_LEFT_MID, LV_ALIGN_RIGHT_MID
        };

        lv_baseobj_set_ori_align(obj, aligns[align_index]);
        lv_baseobj_align_to_ori_pos(obj);

        align_index = (align_index + 1) % (sizeof(aligns) / sizeof(aligns[0]));
    }

    return 0;
}

/**
 * @brief 开始测试按钮回调
 */
static void start_test_cb(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_t* test_container = lv_obj_get_parent(lv_obj_get_parent(btn));
    lv_timer_t* timer = lv_obj_get_user_data(lv_obj_get_parent(btn));

    if (timer) {
        lv_timer_resume(timer);
        lv_obj_t* info_label = lv_obj_get_child(test_container, 1);
        lv_label_set_text(info_label, "test is running");
        LV_LOG_USER("test is running");
    }
}

/**
 * @brief 停止测试按钮回调
 */
static void stop_test_cb(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_t* test_container = lv_obj_get_parent(lv_obj_get_parent(btn));
    lv_timer_t* timer = lv_obj_get_user_data(lv_obj_get_parent(btn));

    if (timer) {
        lv_timer_pause(timer);
        lv_obj_t* info_label = lv_obj_get_child(test_container, 1);
        lv_label_set_text(info_label, "test is stop");
        LV_LOG_USER("test is stop");
    }
}

/**
 * @brief 重置测试按钮回调
 */
static void reset_test_cb(lv_event_t* e)
{
    lv_obj_t* btn = lv_event_get_target(e);
    lv_obj_t* test_container = lv_obj_get_parent(lv_obj_get_parent(btn));
    lv_obj_t* test_baseobj = lv_obj_get_child(test_container, 2);

    g_refresh_count = 0;
    lv_baseobj_set_ori_align(test_baseobj, LV_ALIGN_TOP_LEFT);
    lv_baseobj_align_to_ori_pos(test_baseobj);
    lv_obj_clear_flag(test_baseobj, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t* status_label = lv_obj_get_child(test_container, 3);
    lv_label_set_text(status_label, "count: 0\n num: 0\n align: 0");

    lv_obj_t* info_label = lv_obj_get_child(test_container, 1);
    lv_label_set_text(info_label, "test is reset");

    LV_LOG_USER("test is reset");
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
    lv_img_bar_set_src(img_bar, srcs[0]);
    lv_img_bar_set_indicator_src(img_bar, srcs[2]);

    lv_obj_set_size(img_bar, 200, 50); // 示例大小
    lv_obj_set_size(((lv_img_bar_t *)img_bar)->bar_img, 200, 50);

    lv_obj_center(((lv_img_bar_t *)img_bar)->bar_img);
    lv_obj_center(((lv_img_bar_t *)img_bar)->indicator_img);

    // // 创建基础对象实例
    // lv_obj_t* test_baseobj = lv_baseobj_create(test_container);
    // lv_obj_set_size(test_baseobj, 200, 100);
    // lv_obj_set_style_bg_color(test_baseobj, lv_color_hex(0x3498db), 0);
    // lv_obj_set_style_bg_opa(test_baseobj, LV_OPA_80, 0);
    // lv_obj_set_style_border_width(test_baseobj, 2, 0);
    // lv_obj_set_style_border_color(test_baseobj, lv_color_hex(0x2980b9), 0);
    // lv_obj_set_style_radius(test_baseobj, 15, 0);

    // // 设置基础对象属性
    // lv_baseobj_set_ori_pos(test_baseobj, 160, 80);
    // lv_baseobj_set_ori_size(test_baseobj, 200, 100);
    // lv_baseobj_set_ori_align(test_baseobj, LV_ALIGN_TOP_LEFT);
    // lv_baseobj_set_hidden_rule(test_baseobj, HIDDEN_RULE_ALWAYS_ON);
    // lv_baseobj_set_range_value(test_baseobj, 0, 100);
    // lv_baseobj_set_range_scale(test_baseobj, 0, 360);
    // lv_baseobj_set_refresh_cb(test_baseobj, custom_refresh_cb);

    // // 设置源ID
    // uint16_t source_ids[] = {1001, 1002, 1003};
    // lv_baseobj_set_source_id(test_baseobj, source_ids, 3);

    // // 在基础对象内添加内容标签
    // lv_obj_t* content_label = lv_label_create(test_baseobj);
    // lv_label_set_text(content_label, "baseobj");
    // lv_obj_center(content_label);

    // // 创建状态显示标签
    // lv_obj_t* status_label = lv_label_create(test_container);
    // lv_label_set_text(status_label, "count: 0\n num: 0\n align: 0");
    // lv_obj_set_width(status_label, lv_pct(100));
    // lv_obj_set_style_text_align(status_label, LV_TEXT_ALIGN_CENTER, 0);

    // // 创建控制按钮面板
    // lv_obj_t* btn_container = lv_obj_create(test_container);
    // lv_obj_remove_style_all(btn_container);
    // lv_obj_set_size(btn_container, lv_pct(100), LV_SIZE_CONTENT);
    // lv_obj_set_flex_flow(btn_container, LV_FLEX_FLOW_COLUMN);
    // lv_obj_set_flex_align(btn_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // // 创建开始按钮
    // lv_obj_t* start_btn = lv_btn_create(btn_container);
    // lv_obj_set_size(start_btn, 100, 40);
    // lv_obj_t* start_label = lv_label_create(start_btn);
    // lv_label_set_text(start_label, "start");
    // lv_obj_center(start_label);
    // lv_obj_add_event_cb(start_btn, start_test_cb, LV_EVENT_CLICKED, NULL);

    // // 创建停止按钮
    // lv_obj_t* stop_btn = lv_btn_create(btn_container);
    // lv_obj_set_size(stop_btn, 100, 40);
    // lv_obj_set_style_bg_color(stop_btn, lv_color_hex(0xe74c3c), 0);
    // lv_obj_t* stop_label = lv_label_create(stop_btn);
    // lv_label_set_text(stop_label, "stop");
    // lv_obj_center(stop_label);
    // lv_obj_add_event_cb(stop_btn, stop_test_cb, LV_EVENT_CLICKED, NULL);

    // // 创建重置按钮
    // lv_obj_t* reset_btn = lv_btn_create(btn_container);
    // lv_obj_set_size(reset_btn, 100, 40);
    // lv_obj_set_style_bg_color(reset_btn, lv_color_hex(0xf39c12), 0);
    // lv_obj_t* reset_label = lv_label_create(reset_btn);
    // lv_label_set_text(reset_label, "reset");
    // lv_obj_center(reset_label);
    // lv_obj_add_event_cb(reset_btn, reset_test_cb, LV_EVENT_CLICKED, NULL);

    // // 创建刷新定时器（1秒刷新一次）
    // lv_baseobj_create_refresh_task(test_baseobj, 1000, refresh_timer_cb);
    // lv_baseobj_refresh_stop(test_baseobj); // 初始状态暂停

    // // 将定时器指针存储在测试容器中
    // lv_obj_set_user_data(btn_container, ((lv_baseobj_t *)test_baseobj)->timer);

    // g_refresh_count = 0;

    // LV_LOG_USER("page create done");

    return test_container;
}
#endif
