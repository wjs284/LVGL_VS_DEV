#include "zh_ui_test.h"


typedef struct
{
	lv_obj_t *cont;
} Zh_Demo_Data_t;

Zh_Demo_Data_t zh_demo_data;

#define ZH_DEMO_CONT 0
#define ZH_DEMO_IMG 0
#define ZH_DEMO_LABEL 0
#define ZH_DEMO_BUTTON 0
#define ZH_DEMO_BASE_PAGE 0
#define ZH_DEMO_ARC 0
#define ZH_DEMO_CHART 0
#define ZH_DEMO_BAR 0
#define ZH_DEMO_BEZIER_LINE 0
#define ZH_DEMO_CANVAS 0
#define ZH_DEMO_FLEX_PAGE 0
#define ZH_DEMO_WEATHER_LINE 0
#define ZH_DEMO_PATH_VECTOR 1
static void btn_event_cb(lv_event_t *e)
{
	lv_obj_t *btn = lv_event_get_target(e);
	static uint8_t state = 0;
	if (lv_event_get_code(e) == LV_EVENT_SHORT_CLICKED)
	{
		state = !state;
		lv_obj_set_style_bg_color(btn, state ? lv_palette_main(LV_PALETTE_RED) : lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
		printf("Button Clicked state = %d\n", state);
	}
}

#if ZH_DEMO_CONT
const lv_style_const_prop_t const_style_props[] = {
	LV_STYLE_CONST_WIDTH(51),
	LV_STYLE_CONST_HEIGHT(50),
	LV_STYLE_CONST_SHADOW_WIDTH(10),
	LV_STYLE_CONST_SHADOW_SPREAD(5),
	LV_STYLE_CONST_SHADOW_COLOR(0xFCCFFF),
	LV_STYLE_CONST_PROPS_END};
LV_STYLE_CONST_INIT(const_style, const_style_props);

void Zh_Demo_Create(void)
{
	lv_obj_t *cont = zh_cont_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 0, 0, NULL);
	zh_demo_data.cont = cont;
	// lv_obj_null_on_delete(zh_demo_data.cont);//obj被删除时置空指针
	lv_obj_center(cont);//居中

	// lv_obj_add_style(zh_demo_data.cont, &const_style, LV_PART_MAIN);

	static lv_style_t style_shadow;
	lv_style_init(&style_shadow);
	lv_style_set_shadow_width(&style_shadow, 10);
	lv_style_set_shadow_spread(&style_shadow, 5);
	lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));
	lv_obj_add_style(zh_demo_data.cont, &style_shadow, LV_PART_MAIN);

	lv_obj_t *test1_label = lv_label_create(cont);
	lv_label_set_text(test1_label, "test1_label");
	lv_obj_align_to(test1_label, cont, LV_ALIGN_LEFT_MID, 10, 0);

	lv_obj_t *test2_label = lv_label_create(cont);
	lv_label_set_text(test2_label, "test2_label");
	lv_obj_align_to(test2_label, test1_label, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

	lv_obj_t *test3_label = lv_label_create(cont);
	lv_label_set_text(test3_label, "test3_label");
	lv_obj_align_to(test3_label, test1_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
#elif ZH_DEMO_IMG
void Zh_Demo_Create(void)
{
	lv_obj_t *img = zh_img_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, &emoji_F617_2);
	lv_obj_center(img);
	// lv_image_set_src(img, LV_SYMBOL_DUMMY "Some text");//文本以图片形式展现
	// lv_image_set_scale(img, 128);	  // 缩放图片zoom
	// lv_image_set_rotation(img, 1800); // 旋转图片180度
	// lv_image_set_pivot(img, 0, 0);	  // 设置图片旋转中心,默认为图片中心
	// lv_image_set_antialias(img, true); // 抗锯齿
	lv_obj_set_style_image_recolor_opa(img, LV_OPA_70, LV_PART_MAIN);//设置图片透明度
    lv_obj_set_style_image_recolor(img, lv_palette_main(LV_PALETTE_BLUE),LV_PART_MAIN);//设置图片颜色

#if 0// 重设图片框的背景颜色与大小，设置图片在图片框内的y偏移量
	static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
	lv_obj_add_style(img, &style, LV_PART_MAIN);
	lv_image_set_src(img, &emoji_F617_2);
	lv_obj_set_size(img, 300, 300);
	lv_image_set_offset_y(img, 100); // 设置图片Y
#endif
}
#elif ZH_DEMO_LABEL
void Zh_Demo_Create(void)
{
#if 0
	lv_coord_t width = 300, height = 60;
	lv_label_long_mode_t long_mode = LV_LABEL_LONG_SCROLL_CIRCULAR;
	lv_text_align_t label_align = LV_TEXT_ALIGN_CENTER;
#elif 0
	lv_coord_t width = 300, height = 60;
	lv_label_long_mode_t long_mode = LV_LABEL_LONG_DOT;
	lv_text_align_t label_align = LV_TEXT_ALIGN_CENTER;
#elif 1
	lv_coord_t width = 300, height = 0;
	lv_label_long_mode_t long_mode = LV_LABEL_LONG_WRAP;
	lv_text_align_t label_align = LV_TEXT_ALIGN_CENTER;
#endif
	lv_obj_t *label = zh_label_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, width, height, "LabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabelLabel",
										  lv_palette_main(LV_PALETTE_BLUE), label_align, long_mode, 0, 0);
	lv_obj_center(label);
}
#elif ZH_DEMO_BUTTON
void Zh_Demo_Create(void)
{
#if 0
	lv_obj_t *btn = zh_button_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 100, 50, 60, 
									lv_palette_main(LV_PALETTE_BLUE), LV_OPA_40, 30, 20, btn_event_cb);
#elif 0
	lv_obj_t *btn = zh_button_with_icon_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 200, 120, 60,
											   lv_palette_main(LV_PALETTE_BLUE), LV_OPA_40, 30, 20, &emoji_F617_2, btn_event_cb);
#elif 0
	lv_obj_t *btn = zh_button_with_txt_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 200, 120, 60,
											  lv_palette_main(LV_PALETTE_BLUE), LV_OPA_40, 30, 20,
											  200 - 20 * 2, 0, "Button", lv_palette_main(LV_PALETTE_RED), LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_SCROLL, 0, 0, btn_event_cb);
#elif 1
	lv_obj_t *btn = zh_img_button_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, &emoji_F617_2, btn_event_cb);
#elif 0
	lv_obj_t *btn = zh_img_button_with_icon_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, &test_arc_bg22, &emoji_F617_2, btn_event_cb);
#else
	lv_obj_t *btn = zh_img_button_with_txt_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, &emoji_F617_2, 200 - 20 * 2, 0, "Button", lv_palette_main(LV_PALETTE_RED), LV_TEXT_ALIGN_CENTER, LV_LABEL_LONG_SCROLL, 0, 0, btn_event_cb);
#endif
	lv_obj_center(btn);
}
#elif ZH_DEMO_BASE_PAGE

static bool Zh_Lv_Base_Page_Left_Gesture(lv_event_t *e)
{
	printf("\r\n%s\r\n", __func__);
	return true;
}

static bool Zh_Lv_Base_Page_Right_Gesture(lv_event_t *e)
{
	printf("\r\n%s\r\n", __func__);
	return true;
}

static bool Zh_Lv_Base_Page_Up_Gesture(lv_event_t *e)
{
	printf("\r\n%s\r\n", __func__);
	return true;
}

static bool Zh_Lv_Base_Page_Down_Gesture(lv_event_t *e)
{
	printf("\r\n%s\r\n", __func__);
	return true;
}

void Zh_Demo_Create(void)
{
	lv_obj_t *title = Zh_Lv_Title_Create(lv_scr_act(), 40, "Base Page", true, true, NULL);

	lv_obj_t *base_page = Zh_Lv_Base_Page_Create(lv_scr_act(), title, LV_ALIGN_OUT_BOTTOM_MID, 0, 0, LV_HOR_RES, LV_HOR_RES - lv_obj_get_height(title));
	// Zh_Lv_Base_Page_Set_Dir(base_page, BASE_PAGE_DIR_HOR);
	Zh_Lv_Base_Page_Set_Gesture_Cb(base_page, Zh_Lv_Base_Page_Left_Gesture, Zh_Lv_Base_Page_Right_Gesture, Zh_Lv_Base_Page_Up_Gesture, Zh_Lv_Base_Page_Down_Gesture);

	for (int i = 0; i < 10; i++)
	{
		lv_obj_t *child = Zh_Lv_Base_Page_Child_Create(base_page, 100);
		Zh_Lv_Base_Page_Add_Child(base_page, child);

		lv_obj_t *label = lv_label_create(child);
		lv_label_set_text_fmt(label, "idx = %d", i);
		lv_obj_center(label);

		if (i % 2 == 0)
		{
			lv_obj_set_style_bg_color(child, lv_palette_main(LV_PALETTE_PURPLE), LV_PART_MAIN);
			lv_obj_set_style_bg_opa(child, LV_OPA_80, LV_PART_MAIN);
			lv_obj_set_style_border_color(child, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);
			lv_obj_set_style_border_width(child, 1, LV_PART_MAIN);
		}
	}
}
#elif ZH_DEMO_ARC
void Zh_Demo_Create(void)
{
	lv_obj_t *arc = zh_arc_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 300, 5, 270, 360, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED));
	lv_arc_set_range(arc, 0, 360);
	lv_arc_set_value(arc, 20);
	lv_obj_center(arc);
}
#elif ZH_DEMO_CHART
void Zh_Demo_Create(void)
{
	lv_obj_t *chart = zh_chart_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 300, 200, LV_CHART_TYPE_BAR, 10, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
	lv_obj_center(chart);

	lv_chart_series_t *ser1 = lv_chart_add_series(chart, lv_palette_lighten(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);
	lv_chart_series_t *ser2 = lv_chart_add_series(chart, lv_palette_darken(LV_PALETTE_GREEN, 2), LV_CHART_AXIS_PRIMARY_Y);

	for (uint8_t i = 0; i < 12; i++)
	{
		lv_chart_set_next_value(chart, ser1, lv_rand(10, 60));
		lv_chart_set_next_value(chart, ser2, lv_rand(50, 90));
	}
	lv_chart_refresh(chart);
}
#elif ZH_DEMO_BAR
void Zh_Demo_Create(void)
{
	lv_obj_t *bar = zh_bar_create(lv_scr_act(), NULL, LV_ALIGN_CENTER, 0, 0, 300, 15,
								  60, 60, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), 75, 100);
	lv_obj_center(bar);
}
#elif ZH_DEMO_BEZIER_LINE

#include <math.h>
#include <stdio.h>

uint16_t isqrt_shift(uint32_t num) {
    uint32_t res = 0, bit = 1UL << 30; // 支持32位输入防溢出
    while (bit > num) bit >>= 2;
    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return (uint16_t)res;
}

// 优化后的步数计算函数
static int calculate_optimized_steps(lv_point_t start, lv_point_t end, int line_width) {
    // 1. 坐标差计算（64位防溢出）
    int64_t dx = (int64_t)(end.x - start.x);
    int64_t dy = (int64_t)(end.y - start.y);
    
    // 2. 曲率感知计算（引入Y轴变化率）
    float y_diff_ratio = fabs(dy) / (fabs(dx) + 1e-5); // 网页6曲率相关推导[6](@ref)
    float curvature = fabs(2 * (dx * (end.y - start.y) - dy * (end.x - start.x))) / 
                     pow(dx*dx + dy*dy, 1.5); // 网页7曲率公式[7](@ref)
    
    // 3. 动态混合距离计算
    int64_t manhattan = llabs(dx) + llabs(dy);
    int64_t chebyshev = LV_MAX(llabs(dx), llabs(dy));
    int hybrid_dist = (manhattan * 3 + chebyshev * 7) / 10; // 网页2混合距离优化[2](@ref)
    
    // 4. 线宽补偿因子
    int width_factor = line_width / 2 + 1; // 网页1线宽关联逻辑[1](@ref)
    
    // 5. 动态步数计算
    int base_steps = isqrt_shift(hybrid_dist); // 网页3整数优化[3](@ref)
    int dynamic_steps = (int)(base_steps * (1.0 + 0.5 * curvature + 0.3 * y_diff_ratio));
    
    return LV_MAX(dynamic_steps / width_factor, 100); // 最小步数约束
}
// 修改后的控制点生成逻辑
void cubic_bezier_smooth(lv_point_t start, lv_point_t end, lv_point_t curve_points[], int numSteps) {
    // 计算主方向向量
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float dist = sqrt(dx*dx + dy*dy);

    // 生成带垂直偏移的控制点（关键修改）
    lv_point_t cp1 = {
        .x = start.x + dx*0.25 - dy*0.15, // 横向25% + 垂直15%偏移
        .y = start.y + dy*0.25 + dx*0.15  // 产生曲率的关键
    };
    
    lv_point_t cp2 = {
        .x = end.x - dx*0.25 - dy*0.15,
        .y = end.y - dy*0.25 + dx*0.15
    };

    // 贝塞尔曲线计算（保持不变）
    for(int i=0; i<=numSteps; i++){
        float t = (float)i/numSteps;
        float u = 1.0 - t;
        curve_points[i].x = u*u*u*start.x + 3*u*u*t*cp1.x + 3*u*t*t*cp2.x + t*t*t*end.x;
        curve_points[i].y = u*u*u*start.y + 3*u*u*t*cp1.y + 3*u*t*t*cp2.y + t*t*t*end.y;
    }
}

void Zh_Demo_Create(void)
{
	uint16_t temp_first = 100;
	uint16_t temp_second = 120;
	lv_point_t start = {100, 0};
	lv_point_t end = {200, 0};
	start.y = temp_first;
	end.y = temp_second;

	int numSteps = 300; // 控制曲线精度

	numSteps = calculate_optimized_steps(start, end, 4); // 计算步数

	static lv_point_t curve[466];
	cubic_bezier_smooth(start, end, curve, numSteps);

	static lv_style_t style_line;
	lv_style_init(&style_line);
	lv_style_set_line_width(&style_line, 2);
	lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
	lv_style_set_line_rounded(&style_line, true);

	/*Create a line and apply the new style*/
	lv_obj_t *line1;
	line1 = lv_line_create(lv_screen_active());
	lv_line_set_points(line1, curve, numSteps + 1); /*Set the points*/
	lv_obj_add_style(line1, &style_line, 0);
	lv_obj_center(line1);
}
#elif ZH_DEMO_CANVAS
void Zh_Demo_Create(void)
{
	lv_obj_set_style_bg_color(lv_screen_active(), lv_palette_lighten(LV_PALETTE_YELLOW, 4), 0);

	LV_DRAW_BUF_DEFINE_STATIC(draw_buf, 466, 466, LV_COLOR_FORMAT_ARGB8888);
	LV_DRAW_BUF_INIT_STATIC(draw_buf);
	lv_obj_t *canvas = lv_canvas_create(lv_screen_active());
	lv_canvas_set_draw_buf(canvas, &draw_buf);
	lv_obj_center(canvas);
	lv_canvas_fill_bg(canvas, lv_color_hex(0xFF0000), LV_OPA_COVER);

#if 0
	uint32_t x;
    uint32_t y;
    for(y = 10; y < 20; y++) {
        for(x = 5; x < 75; x++) {
            lv_canvas_set_px(canvas, x, y, lv_palette_main(LV_PALETTE_BLUE), LV_OPA_50);
        }
    }
#endif
	lv_layer_t layer;
	lv_canvas_init_layer(canvas, &layer);

	lv_draw_rect_dsc_t dsc;
	lv_draw_rect_dsc_init(&dsc);
	dsc.bg_color = lv_palette_main(LV_PALETTE_BLUE);
	dsc.outline_opa = LV_OPA_COVER;
	dsc.radius = 5;
	lv_area_t coords = {0, 0, 350, 350};
	lv_draw_rect(&layer, &dsc, &coords);

	// draw mask
	lv_area_t outer_area = {200, 200, 400, 400};
	lv_draw_mask_rect_dsc_t outer_mask_dsc;
	lv_draw_mask_rect_dsc_init(&outer_mask_dsc);
	outer_mask_dsc.radius = 200;
	outer_mask_dsc.area = outer_area;
	lv_draw_mask_rect(&layer, &outer_mask_dsc);

	lv_canvas_finish_layer(canvas, &layer);
}
#elif ZH_DEMO_FLEX_PAGE
#define DESCRIPTION_LABEL_W 368
#define LEVEL_TITLE_LABEL_W 332
#define PADDING_HOR 10
#define PADDING_VER 20
#define MARGIN_BOTTOM 48
#define CONT_HOR_H 48
#define INDICATOR_W 8
#define INDICATOR_H 32

enum {
    POWER_CONSUMPTION_LEVEL_1 = 0,
    POWER_CONSUMPTION_LEVEL_2,
    POWER_CONSUMPTION_LEVEL_3,
    POWER_CONSUMPTION_LEVEL_NUM_MAX,
};

static char *str_page_title = NULL;
static char *str_level_1_title = NULL;
static char *str_level_2_title = NULL;
static char *str_level_3_title = NULL;
static char *str_level_1_desc = NULL;
static char *str_level_2_desc = NULL;
static char *str_level_3_desc = NULL;
static char *str_page_desc = NULL;

static void init_power_consumption_tips_text(void)
{
    str_page_title = "high_power_consumption_level.watchface";
    str_level_1_title = "high_power_consumption_level1.watchface";
    str_level_2_title = "high_power_consumption_level2.watchface";
    str_level_3_title = "high_power_consumption_level3.watchface";
    str_level_1_desc = "high_power_consumption_level1_tips.watchface";
    str_level_2_desc = "high_power_consumption_level2_tips.watchface";
    str_level_3_desc = "high_power_consumption_level3_tips.watchface";
    str_page_desc = "high_power_consumption_desc.watchface";
}

static void create_consumption_level_labels(lv_obj_t *parent, uint8_t level)
{
	lv_obj_t *cont_blocks = lv_obj_create(parent);
	lv_obj_remove_style_all(cont_blocks);
	lv_obj_set_size(cont_blocks, DESCRIPTION_LABEL_W, LV_SIZE_CONTENT);
	lv_obj_set_style_bg_opa(cont_blocks, LV_OPA_TRANSP, 0);

	lv_obj_t *cont_hor = lv_obj_create(cont_blocks);
	lv_obj_remove_style_all(cont_hor);
	lv_obj_set_size(cont_hor, DESCRIPTION_LABEL_W, CONT_HOR_H);
	lv_obj_set_style_bg_opa(cont_hor, LV_OPA_TRANSP, 0);

	lv_obj_t *indicator = lv_obj_create(cont_hor);
	lv_obj_remove_style_all(indicator);
	lv_obj_set_size(indicator, INDICATOR_W, INDICATOR_H);
	lv_obj_set_style_bg_opa(indicator, LV_OPA_COVER, 0);
	lv_obj_set_style_radius(indicator, 32, 0);
	lv_obj_align(indicator, LV_ALIGN_LEFT_MID, 0, 0);

	lv_obj_t *label_level_title = lv_label_create(cont_hor);
	lv_obj_set_width(label_level_title, LEVEL_TITLE_LABEL_W);
	lv_obj_set_style_text_color(label_level_title,
								lv_color_make(0x99, 0x99, 0x99), 0);
	lv_obj_set_style_text_align(label_level_title, LV_TEXT_ALIGN_LEFT, 0);
	lv_label_set_long_mode(label_level_title, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_align_to(label_level_title, indicator, LV_ALIGN_OUT_RIGHT_MID,
					PADDING_HOR, 0);

	lv_obj_t *label_level_desc = lv_label_create(cont_blocks);
	lv_obj_set_width(label_level_desc, LEVEL_TITLE_LABEL_W);
	lv_obj_set_style_text_color(label_level_desc,
								lv_color_make(0xFF, 0xFF, 0xFF), 0);
	lv_obj_set_style_text_align(label_level_desc, LV_TEXT_ALIGN_LEFT, 0);
	lv_label_set_long_mode(label_level_desc, LV_LABEL_LONG_WRAP);
	lv_obj_align_to(label_level_desc, cont_hor, LV_ALIGN_OUT_BOTTOM_MID,
					0, PADDING_VER);
	// lv_obj_set_style_border_width(label_level_desc, 1, 0);
	// lv_obj_set_style_border_color(label_level_desc, lv_palette_main(LV_PALETTE_RED), 0);

	if (level == POWER_CONSUMPTION_LEVEL_1)
	{
		lv_obj_set_style_bg_color(indicator, lv_color_make(0x10, 0xC5, 0x50), 0);
		lv_label_set_text(label_level_title, str_level_1_title);
		lv_label_set_text(label_level_desc, str_level_1_desc);
	}
	else
	{
		lv_obj_set_style_bg_color(indicator,
								  level == POWER_CONSUMPTION_LEVEL_2
									  ? lv_color_make(0xEC, 0xA2, 0x00)
									  : lv_color_make(0xE5, 0x2C, 0xC0),
								  0);
		lv_label_set_text(label_level_title,
						  level == POWER_CONSUMPTION_LEVEL_2
							  ? str_level_2_title
							  : str_level_3_title);
		lv_label_set_text(label_level_desc,
						  level == POWER_CONSUMPTION_LEVEL_2
							  ? str_level_2_desc
							  : str_level_3_desc);
	}
}

static void on_create(lv_obj_t *root)
{
	init_power_consumption_tips_text();

	lv_obj_t *cont = root;
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_column(cont, PADDING_VER, 0);
    lv_obj_set_style_margin_bottom(cont, MARGIN_BOTTOM, 0);
	lv_obj_set_style_bg_color(cont, lv_color_make(0,0,0), 0);
	for (uint8_t idx = 0; idx < POWER_CONSUMPTION_LEVEL_NUM_MAX; idx++)
	{
		create_consumption_level_labels(cont, idx);
	}

	lv_obj_t *label_page_desc = lv_label_create(cont);
	lv_obj_set_size(label_page_desc, DESCRIPTION_LABEL_W, LV_SIZE_CONTENT);
	lv_obj_set_style_text_color(label_page_desc,
								lv_color_make(0x99, 0x99, 0x99), 0);
	lv_obj_set_style_text_align(label_page_desc, LV_TEXT_ALIGN_LEFT, 0);
	lv_label_set_long_mode(label_page_desc, LV_LABEL_LONG_WRAP);
	lv_label_set_text(label_page_desc, str_page_desc);
}

void Zh_Demo_Create(void)
{
	on_create(lv_screen_active());
}
#elif ZH_DEMO_WEATHER_LINE
// 原始数据参数
#define ORIGIN_POINTS 5
static float raw_data[] = {18.5, 22.0, 19.8, 17.3, 20.1}; // 示例温度数据
static const char* labels[] = {"09:00", "12:00", "15:00", "18:00", "21:00"};

// 处理参数配置
#define INTERPOLATION_RATE 5  // 插值倍数
#define SMOOTH_WINDOW 4        // 滤波窗口
#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 200

float h[ORIGIN_POINTS], alpha[ORIGIN_POINTS], l[ORIGIN_POINTS], mu[ORIGIN_POINTS], z[ORIGIN_POINTS], c[ORIGIN_POINTS], b[ORIGIN_POINTS], d[ORIGIN_POINTS];
/* 三次样条插值核心算法 */
static void cubic_spline(const float *x, const float *y, int n,
						 float *new_x, float *new_y, int new_n)
{
	// float h[n], alpha[n], l[n], mu[n], z[n], c[n], b[n], d[n];

	// 计算步长
	for (int i = 0; i < n - 1; i++)
		h[i] = x[i + 1] - x[i];

	// 构建三对角矩阵
	alpha[0] = 3 * (y[1] - y[0]) / h[0];
	for (int i = 1; i < n - 1; i++)
		alpha[i] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);

	// 托马斯算法求解
	l[0] = 1;
	mu[0] = z[0] = 0;
	for (int i = 1; i < n - 1; i++)
	{
		l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
		mu[i] = h[i] / l[i];
		z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
	}
	l[n - 1] = 1;
	z[n - 1] = c[n - 1] = 0;

	// 回代求解系数
	for (int j = n - 2; j >= 0; j--)
		c[j] = z[j] - mu[j] * c[j + 1];
	for (int j = 0; j < n - 1; j++)
	{
		b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
		d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
	}

	// 生成插值点
	int idx = 0;
	for (int i = 0; i < n - 1; i++)
	{
		float step = (x[i + 1] - x[i]) / (new_n / (n - 1));
		for (float t = x[i]; t <= x[i + 1]; t += step)
		{
			float dx = t - x[i];
			new_y[idx] = y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
			new_x[idx++] = t;
			if (idx >= new_n)
				return;
		}
	}
}

/* 滑动平均滤波实现 */
static void moving_average(float *data, int len)
{
	float buffer[SMOOTH_WINDOW];
	for (int i = SMOOTH_WINDOW; i < len; i++)
	{
		float sum = 0;
		for (int j = 0; j < SMOOTH_WINDOW; j++)
			sum += data[i - j];
		data[i] = sum / SMOOTH_WINDOW;
	}
}

/* 创建画布对象 */
static lv_obj_t *create_canvas(lv_obj_t *parent)
{
	lv_obj_t *canvas = lv_canvas_create(parent);
	lv_canvas_set_buffer(canvas, lv_mem_alloc(CANVAS_WIDTH * CANVAS_HEIGHT * 4),
						 CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888);

	// 绘制渐变背景
	lv_draw_rect_dsc_t bg_style;
	lv_draw_rect_dsc_init(&bg_style);
	bg_style.bg_grad.dir = LV_GRAD_DIR_VER;
	bg_style.bg_grad.stops[0].color = lv_color_hex(0x1E90FF);
	bg_style.bg_grad.stops[1].color = lv_color_hex(0x0047AB);
	lv_canvas_draw_rect(canvas, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, &bg_style);

	return canvas;
}

/* 主绘制函数 */
void draw_processed_curve(lv_obj_t *canvas)
{
	// 数据预处理
	int interp_len = ORIGIN_POINTS * INTERPOLATION_RATE;
	float *interp_x = lv_mem_alloc(interp_len * sizeof(float));
	float *interp_y = lv_mem_alloc(interp_len * sizeof(float));

	cubic_spline((float[]){0, 1, 2, 3, 4}, raw_data, ORIGIN_POINTS,
				 interp_x, interp_y, interp_len);
	moving_average(interp_y, interp_len);

	// 坐标映射
	lv_point_t points[25];
	float y_min = 17.0, y_max = 22.0; // 动态计算或预设范围
	for (int i = 0; i < interp_len; i++)
	{
		points[i].x = (CANVAS_WIDTH * i) / (interp_len - 1);
		points[i].y = CANVAS_HEIGHT - (interp_y[i] - y_min) / (y_max - y_min) * (CANVAS_HEIGHT - 40) + 20;
	}

	// 绘制曲线
	lv_draw_line_dsc_t line_style;
	lv_draw_line_dsc_init(&line_style);
	line_style.color = lv_color_white();
	line_style.width = 3;
	line_style.blend_mode = LV_BLEND_MODE_ADDITIVE;
	lv_canvas_draw_line(canvas, points, interp_len, &line_style);

	// 添加标注
	lv_draw_label_dsc_t label_style;
	lv_draw_label_dsc_init(&label_style);
	label_style.color = lv_color_white();
	for (int i = 0; i < ORIGIN_POINTS; i++)
	{
		lv_canvas_draw_text(canvas, labels[i],
							i * (CANVAS_WIDTH / (ORIGIN_POINTS - 1)) - 30,
							CANVAS_HEIGHT - 20, &label_style);
	}

	// 释放内存
	lv_mem_free(interp_x);
	lv_mem_free(interp_y);
}

/* UI初始化 */
void Zh_Demo_Create(void)
{
	lv_obj_t *canvas = create_canvas(lv_screen_active());
	draw_processed_curve(canvas);

	// 添加标题
	lv_draw_label_dsc_t title_style;
	lv_draw_label_dsc_init(&title_style);
	title_style.font = &lv_font_montserrat_24;
	lv_canvas_draw_text(canvas, "温度变化曲线", 10, 10, &title_style);
}
#elif ZH_DEMO_PATH_VECTOR

#define CANVAS_WIDTH  150
#define CANVAS_HEIGHT 150

static lv_fpoint_t pts[3] = {{10, 10}, {130, 130}, {10, 130}};
void Zh_Demo_Create(void)
{
	/*Create a buffer for the canvas*/
    LV_DRAW_BUF_DEFINE(draw_buf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_COLOR_FORMAT_ARGB8888);

	/*Create a canvas and initialize its palette*/
	lv_obj_t *canvas = lv_canvas_create(lv_screen_active());
	lv_canvas_set_draw_buf(canvas, &draw_buf);
	lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_COVER);
	lv_obj_center(canvas);

	lv_layer_t layer;
	lv_canvas_init_layer(canvas, &layer);

	lv_vector_dsc_t *dsc = lv_vector_dsc_create(&layer);
	lv_vector_path_t *path = lv_vector_path_create(LV_VECTOR_PATH_QUALITY_MEDIUM);

	lv_vector_path_move_to(path, &pts[0]);
	lv_vector_path_line_to(path, &pts[1]);
	lv_vector_path_line_to(path, &pts[2]);
	lv_vector_path_close(path);

	lv_vector_dsc_set_fill_color(dsc, lv_color_make(0x00, 0x80, 0xff));
	lv_vector_dsc_add_path(dsc, path);

	lv_draw_vector(dsc);
	lv_vector_path_delete(path);
	lv_vector_dsc_delete(dsc);

	lv_canvas_finish_layer(canvas, &layer);
}
#else 
void Zh_Demo_Create(void)
{
	    /*Create a buffer for the canvas*/
		LV_DRAW_BUF_DEFINE_STATIC(draw_buf, 300, 300, LV_COLOR_FORMAT_ARGB8888);
		LV_DRAW_BUF_INIT_STATIC(draw_buf);
	
		/*Create a canvas and initialize its palette*/
		lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
		lv_canvas_set_draw_buf(canvas, &draw_buf);
		lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_TRANSP);
		lv_obj_center(canvas);
	
		lv_layer_t layer;
		lv_canvas_init_layer(canvas, &layer);
	
		lv_draw_line_dsc_t dsc;
		lv_draw_line_dsc_init(&dsc);
		dsc.color = lv_palette_main(LV_PALETTE_RED);
		dsc.width = 4;
		dsc.round_end = 1;
		dsc.round_start = 1;
		dsc.p1.x = 15;
		dsc.p1.y = 15;
		dsc.p2.x = 35;
		dsc.p2.y = 10;
		lv_draw_line(&layer, &dsc);
		dsc.p1.x = 35;
		dsc.p1.y = 35;
		dsc.p2.x = 75;
		dsc.p2.y = 50;
		lv_draw_line(&layer, &dsc);
		lv_canvas_finish_layer(canvas, &layer);
}
#endif
