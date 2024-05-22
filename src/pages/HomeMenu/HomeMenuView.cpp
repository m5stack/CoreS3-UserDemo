#include <stdarg.h>
#include <stdio.h>
#include "HomeMenuView.h"

using namespace Page;

/*
    width: 60px
    height: 73px
*/




LV_IMG_DECLARE(menu_wifi);

#if defined(M5CORES3)
    LV_IMG_DECLARE(menu_cam);
#elif defined(M5CORES3SE)
    LV_IMG_DECLARE(menu_cam_se);
#endif

LV_IMG_DECLARE(menu_mic);
LV_IMG_DECLARE(menu_power);

#if defined(M5CORES3)
    LV_IMG_DECLARE(menu_imu);
#elif defined(M5CORES3SE)
    LV_IMG_DECLARE(menu_imu_se);
#endif
LV_IMG_DECLARE(menu_sd);
LV_IMG_DECLARE(menu_touch);
LV_IMG_DECLARE(menu_i2c);
LV_IMG_DECLARE(menu_sys);

static const lv_img_dsc_t* menu_img_pressed_list[] = {
    &menu_wifi,
#if defined(M5CORES3)
    &menu_cam,
#elif defined(M5CORES3SE)
    &menu_cam_se,
#endif
    &menu_mic,
    &menu_power,
#if defined(M5CORES3)
    &menu_imu,
#elif defined(M5CORES3SE)
    &menu_imu_se,
#endif
    &menu_sd,
    &menu_touch,
    &menu_i2c,
    &menu_sys,
};

void HomeMenuView::Create(lv_obj_t* root) {
#if defined(M5CORES3)
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("menu_bg"));
#elif defined(M5CORES3SE)
    ui.img_bg_se = lv_img_create(root);
    lv_img_set_src(ui.img_bg_se, ResourcePool::GetImage("menu_bg_se"));
#endif


    for (size_t i = 0; i < 8; i++)
    {
        ui.imgbtn_list[i] = lv_imgbtn_create(root);
        // lv_obj_remove_style_all(ui.imgbtn_list[i]);
        lv_obj_set_size(ui.imgbtn_list[i], 60, 73);
        lv_obj_set_pos(ui.imgbtn_list[i], 10 + 80 * (i % 4), 75 + 80 * (i / 4));


        lv_imgbtn_set_src(ui.imgbtn_list[i], LV_IMGBTN_STATE_PRESSED, NULL, menu_img_pressed_list[i], NULL);
        lv_imgbtn_set_src(ui.imgbtn_list[i], LV_IMGBTN_STATE_RELEASED, NULL, menu_img_pressed_list[i], NULL);

        // lv_obj_set_style_border_color(ui.imgbtn_list[i], lv_color_hex(0xff00ff), 0);
        // lv_obj_set_style_border_side(ui.imgbtn_list[i], LV_BORDER_SIDE_FULL, 0);
        // lv_obj_set_style_border_width(ui.imgbtn_list[i], 1, 0);
        // lv_obj_set_style_radius(ui.imgbtn_list[i], 0, 0);
        // lv_obj_set_style_border_post(ui.imgbtn_list[i], true, 0);
    }

    ui.imgbtn_list[8] = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_list[8], 60, 73);
    lv_obj_set_pos(ui.imgbtn_list[8], 250, 10);

    lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_PRESSED, NULL, menu_img_pressed_list[8], NULL);
    lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_RELEASED, NULL, menu_img_pressed_list[8], NULL);

    // lv_obj_set_style_border_color(ui.imgbtn_list[8], lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.imgbtn_list[8], LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.imgbtn_list[8], 1, 0);
    // lv_obj_set_style_radius(ui.imgbtn_list[8], 0, 0);
    // lv_obj_set_style_border_post(ui.imgbtn_list[8], true, 0);
}

void HomeMenuView::Delete() {
}
