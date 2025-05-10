#ifndef _ZH_PAGE_MODEL_COMMON_H
#define _ZH_PAGE_MODEL_COMMON_H

#include "../LvglPlatform/lvgl/lvgl.h"

lv_obj_t *zh_cont_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, lv_event_cb_t event_cb);

lv_obj_t *zh_img_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *src_img);

lv_obj_t *zh_label_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                          const char *str, lv_color_t color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line);
lv_obj_t *zh_button_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                           int32_t radius, lv_color_t color, lv_opa_t opa, int32_t transform_w, int32_t transform_h, lv_event_cb_t event_cb);

lv_obj_t *zh_button_with_icon_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                                     int32_t radius, lv_color_t color, lv_opa_t opa, int32_t transform_w, int32_t transform_h, const void *fg_img, lv_event_cb_t event_cb);
lv_obj_t *zh_button_with_txt_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                                    int32_t radius, lv_color_t btn_color, lv_opa_t opa, int32_t transform_w, int32_t transform_h,
                                    uint16_t txt_w, uint16_t txt_h, const char *txt, lv_color_t txt_color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line, lv_event_cb_t event_cb);

lv_obj_t *zh_img_button_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *src_img, lv_event_cb_t event_cb);

lv_obj_t *zh_img_button_with_icon_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *bg_img, const void *fg_img, lv_event_cb_t event_cb);

lv_obj_t *zh_img_button_with_txt_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, const void *bg_img,
                                        uint16_t txt_w, uint16_t txt_h, const char *txt, lv_color_t txt_color, lv_text_align_t label_align, lv_label_long_mode_t long_mode, uint16_t f_size, uint8_t line, lv_event_cb_t event_cb);
lv_obj_t *zh_arc_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y,
                         lv_coord_t arc_size, lv_coord_t arc_width, int32_t start_angles, int32_t bg_angles, lv_color_t bg_color, lv_color_t indic_color);

lv_obj_t *zh_bar_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                        int32_t bg_radius, int32_t ind_radius, lv_color_t bg_color, lv_color_t ind_color, int32_t value, int32_t range_max);

lv_obj_t *zh_chart_create(lv_obj_t *parent, lv_obj_t *align_parent, lv_align_t align, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                          lv_chart_type_t type, lv_coord_t point_count, lv_chart_axis_t axis, lv_coord_t y_range_low, lv_coord_t y_range_hight);
#endif //_ZH_PAGE_MODEL_COMMON_H