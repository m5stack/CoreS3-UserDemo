#include "HomeMenu.h"

using namespace Page;

HomeMenu::HomeMenu() : timer(nullptr) {
}

HomeMenu::~HomeMenu() {
}

void HomeMenu::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewLoad() {
    LV_LOG_USER(__func__);

    View.Create(_root);

    for (size_t i = 0; i < 9; i++) {
        AttachEvent(View.ui.imgbtn_list[i], LV_EVENT_CLICKED);
    }
}

void HomeMenu::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void HomeMenu::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void HomeMenu::onViewUnload() {
    LV_LOG_USER(__func__);
}

void HomeMenu::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void HomeMenu::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void HomeMenu::Update() {
}

void HomeMenu::onTimerUpdate(lv_timer_t* timer) {
    HomeMenu* instance = (HomeMenu*)timer->user_data;

    instance->Update();
}

void HomeMenu::onEvent(lv_event_t* event) {
    HomeMenu* instance = (HomeMenu*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        if (obj == instance->View.ui.imgbtn_list[2]) {
            USBSerial.println("HomeMenu -> AppMic");
            instance->_Manager->Replace("Pages/AppMic");
            return;
        }
        USBSerial.print("HomeMenu -> ");
        M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"),
                           ~0u, 1, 1);
        if (obj == instance->View.ui.imgbtn_list[0]) {
            USBSerial.println("AppWiFi");
            instance->_Manager->Replace("Pages/AppWiFi");
        } 
    #if defined(M5CORES3)
        else if (obj == instance->View.ui.imgbtn_list[1]) {
            USBSerial.println("AppCamera");
            instance->_Manager->Replace("Pages/AppCamera");
        }else if (obj == instance->View.ui.imgbtn_list[4]) {
            USBSerial.println("AppIMU");
            instance->_Manager->Replace("Pages/AppIMU");
        }  
    #elif defined(M5CORES3SE)

    #endif
        
        else if (obj == instance->View.ui.imgbtn_list[3]) {
            USBSerial.println("AppPower");
            instance->_Manager->Replace("Pages/AppPower");
        } else if (obj == instance->View.ui.imgbtn_list[5]) {
            USBSerial.println("AppSD");
            instance->_Manager->Replace("Pages/AppSD");
        } else if (obj == instance->View.ui.imgbtn_list[6]) {
            USBSerial.println("AppTouch");
            instance->_Manager->Replace("Pages/AppTouch");
        } else if (obj == instance->View.ui.imgbtn_list[7]) {
            USBSerial.println("AppI2C");
            instance->_Manager->Replace("Pages/AppI2C");
        } else if (obj == instance->View.ui.imgbtn_list[8]) {
            USBSerial.println("AppRTC");
            instance->_Manager->Replace("Pages/AppRTC");
        }
    }
}
