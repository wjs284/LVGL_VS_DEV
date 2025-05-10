/**
 * @file zh_lv_base_page.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "zh_lv_base_page_private.h"
#include "../../misc/lv_area_private.h"
#include "../../draw/lv_draw_mask_private.h"
#include "../../core/lv_obj_private.h"
#include "../../core/lv_obj_class_private.h"
#if LV_USE_ZH_BASE_PAGE != 0

#include "../../draw/lv_draw.h"
#include "../../misc/lv_assert.h"
#include "../../misc/lv_anim_private.h"
#include "../../misc/lv_math.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS (&zh_lv_base_page_class)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void Zh_Lv_Base_Page_Constructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void Zh_Lv_Base_Page_Destructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void Zh_Lv_Base_Page_Event(const lv_obj_class_t *class_p, lv_event_t *e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t zh_lv_base_page_class = {
    .constructor_cb = Zh_Lv_Base_Page_Constructor,
    .destructor_cb = Zh_Lv_Base_Page_Destructor,
    .event_cb = Zh_Lv_Base_Page_Event,
    .width_def = LV_DPI_DEF,
    .height_def = LV_DPI_DEF,
    .instance_size = sizeof(Zh_Lv_Base_Page_t),
    .base_class = &lv_obj_class,
    .name = "base_page",
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t *Zh_Lv_Base_Page_Create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h)
{
    LV_LOG_INFO("begin");
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);

    if (w != 0)
        lv_obj_set_width(obj, w);
    if (h != 0)
        lv_obj_set_height(obj, h);

    if (align_parent)
        lv_obj_align_to(obj, align_parent, align, x, y);
    else
        lv_obj_set_pos(obj, x, y);

    return obj;
}

lv_obj_t *Zh_Lv_Base_Page_Child_Create(void *base_page, lv_coord_t height)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    lv_obj_t *child = lv_obj_create((lv_obj_t *)base_page);
    lv_obj_remove_style_all(child);
    lv_obj_remove_flag(child, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_PRESS_LOCK);
    lv_obj_set_size(child, lv_obj_get_width((lv_obj_t *)base_page), height);

#if 1
    lv_obj_set_style_bg_color(child, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(child, LV_OPA_80, LV_PART_MAIN);
    lv_obj_set_style_border_color(child, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
    lv_obj_set_style_border_width(child, 1, LV_PART_MAIN);
#endif
    return child;
}

uint8_t Zh_Lv_Base_Page_Add_Child(void *base_page, lv_obj_t *child)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    if(base_page == NULL || child == NULL)
    {
        return UINT8_MAX;
    }

    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    Zh_Lv_Base_Page_Child_Node_t *new_node = (Zh_Lv_Base_Page_Child_Node_t *)lv_malloc(sizeof(Zh_Lv_Base_Page_Child_Node_t));
    if (new_node == NULL)
    {
        LV_TRACE_OBJ_CREATE("\r\n%s, erro, lv_malloc failed\r\n", __func__);
        return UINT8_MAX;
    }
    new_node->child = child;
    new_node->next = NULL;

    uint8_t list_length = 1;
    if (p_base_page->child_head == NULL)
    {
        p_base_page->child_head = new_node;
        return list_length;
    }

    Zh_Lv_Base_Page_Child_Node_t *current = p_base_page->child_head;
    while (current->next != NULL)
    {
        current = current->next;
        list_length++;
    }
    current->next = new_node;
    return list_length + 1;
}

void Zh_Lv_Base_Page_Clear_Child(void *base_page)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    if(base_page == NULL)
    {
        return;
    }

    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    Zh_Lv_Base_Page_Child_Node_t *current = p_base_page->child_head;
    while (current != NULL)
    {
        Zh_Lv_Base_Page_Child_Node_t *next = current->next;
        lv_free(current);
        current = next;
    }
    p_base_page->child_head = NULL;
}

uint8_t Zh_Lv_Base_Page_Get_Child_Num(void *base_page)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    if(base_page == NULL)
    {
        return UINT8_MAX;
    }

    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    uint8_t num = 0;
    Zh_Lv_Base_Page_Child_Node_t *current = p_base_page->child_head;
    while (current != NULL)
    {
        num++;
        current = current->next;
    }
    return num;
}

void Zh_Lv_Base_Page_Set_Dir(void *base_page, Zh_Base_Page_Dir_e dir)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    if (base_page == NULL)
    {
        return;
    }

    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    if (dir == BASE_PAGE_DIR_HOR)
    {
        lv_obj_set_flex_flow((lv_obj_t *)base_page, LV_FLEX_FLOW_ROW);
        p_base_page->dir = BASE_PAGE_DIR_HOR;
    }
    else if (dir == BASE_PAGE_DIR_VER)
    {
        lv_obj_set_flex_flow((lv_obj_t *)base_page, LV_FLEX_FLOW_COLUMN);
        p_base_page->dir = BASE_PAGE_DIR_VER;
    }
}

void Zh_Lv_Base_Page_Set_Gesture_Cb(void *base_page, void *left_gesture, void *right_gesture, void *up_gesture, void *down_gesture)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    if (base_page == NULL)
    {
        return;
    }
    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    p_base_page->gesture_cb[0] = (Zh_Lv_Gesture_Cb_t)left_gesture;
    p_base_page->gesture_cb[1] = (Zh_Lv_Gesture_Cb_t)right_gesture;
    p_base_page->gesture_cb[2] = (Zh_Lv_Gesture_Cb_t)up_gesture;
    p_base_page->gesture_cb[3] = (Zh_Lv_Gesture_Cb_t)down_gesture;
}

void Zh_Lv_Base_Page_Scroll_To_Last_Pos(void *base_page, bool anim_en)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);
    Zh_Lv_Base_Page_t *p_base_page = (Zh_Lv_Base_Page_t *)base_page;
    lv_obj_scroll_to((lv_obj_t *)base_page, p_base_page->last_pos.x, p_base_page->last_pos.y, anim_en);
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

static void Zh_Lv_Base_Page_Constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    Zh_Lv_Base_Page_t *base_page = (Zh_Lv_Base_Page_t *)obj;
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC |LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_CHAIN | LV_OBJ_FLAG_PRESS_LOCK);
    //scroll direction
#if 1
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
    base_page->dir = BASE_PAGE_DIR_VER;
    lv_obj_set_style_pad_row(obj, 10, LV_PART_MAIN);
    lv_obj_add_flag(obj, ZH_LV_OBJ_FLAG_SCROLL_ELASTIC_VER);
#else
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
    base_page->dir = BASE_PAGE_DIR_HOR;
    lv_obj_set_style_pad_column(obj, 10, LV_PART_MAIN);
    lv_obj_add_flag(obj, ZH_LV_OBJ_FLAG_SCROLL_ELASTIC_HOR);
#endif
    //top/bottom gap
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(obj, 20, LV_PART_MAIN);
    //scroll bar properties
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_ACTIVE);
    //scroll bar styles
    lv_style_init(&base_page->scrollbar_style);
    lv_style_set_bg_color(&base_page->scrollbar_style, lv_palette_main(LV_PALETTE_DEEP_PURPLE));
    lv_style_set_bg_opa(&base_page->scrollbar_style, LV_OPA_COVER);
    lv_style_set_width(&base_page->scrollbar_style, 10);
    lv_obj_add_style(obj, &base_page->scrollbar_style, LV_PART_SCROLLBAR);
    //debug border
#if 1
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(obj, LV_OPA_80, LV_PART_MAIN);
	lv_obj_set_style_border_color(obj, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
	lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
#endif

    LV_TRACE_OBJ_CREATE("finished");
}

static void Zh_Lv_Base_Page_Destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);
    Zh_Lv_Base_Page_t *base_page = (Zh_Lv_Base_Page_t *)obj;
    Zh_Lv_Base_Page_Clear_Child(base_page);
}

static void Zh_Lv_Base_Page_Event(const lv_obj_class_t *class_p, lv_event_t *e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /*Call the ancestor's event handler*/
    res = lv_obj_event_base(MY_CLASS, e);
    if (res != LV_RESULT_OK)
        return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_current_target(e);
    Zh_Lv_Base_Page_t *base_page = (Zh_Lv_Base_Page_t *)obj;

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
        printf("\r\ndraw main begin\r\n");
        lv_indev_t *indev = lv_indev_get_act();
        if (indev)
        {
            printf("\r\nindev = 0x%08X\r\n", indev);
            lv_dir_t dir = lv_indev_get_gesture_dir(indev);
            if (dir > 0 && dir <= 4 && base_page->gesture_cb[dir - 1] != NULL)
            {
                base_page->gesture_cb[dir - 1](e);
            }
        }
    }
    else if(code == LV_EVENT_SCROLL_END)
    {
        base_page->last_pos.x = lv_obj_get_scroll_x(obj);
        base_page->last_pos.y = lv_obj_get_scroll_y(obj);
        printf("\r\nscroll end, x:%d, y:%d\r\n", base_page->last_pos.x, base_page->last_pos.y);
    }
}
#endif
