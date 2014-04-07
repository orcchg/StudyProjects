/*! @file vconfpopup.h
 *  @brief New file description.
 *  @author Alov Maxim <m.alov@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code conforms to http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide.
 *
 *  @section Copyright
 *  Copyright 2012 Samsung Electronics
 */

#ifndef SRC_UI_VCONFPOPUP_H_
#define SRC_UI_VCONFPOPUP_H_

#include <Elementary.h>

#define __UNUSED__

namespace Utility {

// ----------------------------------------------------------------------------
typedef void SIG_CB_FUNC(void*, Evas_Object*, void*);

void _popup_block_clicked(
    void* data,
    Evas_Object* obj,
    void* event_info);

// ----------------------------------------------
void _popup_button_clicked(
    void* data,
    Evas_Object* obj,
    void* event_info);

// ----------------------------------------------
Evas_Object* invoke_popup(
    Evas_Object* window,
    SIG_CB_FUNC click_button_cb,
    SIG_CB_FUNC click_out_cb,
    const char* text,
    const char* button_label);

// ----------------------------------------------
Evas_Object* invoke_popup_alt(
    Evas_Object* window,
    SIG_CB_FUNC click_button_one_cb,
    SIG_CB_FUNC click_button_two_cb,
    SIG_CB_FUNC click_out_cb,
    const char* text,
    const char* button_one_label,
    const char* button_two_label,
    void* data_to_one);

}  // end namespace Utility

#endif  // SRC_UI_VCONFPOPUP_H_
