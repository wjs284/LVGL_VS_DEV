/**
 * @file zh_lv_title.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "zh_lv_title_private.h"
#include "../../misc/lv_area_private.h"
#include "../../draw/lv_draw_mask_private.h"
#include "../../core/lv_obj_private.h"
#include "../../core/lv_obj_class_private.h"
#if LV_USE_ZH_TITLE != 0

#include "../../draw/lv_draw.h"
#include "../../misc/lv_assert.h"
#include "../../misc/lv_anim_private.h"
#include "../../misc/lv_math.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS (&zh_lv_title_class)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void Zh_Lv_Title_Constructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void Zh_Lv_Title_Destructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void Zh_Lv_Title_Event(const lv_obj_class_t *class_p, lv_event_t *e);
static void Zh_Lv_Title_Back_Icon_Event_Cb(lv_event_t *e);
/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t zh_lv_title_class = {
    .constructor_cb = Zh_Lv_Title_Constructor,
    .destructor_cb = Zh_Lv_Title_Destructor,
    .event_cb = Zh_Lv_Title_Event,
    .width_def = LV_DPI_DEF,
    .height_def = 40,
    .instance_size = sizeof(Zh_Lv_Title_t),
    .base_class = &lv_obj_class,
    .name = "zh_title",
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t *Zh_Lv_Title_Create(lv_obj_t *parent, lv_coord_t height, const char *title_str, bool has_back_icon, bool has_timestamp, void *custom_cb)
{
    LV_LOG_INFO("begin");
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);

    lv_obj_set_size(obj, lv_obj_get_width(parent), height);

    if (has_back_icon)
    {
        lv_obj_t *img_icon = lv_image_create(obj);
        // lv_image_set_src(img_icon, &test_img_lvgl_logo_pngw2);
        // lv_obj_set_size(img_icon, LV_PCT(10), LV_SIZE_CONTENT);
//         lv_obj_align_to(img_icon, obj, LV_ALIGN_LEFT_MID, 0, 0);
//         lv_obj_add_flag(img_icon, LV_OBJ_FLAG_CLICKABLE);
//         // lv_obj_add_event_cb(img_icon, Zh_Lv_Title_Back_Icon_Event_Cb, LV_EVENT_SHORT_CLICKED, (Zh_Lv_Title_Custom_Cb_t)custom_cb);
#if 1
//         lv_obj_set_style_border_color(img_icon, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
//         lv_obj_set_style_border_width(img_icon, 1, LV_PART_MAIN);
#endif
    }

    lv_obj_t *descr_label = lv_label_create(obj);
    lv_obj_set_size(descr_label, LV_PCT(60), LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(descr_label, lv_color_white(), LV_PART_MAIN);
    //lv_obj_set_style_text_font(descr_label, font_large, LV_PART_MAIN);//TODO: wjs
    lv_label_set_long_mode(descr_label, LV_LABEL_LONG_SCROLL);
    lv_label_set_text(descr_label, title_str);
    lv_obj_set_style_text_align(descr_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_align_to(descr_label, obj, LV_ALIGN_LEFT_MID, 0, 0);
#if 1
    lv_obj_set_style_border_color(descr_label, lv_palette_main(LV_PALETTE_PURPLE), LV_PART_MAIN);
    lv_obj_set_style_border_width(descr_label, 1, LV_PART_MAIN);
#endif

    if (has_timestamp)
    {
        lv_obj_t *time_label = lv_label_create(obj);
        lv_obj_set_size(time_label, LV_PCT(28), LV_SIZE_CONTENT);
        lv_obj_set_style_text_color(time_label, lv_color_white(), LV_PART_MAIN);
        // lv_obj_set_style_text_font(time_label, font_large, LV_PART_MAIN);//TODO: wjs
        lv_label_set_long_mode(time_label, LV_LABEL_LONG_SCROLL);
        lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
        lv_obj_align_to(time_label, descr_label, LV_ALIGN_OUT_RIGHT_MID, LV_PCT(2), 0);
#if 1
        lv_obj_set_style_border_color(time_label, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
        lv_obj_set_style_border_width(time_label, 1, LV_PART_MAIN);
#endif
    }

    return obj;
}

/*=====================
 * Setter functions
 *====================*/

/*=====================
 * Getter functions
 *====================*/


/**********************
 *   STATIC FUNCTIONS
 **********************/

static void Zh_Lv_Title_Constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    Zh_Lv_Title_t *p_title = (Zh_Lv_Title_t *)obj;
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_PRESS_LOCK);
    //debug border
#if 1
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(obj, LV_OPA_80, LV_PART_MAIN);
	lv_obj_set_style_border_color(obj, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
#endif

    LV_TRACE_OBJ_CREATE("finished");
}

static void Zh_Lv_Title_Destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);
    Zh_Lv_Title_t *p_title = (Zh_Lv_Title_t *)obj;
}

static void Zh_Lv_Title_Event(const lv_obj_class_t *class_p, lv_event_t *e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /*Call the ancestor's event handler*/
    res = lv_obj_event_base(MY_CLASS, e);
    if (res != LV_RESULT_OK)
        return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);
    Zh_Lv_Title_t *p_title = (Zh_Lv_Title_t *)obj;
    if (code == LV_EVENT_REFR_EXT_DRAW_SIZE)
    {
    }
    else if (code == LV_EVENT_PRESSED || code == LV_EVENT_RELEASED)
    {
        // lv_bar_t * bar = (lv_bar_t *)obj;
        // lv_obj_invalidate_area(obj, &bar->indic_area);
    }
    else if (code == LV_EVENT_DRAW_MAIN_BEGIN)
    {

    }
    else if(code == LV_EVENT_SCROLL_END)
    {

    }
}

static void Zh_Lv_Title_Back_Icon_Event_Cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    Zh_Lv_Title_Custom_Cb_t custom_cb = lv_event_get_user_data(e);

    if (lv_event_get_code(e) == LV_EVENT_SHORT_CLICKED)
    {
        printf("\r\n%s\r\n", __func__);
        if (custom_cb)
        {
            custom_cb(e);
        }
        else
        {
            printf("\r\ngo back\r\n");
        }
    }
}
#endif
