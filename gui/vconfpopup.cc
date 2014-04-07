/*! @file vconfpopup.cc
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

#include "vconfpopup.h"

// ----------------------------------------------------------------------------
Evas_Object* Utility::invoke_popup(
    Evas_Object* window,
    SIG_CB_FUNC click_button_cb,
    SIG_CB_FUNC click_out_cb,
    const char* text,
    const char* button_label
    ) {
  Evas_Object* popup = elm_popup_add(window);
  elm_object_part_text_set(popup, "title,text", text);
  evas_object_smart_callback_add(popup, "block,clicked", click_out_cb, NULL);

  Evas_Object* button = elm_button_add(popup);
  elm_object_text_set(button, button_label);

  elm_object_part_content_set(popup, "button1", button);
  evas_object_smart_callback_add(button, "clicked", click_button_cb, popup);

  evas_object_show(popup);

  return popup;
}

// ----------------------------------------------
Evas_Object* Utility::invoke_popup_alt(
    Evas_Object* window,
    SIG_CB_FUNC click_button_one_cb,
    SIG_CB_FUNC click_button_two_cb,
    SIG_CB_FUNC click_out_cb,
    const char* text,
    const char* button_one_label,
    const char* button_two_label,
    void* data_to_one
    ) {
  Evas_Object* popup = elm_popup_add(window);
  elm_object_part_text_set(popup, "title,text", text);
  evas_object_smart_callback_add(popup, "block,clicked", click_out_cb, NULL);

  Evas_Object* button_one = elm_button_add(popup);
  elm_object_text_set(button_one, button_one_label);

  elm_object_part_content_set(popup, "button1", button_one);
  evas_object_smart_callback_add(
      button_one,
      "clicked",
      click_button_one_cb,
      data_to_one);

  Evas_Object* button_two = elm_button_add(popup);
  elm_object_text_set(button_two, button_two_label);

  elm_object_part_content_set(popup, "button2", button_two);
  evas_object_smart_callback_add(
      button_two,
      "clicked",
      click_button_two_cb,
      popup);

  evas_object_show(popup);

  return popup;
}

// ----------------------------------------------
void Utility::_popup_block_clicked(
    void* /*data*/,  __UNUSED__
    Evas_Object* obj,
    void* /*event_info*/  __UNUSED__
    ) {
  evas_object_hide(obj);
}

// ----------------------------------------------
void Utility::_popup_button_clicked(
    void* data,
    Evas_Object* /*obj*/,  __UNUSED__
    void* /*event_info*/  __UNUSED__
    ) {
  evas_object_hide(reinterpret_cast<Evas_Object*>(data));
}
