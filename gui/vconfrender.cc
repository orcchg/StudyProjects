/*! @file vconfrender.cc
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

#include <gst/gst.h>
#include "vconfrender.h"

namespace ConferenceUI {

/* Gstreamer binding throught EvasVideoSink */
//-----------------------------------------------------------------------------
GstElement* playbin;
GstElement* playbin2;
GstElement* playbin3;
GstElement* sink;
GstElement* sink2;
GstElement* sink3;
Evas_Object* video;
Evas_Object* video2;
Evas_Object* video3;

/* name: run_video;
 *
 * type: EDIT;
 *
 * params:
 *
 * return: void;
 *
 * description:
 *
 */
void run_video(
    Evas_Object* layout,
    const std::string& partname,
    const std::string& argv
    ) {
  video = evas_object_image_filled_add(evas_object_evas_get(layout));
  elm_object_part_content_set(layout, partname.c_str(), video);
  evas_object_show(video);

  playbin = gst_element_factory_make("playbin2", "playbin");
  sink = gst_element_factory_make("evasvideosink", "sink");

  /* Tell our playbin to render in our sink */
  g_object_set(reinterpret_cast<GObject*>(playbin), "video-sink", sink, NULL);

  /* Set playbin URI */
  g_object_set(reinterpret_cast<GObject*>(playbin), "uri", argv.c_str(), NULL);

  /* Send Evas Image to EvasVideoSink */
  g_object_set(reinterpret_cast<GObject*>(sink), "evas-object", video, NULL);

  GstStateChangeReturn res =
      gst_element_set_state(playbin, GST_STATE_PAUSED);
  if (res == GST_STATE_CHANGE_FAILURE) {
    printf("Unable to set state, make sure your URI or plugin are correct\n");
    return;
  }
  res = gst_element_get_state(playbin, NULL, NULL, GST_CLOCK_TIME_NONE);
  if (res != GST_STATE_CHANGE_SUCCESS) {
    printf("Unable to get state\n");
    return;
  }

  gst_element_set_state(playbin, GST_STATE_PLAYING);
}


/* Video rendering methods' part */
// ----------------------------------------------------------------------------
struct window_func_external {
  Evas_Object* window;
  void* data;

  window_func_external(Evas_Object* w, void* d)
    : window(w)
    , data(d)
  {}
};

static void _win_del(
    void* /*data*/, __UNUSED__
    Evas_Object* obj,
    void* /*event_info*/ __UNUSED__
    ) {
  printf("VIDEO Close\n");
  evas_object_del(obj);
}

void wrapped_invoke_Leave(
    void* data,
    Evas_Object* /*obj*/, __UNUSED__
    void* /*event_info*/ __UNUSED__
    ) {
  window_func_external* wfe =
      reinterpret_cast<window_func_external*>(data);

  ConferenceUI::VConfGUI* gui =
      reinterpret_cast<ConferenceUI::VConfGUI*>(wfe->data);
  /*gui->get_manager()->get_instance()->Leave();*/printf("Leave()\n");

  evas_object_del(wfe->window);
  evas_object_show(gui->at(0).get_window());

  delete wfe;
}

static void on_click_VIDEO(
    void* data,
    Evas_Object* /*obj*/, __UNUSED__
    const char* /*emission*/, __UNUSED__
    const char*/*source*/ __UNUSED__
    ) {
  printf("VIDEO CLICKED!\n");

  window_func_external* wfe =
      reinterpret_cast<window_func_external*>(data);

  Utility::invoke_popup_alt(
      wfe->window,
      wrapped_invoke_Leave,
      Utility::_popup_button_clicked,
      Utility::_popup_block_clicked,
      "Menu",
      "Disconnect",
      "Cancel",
      data);
}


// ----------------------------------------------
Evas_Object* add_smart_area(
    const VConfWindow& window,
    const char* edj_filename,
    const char* smart_group_name,
    const char* swallow_area_name,
    const char* emission,
    const char* source,
    void sig_cb_func(void*, Evas_Object*, const char*, const char*),
    void* data
    ) {
  Evas_Object* layout = elm_layout_add(window.get_window());
  elm_layout_file_set(
      layout,
      edj_filename,
      smart_group_name);
  elm_object_part_content_set(
      window.get_layout(),
      swallow_area_name,
      layout);

  edje_object_signal_callback_add(
      elm_layout_edje_get(layout),
      emission,
      source,
      sig_cb_func,
      data);

  return layout;
}

// ----------------------------------------------
void show_vconference(void* data) {
  // SinkStatus sink_status[4] = {sBusy, sFree, sFree, sFree};
  printf("SHOW START\n");

  VConfWindow video_render_window(
      "Video conference",
      "Video conference",
      VCONF_WIDTH,
      VCONF_HEIGHT,
      EINA_TRUE,
      edj_filename_external,
      "group_video_table_interface");
  video_render_window.add_delete_cb(_win_del, NULL);
  video_render_window.add_win_props(EINA_TRUE, EINA_TRUE);
  printf("WINDOW MADE\n");

  // sink_manager sink(sink_status, gui.at(window_index).get_layout());
  window_func_external* wfe =
      new window_func_external(video_render_window.get_window(), data);
  printf("WFE CREATED\n");

  /* Running owner's video stream */
  Evas_Object* video_area_one = add_smart_area(
      video_render_window,
      edj_filename_external.c_str(),
      "group_participant_one",
      "upper_left_video_swallow",
      "SIG_VIDEO_CLICKED",
      "events",
      on_click_VIDEO,
      wfe);
  Evas_Object* video_area_two = add_smart_area(
      video_render_window,
      edj_filename_external.c_str(),
      "group_participant_two",
      "upper_right_video_swallow",
      "SIG_VIDEO_CLICKED",
      "events",
      on_click_VIDEO,
      wfe);
  Evas_Object* video_area_three = add_smart_area(
      video_render_window,
      edj_filename_external.c_str(),
      "group_participant_three",
      "lower_left_video_swallow",
      "SIG_VIDEO_CLICKED",
      "events",
      on_click_VIDEO,
      wfe);
  Evas_Object* video_area_four = add_smart_area(
      video_render_window,
      edj_filename_external.c_str(),
      "group_participant_four",
      "lower_right_video_swallow",
      "SIG_VIDEO_CLICKED",
      "events",
      on_click_VIDEO,
      wfe);
  printf("SMART AREAD ADDED\n");

  run_video(
      video_area_one,
      "participant_one",
      "file:///home/maximalov/Documents/sources/sample_video/ROND.MPG");
  printf("RUN 1\n");
  run_video(
      video_area_two,
      "participant_two",
      "file:///home/maximalov/Documents/sources/sample_video/MELT.MPG");
  printf("RUN 2\n");
  run_video(
      video_area_three,
      "participant_three",
      "file:///home/maximalov/Documents/sources/sample_video/DELTA.MPG");
  printf("RUN 3\n");
  run_video(
      video_area_four,
      "participant_four",
      "file:///home/maximalov/Documents/sources/sample_video/FORM.MPG");
  printf("RUN 4\n");

  /*run_video(
      video_render_window.get_layout(),
      "upper_left_video_swallow",
      "file:///home/maximalov/Documents/sources/sample_video/ROND.MPG");
  printf("RUN 1\n");
  run_video(
      video_render_window.get_layout(),
      "upper_right_video_swallow",
      "file:///home/maximalov/Documents/sources/sample_video/MELT.MPG");
  printf("RUN 2\n");
  run_video(
      video_render_window.get_layout(),
      "lower_left_video_swallow",
      "file:///home/maximalov/Documents/sources/sample_video/DELTA.MPG");
  printf("RUN 3\n");
  run_video(
      video_render_window.get_layout(),
      "lower_right_video_swallow",
      "file:///home/maximalov/Documents/sources/sample_video/FORM.MPG");
  printf("RUN 4\n");*/
}

}  // end namespace ConferenceUI
