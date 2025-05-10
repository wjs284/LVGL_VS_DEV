#include "zh_common_ui_interface.h"

/**
 * description					创建 cont 控件：主要用于承载其他控件
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					宽
 * lv_coord_t h					高
 * lv_event_cb_t event_cb		事件回调
 **/
lv_obj_t *zh_cont_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, lv_event_cb_t event_cb)
{
	lv_obj_t *cont = lv_obj_create(parent);
	lv_obj_remove_style_all(cont);//移除所有样式
	lv_obj_set_size(cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT);//自适应子对象大小
#if 0
	lv_obj_set_style_bg_color(cont, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(cont, LV_OPA_80, LV_PART_MAIN);
	lv_obj_set_style_border_color(cont, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
	lv_obj_set_style_border_width(cont, 1, LV_PART_MAIN);
#endif 
	if (w != 0)
		lv_obj_set_width(cont, w);
	if (h != 0)
		lv_obj_set_height(cont, h);

	if (align_parent)
		lv_obj_align_to(cont, align_parent, align, x, y);
	else
		lv_obj_set_pos(cont, x, y);

	if (event_cb)
		lv_obj_add_event_cb(cont, event_cb, LV_EVENT_SHORT_CLICKED, NULL);

	return cont;
}

/**
 * description					创建图片
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * const void *src_img			图片资源
**/
lv_obj_t *zh_img_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *src_img)
{
	lv_obj_t *img = lv_image_create(parent);
	lv_image_set_src(img, (lv_img_dsc_t *)src_img);
	if (align_parent)
		lv_obj_align_to(img, align_parent, align, x, y);
	else
		lv_obj_set_pos(img, x, y);

	return img;
}

lv_obj_t *zh_label_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
						  const char *str, lv_color_t color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line)
{
	lv_obj_t *label = lv_label_create(parent);
	lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
	//lv_obj_set_style_text_font(label, &lv_font_montserrat_38, LV_PART_MAIN);
#if 0
	lv_obj_set_style_bg_color(label, lv_palette_main(LV_PALETTE_YELLOW), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(label, LV_OPA_80, LV_PART_MAIN);
	lv_obj_set_style_border_color(label, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
	lv_obj_set_style_border_width(label, 1, LV_PART_MAIN);
#endif
	lv_label_set_long_mode(label, long_mode);
	if (w == 0 || h == 0)
	{
		lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
		if (w)
			lv_obj_set_width(label, w);
		if (h)
			lv_obj_set_height(label, h);
	}
	else
	{
		lv_obj_set_size(label, w, h);
	}

	lv_label_set_text(label, str);

	if (align_parent)
		lv_obj_align_to(label, align_parent, align, x, y);
	else
		lv_obj_set_pos(label, x, y);

	lv_obj_set_style_text_align(label, label_align, LV_PART_MAIN);

	return label;
}

/**
 * description					创建按键：普通按键
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					按键宽
 * lv_coord_t h					按键高
 * uint16_t radius				按键曲率
 * lv_color_t color				按键颜色
 * lv_opa_t opa					按键透明度
 * int32_t transform_w			按下时的按键宽度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
 * int32_t transform_h			按下时的按键高度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
 * lv_event_cb_t event_cb		按键回调
 **/
lv_obj_t *zh_button_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
						   int32_t radius, lv_color_t color, lv_opa_t opa, int32_t transform_w, int32_t transform_h, lv_event_cb_t event_cb)
{
	lv_obj_t *button = lv_button_create(parent);
	lv_obj_remove_style_all(button);
	lv_obj_set_size(button, w, h);
	lv_obj_set_style_radius(button, radius, LV_PART_MAIN);
	lv_obj_set_style_bg_color(button, color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(button, opa, LV_PART_MAIN);

	if (transform_w != 0)
		lv_obj_set_style_transform_width(button, transform_w, LV_STATE_PRESSED);
	if (transform_h != 0)
		lv_obj_set_style_transform_height(button, transform_h, LV_STATE_PRESSED);

	if (event_cb)
	{
		lv_obj_add_event_cb(button, event_cb, LV_EVENT_SHORT_CLICKED, NULL);
	}

	if (align_parent)
		lv_obj_align_to(button, align_parent, align, x, y);
	else
		lv_obj_set_pos(button, x, y);

	return button;
}

/**
* description					创建按键：普通按键+小图片
* lv_obj_t *parent				基于 parent 创建
* lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
* lv_align_t align				对齐方式
* lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
* lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
* lv_coord_t w					按键宽
* lv_coord_t h					按键高
* uint16_t radius				按键曲率
* lv_color_t color				按键颜色
* lv_opa_t opa					按键透明度
* int16_t transform_w			按下时的按键宽度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
* int16_t transform_h			按下时的按键高度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
* const void *fg_img			按键上的图标
* lv_event_cb_t event_cb		按键回调
**/
lv_obj_t *zh_button_with_icon_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
									 int32_t radius, lv_color_t color, lv_opa_t opa, int32_t transform_w, int32_t transform_h, const void *fg_img, lv_event_cb_t event_cb)
{
	lv_obj_t *bg_btn = zh_button_create(parent, align_parent, align, x, y, w, h, radius, color, opa, transform_w, transform_h, event_cb);
	zh_img_create(bg_btn, bg_btn, LV_ALIGN_CENTER, 0, 0, fg_img);
	return bg_btn;
}

/**
* description						创建按键：普通按键+字符串
* lv_obj_t *parent					基于 parent 创建
* lv_obj_t *align_parent			基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
* lv_align_t align					对齐方式
* lv_coord_t x						x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
* lv_coord_t y						y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
* lv_coord_t w						按键宽
* lv_coord_t h						按键高
* uint16_t radius					按键曲率
* lv_color_t btn_color				按键颜色
* lv_opa_t opa						按键透明度
* int16_t transform_w				按下时的按键宽度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
* int16_t transform_h				按下时的按键高度放大或者缩小效果：0:无效果，负数:缩小像素，正数:放大像素
* lv_coord_t txt_w					宽：如果文本宽度根据实际显示的来，则写0
* lv_coord_t txt_h					高：如果文本高度根据实际显示的来，则写0
* const char *txt					按键上的字符串
* lv_color_t txt_color				label 颜色
* lv_label_align_t label_align		label 对齐方式
* lv_label_long_mode_t long_mode	label 模式
* uint16_t f_size					字体大小
* uint8_t line						行数：LV_LABEL_LONG_DOT 模式（显示...）才生效，非 LV_LABEL_LONG_DOT 模式写0
* lv_event_cb_t event_cb			按键回调
**/
lv_obj_t *zh_button_with_txt_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
									int32_t radius, lv_color_t btn_color, lv_opa_t opa, int32_t transform_w, int32_t transform_h,
									uint16_t txt_w, uint16_t txt_h, const char *txt, lv_color_t txt_color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line, lv_event_cb_t event_cb)
{
	lv_obj_t *bg_btn = zh_button_create(parent, align_parent, align, x, y, w, h, radius, btn_color, opa, transform_w, transform_h, event_cb);
	zh_label_create(bg_btn, bg_btn, LV_ALIGN_CENTER, 0, 0, txt_w, txt_h, txt, txt_color, label_align, long_mode, f_size, line);
	return bg_btn;
}

/**
 * description					图片按键回调
 **/
static void zh_img_button_event_cb(lv_event_t *e)
{
	lv_event_code_t event = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	lv_event_cb_t callback = (lv_event_cb_t)lv_event_get_user_data(e);
	if (event == LV_EVENT_PRESSED)
	{
		lv_image_set_scale(obj, 235);
		// lv_obj_set_style_image_recolor_opa(obj, LV_OPA_80, LV_PART_MAIN);
	}
	else if (LV_EVENT_SHORT_CLICKED == event)
	{
		lv_obj_set_style_image_recolor_opa(obj, LV_OPA_50, LV_PART_MAIN);
		callback(e);
	}
	else if (event == LV_EVENT_RELEASED || event == LV_EVENT_PRESS_LOST)
	{
		lv_image_set_scale(obj, 255);
		lv_obj_set_style_image_recolor_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
	}
}

/**
* description					创建图片按键：仅一张图片的按键
* lv_obj_t *parent				基于 parent 创建
* lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
* lv_align_t align				对齐方式
* lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
* lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
* const void *src_img			图片资源
* lv_event_cb_t event_cb		按键回调
**/
lv_obj_t *zh_img_button_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *src_img, lv_event_cb_t event_cb)
{
	lv_obj_t *img_btn = zh_img_create(parent, align_parent, align, x, y, src_img);
	lv_obj_add_flag(img_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_remove_flag(img_btn, LV_OBJ_FLAG_SCROLLABLE);

	if (event_cb)
		lv_obj_add_event_cb(img_btn, zh_img_button_event_cb, LV_EVENT_ALL, (void *)event_cb);
	return img_btn;
}

/**
 * description					创建图片按键：图片按键+小图片
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * const void *bg_img			按键图片
 * const void *fg_img			按键上的图标
 * lv_event_cb_t event_cb		按键回调
 **/
lv_obj_t *zh_img_button_with_icon_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *bg_img, const void *fg_img, lv_event_cb_t event_cb)
{
	lv_obj_t *img_btn = zh_img_create(parent, align_parent, align, x, y, bg_img);
	lv_obj_add_flag(img_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_remove_flag(img_btn, LV_OBJ_FLAG_SCROLLABLE);

	if (fg_img != NULL)
		zh_img_create(img_btn, img_btn, LV_ALIGN_CENTER, 0, 0, fg_img);

	if (event_cb)
		lv_obj_add_event_cb(img_btn, zh_img_button_event_cb, LV_EVENT_ALL, (void *)event_cb);

	return img_btn;
}

/**
* description						创建图片按键：图片按键+字符串
* lv_obj_t *parent					基于 parent 创建
* lv_obj_t *align_parent			基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
* lv_align_t align					对齐方式
* lv_coord_t x						x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
* lv_coord_t y						y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
* const void *bg_img				按键图片
* lv_coord_t txt_w					宽：如果文本宽度根据实际显示的来，则写0
* lv_coord_t txt_h					高：如果文本高度根据实际显示的来，则写0
* const char *txt					按键上的字符串
* lv_color_t color					label 颜色
* lv_label_align_t label_align		label 对齐方式
* lv_label_long_mode_t long_mode	label 模式
* uint16_t f_size					字体大小
* uint8_t line						行数：LV_LABEL_LONG_DOT 模式（显示...）才生效，非 LV_LABEL_LONG_DOT 模式写0
* lv_event_cb_t event_cb			按键回调
**/
lv_obj_t *zh_img_button_with_txt_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *bg_img,
										uint16_t txt_w, uint16_t txt_h, const char *txt, lv_color_t txt_color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line, lv_event_cb_t event_cb)
{
	lv_obj_t *img_btn = zh_img_create(parent, align_parent, align, x, y, bg_img);
	lv_obj_add_flag(img_btn, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_remove_flag(img_btn, LV_OBJ_FLAG_SCROLLABLE);

	if (event_cb)
		lv_obj_add_event_cb(img_btn, zh_img_button_event_cb, LV_EVENT_ALL, (void *)event_cb);

	zh_label_create(img_btn, img_btn, LV_ALIGN_CENTER, 0, 0, txt_w, txt_h, txt, txt_color, label_align, long_mode, f_size, line);

	return img_btn;
}

/**
 * description					创建圆环（用 lv_arc_set_angles 接口设置圆环当前旋转的角度）
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t arc_size			圆环的大小（宽、高）
 * lv_coord_t arc_width			圆环的环的宽度
 * uint16_t start_angles		圆环起始角度：0~360，圆环的正三点钟方向是0度，顺时针转
 * uint16_t bg_angles			圆环背景总的角度：一圈是360，半圈是180
 * lv_color_t bg_color			圆环背景色：暗色
 * lv_color_t indic_color		圆环前景色：亮色
 **/
lv_obj_t *zh_arc_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y,
						lv_coord_t arc_size, lv_coord_t arc_width, int32_t start_angles, int32_t bg_angles, lv_color_t bg_color, lv_color_t indic_color)
{
	lv_obj_t *ret_arc = lv_arc_create(parent);
	lv_obj_remove_flag(ret_arc, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_remove_style(ret_arc, NULL, LV_PART_KNOB);
	lv_obj_remove_style(ret_arc, NULL, LV_PART_MAIN);
	lv_obj_set_size(ret_arc, arc_size, arc_size);

	lv_obj_set_style_arc_width(ret_arc, arc_width, LV_PART_MAIN);
	lv_obj_set_style_arc_color(ret_arc, bg_color, LV_PART_MAIN);
	lv_obj_set_style_arc_width(ret_arc, arc_width, LV_PART_INDICATOR);
	lv_obj_set_style_arc_color(ret_arc, indic_color, LV_PART_INDICATOR);

	lv_arc_set_bg_angles(ret_arc, 0, bg_angles);
	lv_arc_set_rotation(ret_arc, start_angles);

	if (align_parent)
		lv_obj_align_to(ret_arc, align_parent, align, x, y);
	else
		lv_obj_set_pos(ret_arc, x, y);

	return ret_arc;
}

/**
 * description					创建进度条（如果对象的宽度小于其高度，则可以创建垂直条）
 * lv_obj_t *parent 			基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align 			对齐方式
 * lv_coord_t x 				x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y 				y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w 				宽度
 * lv_coord_t h 				高度
 * uint16_t bg_radius			背景圆角曲率
 * uint16_t ind_radius			前景圆角曲率（0：进度条为直的）
 * lv_color_t bg_color			背景颜色
 * lv_color_t ind_color 		前景颜色
 * int32_t value				设置进度条的值（进度条的值可通过 lv_bar_set_value 设置更新，设置范围：0 ~ range_max）
 * int32_t range_max			最大范围值
 **/
lv_obj_t *zh_bar_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
						int32_t bg_radius, int32_t ind_radius, lv_color_t bg_color, lv_color_t ind_color, int32_t value, int32_t range_max)
{
	lv_obj_t *bar = lv_bar_create(parent);
	lv_obj_set_size(bar, w, h);

	lv_obj_set_style_bg_color(bar, bg_color, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_radius(bar, bg_radius, LV_PART_MAIN);
	lv_obj_set_style_bg_color(bar, ind_color, LV_PART_INDICATOR);
	lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);
	lv_obj_set_style_radius(bar, ind_radius, LV_PART_INDICATOR);

	// if (zh_rtl_display())
	// {
	// 	lv_obj_set_style_base_dir(cont, LV_BASE_DIR_RTL, LV_STATE_DEFAULT);
	// }
	lv_bar_set_range(bar, 0, range_max);
	lv_bar_set_value(bar, value, LV_ANIM_OFF);

	if (align_parent)
		lv_obj_align_to(bar, align_parent, align, x, y);
	else
		lv_obj_set_pos(bar, x, y);

	return bar;
}

/**
 * description					创建柱状图或者折线
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					宽度
 * lv_coord_t h					高度
 * lv_chart_type_t type			创建的是柱状图或者折线
 * lv_coord_t point_count		图表总共有多少个点
 * lv_coord_t y_range_low		图表最低点的值
 * lv_coord_t y_range_hight		图表最高点的值
 * lv_style_int_t line_w		图表线宽
 **/
lv_obj_t *zh_chart_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
						  lv_chart_type_t type, lv_coord_t point_count, lv_chart_axis_t axis, lv_coord_t y_range_low, lv_coord_t y_range_hight)
{
	lv_obj_t *chart = lv_chart_create(parent);
	lv_obj_add_flag(chart, LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

	lv_obj_set_size(chart, w, h);								 // 设置图表的大小
	lv_chart_set_type(chart, type);								 // 设置图表类型为折线图
	lv_chart_set_range(chart, axis, y_range_low, y_range_hight); // 设置图表的范围
	lv_chart_set_point_count(chart, point_count);				 // 设置图表的点数
	lv_chart_set_div_line_count(chart, 10, 10);
	lv_obj_set_style_radius(chart, 60, LV_PART_ITEMS);

	if (align_parent)
		lv_obj_align_to(chart, align_parent, align, x, y);
	else
		lv_obj_set_pos(chart, x, y);

	return chart;
}

#if 0
/**
 * description					创建滚筒
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					宽度
 * lv_coord_t h					高度
 * uint16_t sel_opt				默认显示第几个选项：1~n
 * const char *options			选项内容：每个选项之间用“\n”隔开："1\n2\n3\n4\n5\n6\n7\n8\n9\n10"、"First\nSecond\nThird"
 * lv_roller_mode_t mode		滚轮模式：    LV_ROLLER_MODE_NORMAL：不循环滚动，LV_ROLLER_MODE_INIFINITE：循环滚动
 * uint8_t row_cnt				可见行数
 * lv_label_align_t label_align	滚筒中的文字靠那边对齐
 * uint16_t f_size				滚筒中的文字字号
 * lv_color_t f_color			滚筒中的文字颜色
 *lv_event_cb_t event_cb		滚筒的回调：可用于实时获取滚动的值
**/
lv_obj_t *zh_roller_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
								uint16_t sel_opt, const char *options, lv_roller_mode_t mode, uint8_t row_cnt, lv_label_align_t label_align, uint16_t f_size, lv_color_t f_color, lv_event_cb_t event_cb)
{
	uint8_t line_space = (h - row_cnt * f_size) / (row_cnt * 2);

	lv_obj_t *roller = lv_roller_create(parent, NULL);
	lv_ext_set_local_font(roller, f_size, f_color);
	lv_obj_set_style_local_radius(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_radius(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, 0);

//	lv_obj_set_style_local_outline_width(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, 1);
//	lv_obj_set_style_local_outline_color(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_BLACK);
//	lv_obj_set_style_local_outline_opa(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_OPA_100);
//
//	lv_obj_set_style_local_outline_width(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, 1);
//	lv_obj_set_style_local_outline_color(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
//	lv_obj_set_style_local_outline_opa(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_100);

	lv_obj_set_style_local_bg_color(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_set_style_local_bg_color(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_COLOR_BLACK);

	lv_obj_set_style_local_text_color(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, f_color);//设置未选中字体颜色
	lv_obj_set_style_local_text_opa(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_OPA_100);//设置未选中字体透明度
	lv_obj_set_style_local_text_color(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, f_color);//设置选中字体颜色
	lv_obj_set_style_local_text_opa(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_100);//设置选中字体透明度

	lv_obj_set_style_local_bg_opa(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_OPA_0);
	lv_obj_set_style_local_bg_opa(roller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_0);
	lv_obj_set_style_local_text_line_space(roller, LV_ROLLER_PART_BG, LV_STATE_DEFAULT, line_space);

	lv_obj_t *scrl_roller = lv_page_get_scrllable(roller);
	if (NULL != scrl_roller)
	{
		lv_obj_t *opt_label = lv_obj_get_child(scrl_roller, NULL);
		lv_label_set_long_mode(opt_label, LV_LABEL_LONG_BREAK);
		lv_obj_set_width(opt_label, w);
	}


	lv_obj_set_mirror(roller, false);
	lv_roller_set_align(roller, label_align);
	lv_roller_set_auto_fit(roller, true);
	lv_roller_set_visible_row_count(roller, row_cnt);
	lv_roller_set_anim_time(roller, 100);//脱手后滚动100ms
	#if NOT_USE_AUTO_REALIGN==0
	//lv_obj_set_auto_realign(roller, true);
	#endif
	lv_roller_set_options(roller, options, mode);
	lv_roller_get_option_cnt(roller);
	lv_roller_set_selected(roller, sel_opt, LV_ANIM_OFF);
	lv_obj_set_parent_event(roller, true);
	lv_obj_set_event_cb(roller, event_cb);
	if (align_parent)
	{
		lv_obj_align_to(roller, align_parent, align, x, y);
	#if NOT_USE_AUTO_REALIGN==0
		//lv_obj_set_auto_realign(roller, true);
	#endif
	}
	else
	{
		lv_obj_set_pos(roller, x, y);
	}

	return roller;
}

/**
 * description								创建滚筒（mulroller）
 * lv_obj_t *parent							基于 parent 创建
 * lv_obj_t *align_parent					基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align							对齐方式
 * lv_coord_t x								x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y								y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w								宽度
 * lv_coord_t h								高度

 * const lv_img_dsc_t **dsc_array			图片数组
 * int16_t range_min						最小下标：0
 * int16_t range_max						最大下标：有n个，则写n-1
 * int16_t mid_idx							初始选中第几个（下标，0~n-1）
 * uint8_t int_num							显示多少位，如：1写1，01写2，001写3
 * bool leading_zero						高位是否补0，补0个数与 int_num 对应

 * uint16_t middle_zoom    					缩放中间元素
 * uint16_t lateral_zoom   					缩放外侧元素
 * uint8_t middle_opa						中间部分透明度
 * uint8_t lateral_opa						外侧部分透明度
 * lv_mulroller_align_t mulroller_align		元素将向左或向右、顶部或底部或中心对齐
 * lv_mulroller_circle_mode_t circle_mode	循环模式（无限循环、有限循环）
 * lv_mulroller_opa_mode_t opa_mode			透明度模式（没有opa变化；只有中间元素不同；越靠近边缘，透明度越高）

 * lv_mulroller_appear_cb middle_cb			当元素移动到中间时,调用此函数	 1滚轮停止时调用
 * lv_mulroller_appear_cb middle_cb2		当元素移到侧边时,调用此函数	  	 2滚轮滚动时调用
 * lv_mulroller_appear_cb appear_lt_cb		当元素移到侧边时,调用此函数 	 3滚轮滚动时调用
**/
lv_obj_t *zh_mulroller_create_2(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
									const lv_img_dsc_t **dsc_array, int16_t range_min, int16_t range_max, int16_t mid_idx, uint8_t int_num, bool leading_zero,
									uint16_t middle_zoom, uint16_t lateral_zoom, uint8_t middle_opa, uint8_t lateral_opa, lv_mulroller_align_t mulroller_align, lv_mulroller_circle_mode_t circle_mode, lv_mulroller_opa_mode_t opa_mode,
									lv_mulroller_appear_cb middle_cb, lv_mulroller_appear_cb middle_cb2, lv_mulroller_appear_cb appear_lt_cb)
{
	lv_obj_t *mulroller = lv_mulroller_create(parent, NULL);

	lv_obj_set_mirror(mulroller, false);
	lv_obj_set_size(mulroller, w, h);
	lv_mulroller_set_obj_type(mulroller, MULROLLER_TYPE_IMG_ARRAY);
	lv_mulroller_create_element(mulroller, (range_max - range_min) == 1?2:4, lv_obj_get_width(mulroller), h/3);
	lv_mulroller_ext_t *ext = lv_obj_get_ext_attr(mulroller);
	for (uint8_t i = 0; i < ((range_max - range_min) == 1?2:4); i++)
	{
		lv_obj_t *img_array = ext->ele_tab[i].child;
		lv_img_array_set_img_type(img_array, BASEIMG_TYPE_ARRAY_INDEX);
		lv_img_array_bind_src_array(img_array, dsc_array, 0, 12);
		lv_img_array_set_interval(img_array, 0);
		lv_img_array_set_int_num(img_array, int_num);//显示多少位，如：1写1，01写2，001写3
		lv_img_array_set_leading_zero(img_array, leading_zero);//高位是否补0，补0个数与 lv_img_array_set_int_num 对应
//		lv_img_array_set_float_num(img_array, 2);
//		lv_img_array_set_negative_idx(img_array, 10);
//		lv_img_array_set_point_idx(img_array, 11);
	}
	lv_mulroller_set_align(mulroller, mulroller_align);
	lv_mulroller_set_circle_mode(mulroller, circle_mode);
	if (circle_mode == MULROLLER_CIRCLE_INFINITE)
	{
		lv_mulroller_set_circle_range(mulroller, -9000, 9000);//下标0~n-1
	}
	else
	{
		lv_mulroller_set_circle_range(mulroller, range_min, range_max);//下标0~n-1
	}
	lv_mulroller_set_ori_mid_idx(mulroller, mid_idx);
	lv_mulroller_set_layout_mode(mulroller, MULROLLER_LAYOUT_MID);
	lv_mulroller_set_zoom_range(mulroller, middle_zoom, lateral_zoom);
	lv_mulroller_set_opa_mode(mulroller, opa_mode);
	lv_mulroller_set_opa_range(mulroller, middle_opa, lateral_opa);
	lv_mulroller_set_color_mode(mulroller, MULROLLER_COLOR_POS);
#if (PROJECT_466X466_24BIT_N046_GLOBAL||PROJECT_466X466_24BIT_V08_GLOBAL||PROJECT_360X360_16BIT_P01_GLOBAL)
	lv_mulroller_set_color_range(mulroller, 0XFFFFFF, 0xA5A5A5);
#else
	lv_mulroller_set_color_range(mulroller, 0XFFFFFF, 0XFFFFFF);
#endif
	lv_mulroller_set_middle_cb(mulroller, middle_cb);
	lv_mulroller_set_appear_cb(mulroller, appear_lt_cb);
	lv_mulroller_set_middle_cb2(mulroller, middle_cb2);
	lv_mulroller_encoder_enable(mulroller, true);
	lv_mulroller_validate(mulroller);
	lv_obj_set_parent_event(mulroller, true);
	if (align_parent)
	{
		lv_obj_align_to(mulroller, align_parent, align, x, y);
	#if NOT_USE_AUTO_REALIGN==0
		//lv_obj_set_auto_realign(mulroller, true);
	#endif
	}
	else
	{
		lv_obj_set_pos(mulroller, x, y);
	}
	// lv_mulroller_set_wheel_scale(mulroller,50);
	return mulroller;
}

lv_obj_t *zh_mulroller_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
									const lv_img_dsc_t **dsc_array, int16_t range_min, int16_t range_max, int16_t mid_idx, uint8_t int_num, bool leading_zero,
									uint16_t middle_zoom, uint16_t lateral_zoom, uint8_t middle_opa, uint8_t lateral_opa, lv_mulroller_align_t mulroller_align, lv_mulroller_circle_mode_t circle_mode, lv_mulroller_opa_mode_t opa_mode,
									lv_mulroller_appear_cb middle_cb, lv_mulroller_appear_cb appear_lt_cb)
{
	lv_obj_t *mulroller = lv_mulroller_create(parent, NULL);

	lv_obj_set_mirror(mulroller, false);
	lv_obj_set_size(mulroller, w, h);
	lv_mulroller_set_obj_type(mulroller, MULROLLER_TYPE_IMG_ARRAY);
	lv_mulroller_create_element(mulroller, 4, lv_obj_get_width(mulroller), h/3);
	lv_mulroller_ext_t *ext = lv_obj_get_ext_attr(mulroller);
	for (uint8_t i = 0; i < 4; i++)
	{
		lv_obj_t *img_array = ext->ele_tab[i].child;
		lv_img_array_set_img_type(img_array, BASEIMG_TYPE_ARRAY_INDEX);
		lv_img_array_bind_src_array(img_array, dsc_array, 0, 12);
		lv_img_array_set_interval(img_array, 0);
		lv_img_array_set_int_num(img_array, int_num);//显示多少位，如：1写1，01写2，001写3
		lv_img_array_set_leading_zero(img_array, leading_zero);//高位是否补0，补0个数与 lv_img_array_set_int_num 对应
//		lv_img_array_set_float_num(img_array, 2);
//		lv_img_array_set_negative_idx(img_array, 10);
//		lv_img_array_set_point_idx(img_array, 11);
	}
	lv_mulroller_set_align(mulroller, mulroller_align);
	lv_mulroller_set_circle_mode(mulroller, circle_mode);
	if (circle_mode == MULROLLER_CIRCLE_INFINITE)
	{
		lv_mulroller_set_circle_range(mulroller, -9000, 9000);//下标0~n-1
	}
	else
	{
		lv_mulroller_set_circle_range(mulroller, range_min, range_max);//下标0~n-1
	}
	lv_mulroller_set_ori_mid_idx(mulroller, mid_idx);
	lv_mulroller_set_layout_mode(mulroller, MULROLLER_LAYOUT_MID);
	lv_mulroller_set_zoom_range(mulroller, middle_zoom, lateral_zoom);
	lv_mulroller_set_opa_mode(mulroller, opa_mode);
	lv_mulroller_set_opa_range(mulroller, middle_opa, lateral_opa);
	lv_mulroller_set_color_mode(mulroller, MULROLLER_COLOR_POS);
	lv_mulroller_set_color_range(mulroller, 0Xffffff, 0Xffffff);
	lv_mulroller_set_middle_cb(mulroller, middle_cb);
	lv_mulroller_set_appear_cb(mulroller, appear_lt_cb);
	lv_mulroller_encoder_enable(mulroller, true);
	lv_mulroller_validate(mulroller);
	lv_obj_set_parent_event(mulroller, true);
	if (align_parent)
	{
		lv_obj_align_to(mulroller, align_parent, align, x, y);
	#if NOT_USE_AUTO_REALIGN==0
		//lv_obj_set_auto_realign(mulroller, true);
	#endif
	}
	else
	{
		lv_obj_set_pos(mulroller, x, y);
	}
	lv_mulroller_set_wheel_scale(mulroller,50);
	return mulroller;
}

/**
 * description					创建矩形（可用于创建矩形进度环）
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					宽度
 * lv_coord_t h					高度
 * uint16_t radius				圆角曲率
 * lv_coord_t border_width		边框宽度
 * lv_color_t bg_color			边框背景颜色
 * lv_color_t ind_color			边框前景颜色
 * int32_t value				设置进度环的值（进度环的值可通过 lv_rect_set_value 设置更新，设置范围：0 ~ range_max）
 * int32_t range_max			最大范围值
**/
lv_obj_t *zh_rect_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
							lv_style_int_t radius, lv_coord_t border_width, lv_color_t bg_color, lv_color_t ind_color, int32_t value, int32_t range_max)
{
	lv_obj_t* rect = lv_rect_create(parent, NULL);
	lv_rect_set_size(rect, w, h);

	lv_rect_set_border_width(rect, border_width);
	lv_rect_set_radius(rect, radius);
	lv_rect_set_range(rect, range_max);
	lv_rect_set_color(rect, bg_color, ind_color);
	lv_rect_trigger(rect);
	lv_rect_set_value(rect, value);
	if (align_parent)
	{
		lv_obj_align_to(rect, align_parent, align, x, y);
	#if NOT_USE_AUTO_REALIGN==0
		//lv_obj_set_auto_realign(rect, true);
	#endif
	}
	else
	{
		lv_obj_set_pos(rect, x, y);
	}

	return rect;
}
/**
 * description					创建二维码
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					二维码宽二维码最大宽高是
 * lv_coord_t h					二维码高
 * uint16_t radius				二维码曲率
 * char *code					二维码字符串
 * lv_event_cb_t event_cb		按键回调
**/
lv_obj_t *app_binding_create_qrcode(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,lv_style_int_t radius,char *code, lv_event_cb_t cb)
{
	lv_obj_t *bg_btn = zh_button_create(parent, align_parent, align, x-radius, y-radius, 0, 0,
												radius, LV_COLOR_WHITE, LV_OPA_COVER, 0, 0, NULL);
	lv_obj_t *bg_btn2 = zh_button_create(bg_btn, align_parent, align, x-radius, y-radius, 0, 0,
												radius, LV_COLOR_WHITE, LV_OPA_COVER, 0, 0, NULL);
    lv_obj_t *qrcode = lv_lvsfqrcode_create(bg_btn2, NULL);
    lv_lvsfqrcode_setparam(qrcode, w-radius, LV_COLOR_BLACK, LV_COLOR_WHITE);
    lv_lvsfqrcode_set_text(qrcode, code, strlen(code)+1);
	//rt_kprintf("app_binding_create_qrcode==%d,%d\n",lv_obj_get_width(qrcode),lv_obj_get_height(qrcode));
	lv_obj_set_size(bg_btn, lv_obj_get_width(qrcode) + radius, lv_obj_get_height(qrcode) + radius);
    //lv_obj_align_to(bg_btn, parent, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_size(bg_btn2, lv_obj_get_width(qrcode) + radius-6, lv_obj_get_height(qrcode) + radius-6);
	lv_obj_align_to(bg_btn2, bg_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align_to(qrcode, bg_btn2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_parent_event(qrcode, true);
	lv_page_glue_obj(qrcode, true);
    return bg_btn;
}
/**
 * description					创建条形码
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w					二维码宽二维码最大宽高是
 * lv_coord_t h					二维码高
 * uint16_t radius				二维码曲率
 * char *code					二维码字符串
 * lv_barcode_dir_t dir			方向
 * lv_event_cb_t event_cb		按键回调
**/

lv_obj_t *app_binding_create_barcode(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,lv_style_int_t radius,char *code,lv_barcode_dir_t dir, lv_event_cb_t cb)
{
	lv_obj_t *bg_btn = zh_button_create(parent, align_parent, align, x, y, w, h,
												radius, LV_COLOR_WHITE, LV_OPA_COVER, 0, 0, NULL);

	lv_obj_t *barcode = lv_barcode_create(bg_btn, NULL);
	lv_barcode_set_direction(barcode, dir);
	lv_barcode_set_size(barcode,w-radius-12,h);
	lv_barcode_set_text(barcode, code, 'A');


	lv_obj_align_to(barcode, bg_btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_parent_event(barcode, true);
	lv_page_glue_obj(barcode, true);

    return bg_btn;
}

/**
 * description					创建一个GIF  只需要创建销毁不需要你们管理，最大现在是一个页面8个gif
 * lv_obj_t *parent				基于 parent 创建
 * lv_obj_t *align_parent		基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align				对齐方式
 * lv_coord_t x					x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y					y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * app_page_gif_t page_gif		gif信息用来存储这个页面的gif指针和个数
 * const void *gif_data			gif图片
 * const void *gif_img			IMG
 * uint32_t duration			播放速度ms
**/
lv_obj_t *zh_create_gif(lv_obj_t *parent,lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y,app_page_gif_t *page_gif,const void *gif_data,const void *gif_img, uint32_t duration)
{
	lvsf_gif_anim_t *gif = lvsf_gif_anim_init(parent, gif_data, gif_img, \
										 0, 0, duration, GIF_ANIM_DELAY);
	if (align_parent)
	{
		lv_obj_align_to(gif->gif_img, align_parent, align, x, y);
		#if NOT_USE_AUTO_REALIGN==0
		//lv_obj_set_auto_realign(gif->gif_img, true);
		#endif
	}
	else
	{
		lv_obj_set_pos(gif->gif_img, x, y);
	}
	lvsf_gif_anim_resume(gif);
	lvsf_gif_anim_set_layer(gif, LVSF_GIF_LAYER_BACKGROUND);
	page_gif->gif[page_gif->gif_count] = gif;//默认开
	page_gif->gif_count++;

	rt_kprintf("\r\n zh_create_gif gif = 0x%x\n", gif);
	rt_kprintf("\r\n zh_create_gif=0x%x,%d\n", page_gif, page_gif->gif_count);
	return gif->gif_img;
}
/**
 * description					gif初始化函数
 * app_page_gif_t page_gif		gif信息用来存储这个页面的gif指针和个数
**/
void zh_gif_init(app_page_gif_t *page_gif)
{
	if(!page_gif)
		return ;
	rt_kprintf("\r\n zh_gif_init page_gif = 0x%x\n", page_gif);
	for(uint8_t i =0 ;i< 8;i++)
	{
		page_gif->gif[i] = NULL;
	}
	page_gif->gif_count = 0;
}

/**
 * description					gif delete
 * app_page_gif_t page_gif		gif信息用来存储这个页面的gif指针和个数
**/
void zh_gif_delete(app_page_gif_t *page_gif)
{
	if(!page_gif)
		return ;
	rt_kprintf("\r\n zh_gif_delete page_gif = 0x%x, %d\n", page_gif, page_gif->gif_count);
	for(uint8_t i =0 ;i< 8;i++)
	{
		if(page_gif->gif[i])
		{
			rt_kprintf("\r\n zh_gif_delete=0x%x,0x%x,0x%x\n", page_gif->gif[i], page_gif->gif[i]->parent, page_gif->gif[i]->gif);
			lvsf_gif_anim_pause(page_gif->gif[i]);
			lvsf_gif_anim_deinit(page_gif->gif[i]);

			page_gif->gif[i]= NULL;
		}
	}
	page_gif->gif_count = 0;
}

/**
 * description					创建一个task任务
 * app_page_task_t *page_task	task结构体
 * lv_task_cb_t task_cb			任务回调
 * lv_task_prio_t prio			频率
**/
void zh_create_page_task(app_page_task_t *page_task, lv_task_cb_t task_cb, uint32_t period, lv_task_prio_t prio, void *user_data)
{
    if (NULL == page_task->task)
    {
        page_task->task = lv_task_create(task_cb, period, prio, user_data);//Refresh every second
        page_task->task_count=0;
		lv_task_set_prio(page_task->task, LV_TASK_PRIO_OFF);
    }
}
void zh_start_page_task(app_page_task_t *page_task)
{
	#if !LOCAL_MTBF_TEST
	#if MTBF_TEST
	if(get_user_account_bind_state())
	{
		if (page_task->task)
		{
			lv_task_set_prio(page_task->task, LV_TASK_PRIO_OFF);
		}
        return;
	}else
	{
		if (page_task->task)
		{
			page_task->task_count=0;
			lv_task_reset(page_task->task);
			lv_task_set_prio(page_task->task, LV_TASK_PRIO_MID);
		}
	}
    #endif
	#endif

	if (page_task->task)
	{
		page_task->task_count=0;
		lv_task_reset(page_task->task);
		lv_task_set_prio(page_task->task, LV_TASK_PRIO_MID);
	}
}
void zh_stop_page_task(app_page_task_t *page_task)
{
	if (page_task->task)
	{
		lv_task_set_prio(page_task->task, LV_TASK_PRIO_OFF);
	}
}
void zh_delete_page_task(app_page_task_t *page_task)
{
    if (page_task->task)
    {
        lv_task_del(page_task->task);
        page_task->task = NULL;
    }
}

/**
 * description					小语种从右到左显示：阿拉伯语 希伯来语 印尼语 ...
**/
bool zh_rtl_display(void)
{
	return current_lang_is_arab();
}

//**********************创建一个显示专用控件如 98%***************************//
lv_obj_t *zh_lv_SPO_creat(lv_obj_t *parent, uint16_t h, uint16_t data, uint8_t data_font_size, lv_color_t data_color, const char *unit, uint8_t unit_size, lv_color_t unit_color)
{
	char data_str[30];
	memset(data_str,0,sizeof(data_str));
	sprintf(data_str,"%d",data);
	lv_obj_t *spo_label = NULL;
	lv_obj_t *symble_label = NULL;

	lv_obj_t *bg_cont = lv_obj_create(parent, NULL);
	if(Get_Smart_band_Language() == ENUM_LANGUAGE_HEBREW
	|| Get_Smart_band_Language() == ENUM_LANGUAGE_TURKEY
	)
	{
		spo_label = zh_label_create(bg_cont, bg_cont, LV_ALIGN_IN_RIGHT_MID, 0, 0, 0, 0,
										data_str, data_color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_SROLL_CIRC, data_font_size, 0);
		symble_label = zh_label_create(bg_cont, spo_label, LV_ALIGN_OUT_LEFT_BOTTOM, 0, 0, 0, 0,
										unit, unit_color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_SROLL_CIRC, unit_size, 0);
	}
	else
	{
		spo_label = zh_label_create(bg_cont, bg_cont, LV_ALIGN_IN_LEFT_MID, 0, 0, 0, 0,
										data_str, data_color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_SROLL_CIRC, data_font_size, 0);
		symble_label = zh_label_create(bg_cont, spo_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, 0, 0, 0,
										unit, unit_color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_SROLL_CIRC, unit_size, 0);

	}

	lv_obj_set_size(bg_cont, lv_obj_get_width(spo_label)+lv_obj_get_width(symble_label),h);
#if (PROJECT_410X502_16BIT_V02B_GLOBAL||PROJECT_466X466_24BIT_V08_GLOBAL)//N65B  410_502
	if(Get_Smart_band_Language() == ENUM_LANGUAGE_HEBREW
	|| Get_Smart_band_Language() == ENUM_LANGUAGE_TURKEY
	)
	{
		lv_obj_align_to(symble_label, spo_label, LV_ALIGN_OUT_LEFT_BOTTOM, 0, -9);
	}
	else
	{
		lv_obj_align_to(symble_label, spo_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, -9);
	}
#else
	if(Get_Smart_band_Language() == ENUM_LANGUAGE_HEBREW
	|| Get_Smart_band_Language() == ENUM_LANGUAGE_TURKEY
	)
	{
		lv_obj_align_to(symble_label, spo_label, LV_ALIGN_OUT_LEFT_BOTTOM, 0, -5);
	}
	else
	{
		lv_obj_align_to(symble_label, spo_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, -5);
	}

#endif
	return bg_cont;
}



//****************************创建一个心率进度条**************************//
/**
 * description						创建一個label_图片的整页显示,其中图片固定，文本局部滑动
 * lv_obj_t *parent					基于 parent 创建
 lv_img_dsc_t *img_pic				图片
 * const char *str					label 内容
 * lv_color_t color					label 颜色
 * lv_label_align_t label_align		label 对齐方式
 * lv_label_long_mode_t long_mode	label 模式
 * uint16_t f_size					字体大小
 * uint8_t line						行数：LV_LABEL_LONG_DOT 模式（显示...）才生效，非 LV_LABEL_LONG_DOT 模式写0
**/
//zh_lv_create_label_pic_remind_dis(parent, APP_GET_IMG(A0000_IMG_ICON_2),"请在手机确认配对", LV_COLOR_GRAY, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_BREAK, FONT_BIGL, 0);
lv_obj_t *zh_lv_create_label_pic_remind_dis(lv_obj_t *parent, lv_img_dsc_t *img_pic,const char *str,lv_color_t color, lv_label_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line)
{
	//请在手表确认
	lv_obj_t *bg_btn = zh_multobj_bg_create(parent, parent, LV_ALIGN_CENTER, 0, 0, LV_HOR_RES_MAX - 20*2, 0, 0, LV_COLOR_BLACK, LV_OPA_0);
	lv_obj_t *img = zh_img_create(bg_btn, NULL, LV_ALIGN_CENTER, (lv_obj_get_width(bg_btn)-img_pic->header.w)/2, 0,img_pic);
	lv_obj_t *page = zh_lv_page_create(bg_btn, bg_btn, LV_ALIGN_IN_BOTTOM_MID, 0, 0, LV_HOR_RES_MAX - 20*2, 0, LV_COLOR_BLACK, LV_OPA_0);
	lv_obj_t *label_one = zh_label_create(page, page, LV_ALIGN_CENTER, 0, 0, LV_HOR_RES_MAX - 20*2, 0, str, color, label_align, long_mode, f_size, line);
	lv_obj_set_height(parent, LV_VER_RES_MAX - 31 -20);

	if(lv_obj_get_height(label_one)< (LV_VER_RES_MAX-20-lv_obj_get_height(img)-31))
	{
		lv_obj_set_height(page, lv_obj_get_height(label_one));
		lv_obj_set_height(bg_btn, lv_obj_get_height(img)+lv_obj_get_height(page)+20);
	}
	else
	{
		lv_obj_set_height(page, lv_obj_get_height(parent) - lv_obj_get_height(img) -20);
		lv_obj_set_height(bg_btn, lv_obj_get_height(img)+lv_obj_get_height(page)+20);
	}

	return bg_btn;
}
/**
 * description						页面只有文本和图片，两个元素。文本加图片一起拖动
 * lv_obj_t *parent					基于 parent 创建
 lv_img_dsc_t *img_pic				图片
 * const char *str					label 内容
 * lv_color_t color					label 颜色
 * lv_label_align_t label_align		label 对齐方式
 * lv_label_long_mode_t long_mode	label 模式
 * uint16_t f_size					字体大小
 * uint8_t line						行数：LV_LABEL_LONG_DOT 模式（显示...）才生效，非 LV_LABEL_LONG_DOT 模式写0
**/
lv_obj_t *zh_lv_create_label_pic_roll_all_dis(lv_obj_t *parent, lv_img_dsc_t *img_pic,const char *str,lv_color_t color, lv_label_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line)
{
	uint16_t pic_and_label_interval = 16;//图片和文字的间隔
	uint16_t head_interval = 20;
	uint16_t tail_interval = 35;
	//请在手机确认配对页面。图标和文本一起拖动
	lv_obj_t *bg_btn = zh_multobj_bg_create(parent, parent, LV_ALIGN_CENTER, 0, 0, LV_HOR_RES_MAX - 20*2, 0, 0, LV_COLOR_BLACK, LV_OPA_0);
	lv_obj_t *img = zh_img_create(bg_btn, NULL, LV_ALIGN_CENTER, (lv_obj_get_width(bg_btn)-img_pic->header.w)/2, 0,img_pic);
	 lv_obj_t *label_one = zh_label_create(bg_btn, bg_btn, LV_ALIGN_IN_BOTTOM_MID, 0, 0, LV_HOR_RES_MAX - 20*2, 0, str, color, label_align, long_mode, f_size, line);

	lv_obj_set_height(bg_btn, lv_obj_get_height(img)+lv_obj_get_height(label_one)+pic_and_label_interval);
	rt_kprintf("xt_test==%d,%d\n",lv_obj_get_height(bg_btn),(lv_obj_get_height(bg_btn)>LV_VER_RES_MAX - head_interval -tail_interval));
	if(lv_obj_get_height(bg_btn)>LV_VER_RES_MAX - head_interval -tail_interval)
	{
		lv_obj_set_height(parent, lv_obj_get_height(bg_btn));//370
	}
	else
	{
		lv_obj_set_height(parent, LV_VER_RES_MAX-head_interval-tail_interval);
		lv_obj_align_to(bg_btn, parent, LV_ALIGN_CENTER, 0, -(head_interval -tail_interval)/2);
	}
	return bg_btn;
}

/**
 * description						使用多个label创建一个子元素等宽的数字字符串,用于解决数字字符串刷新抖动问题
 * lv_obj_t *parent					基于 parent 创建
 * lv_obj_t *align_parent			基于 align_parent 对齐（为 NULL 则基于 parent 设置绝对坐标）
 * lv_align_t align					对齐方式
 * lv_coord_t x						x坐标（使用对齐:相对于 align_parent 的x坐标，不使用对齐:相对于 parent 的x坐标）
 * lv_coord_t y						y坐标（使用对齐:相对于 align_parent 的y坐标，不使用对齐:相对于 parent 的y坐标）
 * lv_coord_t w						宽：如果文本宽度根据实际显示的来，则写0
 * lv_coord_t h						高：如果文本高度根据实际显示的来，则写0
 * lv_color_t color					label 颜色
 * lv_obj_t **obj_array				子label数组
 * const char *str					数字字符串内容 eg:"59:59.99"、"99:59:59.99"、"23:59:59"...
 * uint8_t obj_num					子label数量
 * uint16_t f_size					字体大小
 * bool is_align_mid                子label对象整体在竖直方向上是否基于bg_cont居中对齐：false-顶部对齐、true-居中对齐
 * uint8_t align_bg_cont			子label对象整体在水平方向上基于bg_cont的对齐方式 0-居中对齐 、1-左对齐 、2-右对齐
 **/
void zh_lv_refresh_label_equal_width_num_str(lv_obj_t **obj_array, const char *str, uint8_t obj_num)
{
	char str_buff[32];
	for (int8_t idx = obj_num - 1; idx >= 0; idx--)
	{
		if (obj_array[idx])
		{
			char *origin = lv_label_get_text(obj_array[idx]);
			if (origin[0] != str[idx])
			{
				memset(str_buff, 0, sizeof(str_buff));
				sprintf(str_buff, "%c", str[idx]);
				lv_label_set_text(obj_array[idx], str_buff);
			}
		}
	}
}

lv_obj_t *zh_lv_create_label_equal_width_num_str(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, lv_color_t color,
												 lv_obj_t **obj_array, const char *str, uint8_t obj_num, uint16_t f_size, bool is_align_mid, uint8_t align_bg_cont)
{
	// parent
	lv_obj_t *bg_cont = zh_cont_create(parent, align_parent, align, x, y, w, h, NULL);
	// lv_obj_set_style_local_border_color(bg_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	// lv_obj_set_style_local_border_width(bg_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, 1);
	// char_num
	char char_num = '0';
	lv_coord_t char_width_max = 0;
	for (uint8_t i = 0; i < 10; i++)
	{
		char_width_max = lvsf_font_width(f_size, char_num) > char_width_max ? lvsf_font_width(f_size, char_num) : char_width_max;
		// rt_kprintf("char_width_max = %d,char_num ='%c'\n", char_width_max, char_num);
		char_num++;
	}
	// colon
	uint8_t colon_index[16];
	uint8_t colon_num = 0;
	lv_coord_t colon_width_total = 0;
	for (uint8_t idx = 0; idx < strlen(str); idx++)
	{
		if (str[idx] < '0' || str[idx] > '9')
		{
			colon_index[colon_num] = idx;
			colon_num++;
			colon_width_total += lvsf_font_width(f_size, str[idx]);
			// rt_kprintf("colon_num = %d, colon_index[%d] = %d,colon_width_total = %d\n", colon_num, colon_num - 1, idx, colon_width_total);
		}
	}
	// children
	char str_buff[32];
	lv_coord_t pos_x = 0;
	if (align_bg_cont == 0)
		pos_x = (w - char_width_max * (obj_num - colon_num) - colon_width_total) / 2;
	for (uint8_t idx = 0; idx < obj_num; idx++)
	{
		bool is_colon = false;
		for (uint8_t i = 0; i < colon_num; i++)
		{
			if (colon_index[i] == idx)
			{
				is_colon = true;
				break;
			}
		}

		memset(str_buff, 0, sizeof(str_buff));
		sprintf(str_buff, "%c", str[idx]);
		if (is_colon)
		{
			obj_array[idx] = zh_label_create(bg_cont, obj_array[idx - 1], LV_ALIGN_OUT_RIGHT_MID, 0, 0, lvsf_font_width(f_size, str[idx]), 0, str_buff, color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_BREAK, f_size, 0);
			lv_obj_align_to(obj_array[idx], obj_array[idx - 1], LV_ALIGN_OUT_RIGHT_MID, 0, 0);
		}
		else
		{
			lv_align_t child_head_align = LV_ALIGN_IN_TOP_LEFT;
			if (is_align_mid)
				child_head_align = LV_ALIGN_IN_LEFT_MID;

			if (!idx)
			{
				obj_array[idx] = zh_label_create(bg_cont, bg_cont, child_head_align, pos_x, 0, char_width_max, 0, str_buff, color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_BREAK, f_size, 0);
				lv_obj_align_to(obj_array[idx], bg_cont, child_head_align, pos_x, 0);
			}
			else
			{
				obj_array[idx] = zh_label_create(bg_cont, obj_array[idx - 1], LV_ALIGN_OUT_RIGHT_MID, 0, 0, char_width_max, 0, str_buff, color, LV_LABEL_ALIGN_CENTER, LV_LABEL_LONG_BREAK, f_size, 0);
				lv_obj_align_to(obj_array[idx], obj_array[idx - 1], LV_ALIGN_OUT_RIGHT_MID, 0, 0);
			}
		}
		// lv_obj_set_style_local_border_color(obj_array[idx], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
		// lv_obj_set_style_local_border_width(obj_array[idx], LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 1);
	}

	if (align_bg_cont == 2)
	{
		lv_align_t child_head_align = LV_ALIGN_IN_TOP_RIGHT;
		if (is_align_mid)
			child_head_align = LV_ALIGN_IN_RIGHT_MID;

		for (int8_t idx = obj_num - 1; idx >= 0; idx--)
		{
			if (idx == obj_num - 1)
				lv_obj_align_to(obj_array[idx], bg_cont, child_head_align, pos_x, 0);
			else
				lv_obj_align_to(obj_array[idx], obj_array[idx + 1], LV_ALIGN_OUT_LEFT_MID, 0, 0);
		}
	}

	return bg_cont;
}

/**
 * description                       更新当前页面，不包含标题
 * lv_obj_t *parent                  主背景
 * int (*cb_func)(lv_obj_t *list)    界面加载函数
 * void *gif_page					 页面有gif时需要传这个参，当gif在标题上时传null,不在标题时就传对用的指针
**/
void zh_page_update_common(lv_obj_t *parent, int (*cb_func)(lv_obj_t *list),void *gif_page)
{
	rt_kprintf("zh_page_update_common\n");

	lv_baselist_ext_t *ext = lv_obj_get_ext_attr(parent);
	if(baselist_resumed != ext->state)
	  {
        // RT_ASSERT(0);
        rt_kprintf("not baselist_resumed\n");
		return;
	  }
	if(gif_page)
	{
		zh_gif_delete((app_page_gif_t *)gif_page);

	}
	lv_baselist_set_pause(parent);
	lv_page_clean(parent);
    if (cb_func)
    {
	    cb_func(parent);
    }
	lv_baselist_set_resume(parent);
	//extern void Zh_page_reflash_fun();//会刷新熄屏时长
	//Zh_page_reflash_fun();
}
/**
 * description                       更新当前弹窗，不包含标题
 * lv_obj_t *parent                  主背景
 * int (*cb_func)(lv_obj_t *list)    界面加载函数
**/
void zh_page_update_common_pop(lv_obj_t *parent, int (*cb_func)(lv_obj_t *list))
{
	lv_baselist_set_pause(parent);
	lv_page_clean(parent);
    if (cb_func)
    {
	    cb_func(parent);
    }
	lv_baselist_set_resume(parent);
}

static lv_coord_t zh_baselist_get_scrl_index(lv_obj_t *element, bool is_hor)
{
	lv_coord_t index = 0;
	lv_coord_t h = lv_obj_get_height(element);
	lv_coord_t y = lv_obj_get_y(element);

	if (is_hor)
	{
		h = lv_obj_get_width(element);
		y = lv_obj_get_x(element);
	}

	lv_coord_t h_pivot = h >> 1;

	if ((y + h_pivot) > 0)
		index = (y + h_pivot) / h;
	else
		index = -(h_pivot - y) / h;

	return index;
}

/**
 * description                       判断当前是baselist/multlist的第几页
 * void *ext            			 multlist的额外属性，通过lv_obj_get_ext_attr获取
 * uint8_t index					 当前是否是第index页
 * bool is_hor					 	 是否是水平排布的list,true-水平方向排布,false-竖直方向排布
 **/
bool zh_baselist_judge_is_this_page(void *ext, uint8_t index, bool is_hor) // page_index start from 0
{
	if (!ext)
		return false;

	rt_list_t *pos;
	uint8_t count = 0;
	lv_multlist_ext_t *ext_attr = (lv_multlist_ext_t *)ext;

	rt_list_for_each(pos, &ext_attr->draw_list)
	{
		lv_multlist_draw_node_t *node_des = rt_list_entry(pos, lv_multlist_draw_node_t, list);

		if (zh_baselist_get_scrl_index(node_des->element, is_hor) == 0 && count == index)
			return true;

		count++;
	}
	return false;
}

static rt_list_t zh_refresh_list;
static int zh_obj_refresh_list_init(void)
{
    rt_list_init(&zh_refresh_list);
    return 0;
}
INIT_PRE_APP_EXPORT(zh_obj_refresh_list_init);

#define subscribe_same_node(refresh_node) (refresh_node->obj == obj && refresh_node->idx == idx)//绑定不同
void zh_obj_data_subscribe(lv_obj_t *obj, uint16_t idx, zh_obj_datasubs_cb_t cb, void *user_data)
{
	if(!obj) return;

	rt_list_t *pos;
	zh_refresh_p refresh_node;
	rt_list_for_each(pos, &zh_refresh_list)
	{
		refresh_node = rt_list_entry(pos, zh_refresh_t, list);
		if(subscribe_same_node(refresh_node))//当前已存在相同项，更新并退出
		{
			refresh_node->datasubs_cb = cb;
			refresh_node->user_data = user_data;
			return;
		}
	}

	refresh_node = rt_malloc(sizeof(zh_refresh_t));
	RT_ASSERT(refresh_node);
	rt_memset(refresh_node, 0, sizeof(zh_refresh_t));
	refresh_node->obj = obj;
	refresh_node->idx = idx;
	refresh_node->datasubs_cb = cb;
	refresh_node->user_data = user_data;
	rt_list_insert_before(&zh_refresh_list, &refresh_node->list);
}

void zh_obj_data_unsubscribe(lv_obj_t *obj, uint16_t idx)
{
	rt_list_t *pos;
	rt_list_for_each(pos, &zh_refresh_list)
	{
		zh_refresh_p refresh_node = rt_list_entry(pos, zh_refresh_t, list);
		if(subscribe_same_node(refresh_node))
		{
			rt_list_remove(&refresh_node->list);
			rt_free(refresh_node);
			break;
		}
	}
}

int zh_obj_datasubs_notify(uint16_t idx/*, const void *data, uint16_t len*/)
{
	rt_list_t *pos;
	int exist_cur_idx = 0;
	rt_list_for_each(pos, &zh_refresh_list)
	{
		zh_refresh_p refresh_node = rt_list_entry(pos, zh_refresh_t, list);
		if(refresh_node->idx == idx)
		{
			exist_cur_idx = 1;
			if(refresh_node->datasubs_cb)
				refresh_node->datasubs_cb(refresh_node->obj, refresh_node->user_data);
		}
	}

	return exist_cur_idx;
}
#endif

