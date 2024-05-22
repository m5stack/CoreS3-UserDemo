#ifndef __STARTUP_VIEW_H
#define __STARTUP_VIEW_H

#include "../Page.h"

namespace Page {

class StartUpView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
    #if defined(M5CORES3)
        lv_obj_t* img_s3_text;
        lv_obj_t* img_core_text;
        lv_obj_t* img_cores3_diagram;
    #elif defined(M5CORES3SE)
        lv_obj_t* img_s3_text_se;
        lv_obj_t* img_core_text_se;
        lv_obj_t* img_cores3_diagram_se;
    #endif
        // lv_obj_t* btn_next;

        lv_anim_timeline_t* anim_timeline;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
