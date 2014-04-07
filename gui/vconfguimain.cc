/*! @file vconfguimain.cc
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
#include "vconf.h"  // GUI classes part
#include "vconfrender.h"  // render video part
/*#include "src/ui/vconfsignals.h"  // external signals*/


// ----------------------------------------------------------------------------
static void _win_del(
    void* /*data*/, __UNUSED__
    Evas_Object* /*obj*/, __UNUSED__
    void* /*event_info*/ __UNUSED__
    ) {
  elm_exit();
}

// ----------------------------------------------
static void _createconf_win_del(
    void* data,
    Evas_Object* obj,
    void* /*event_info*/ __UNUSED__
    ) {
  printf("DELETE: CreateConf\n");

  edje_object_signal_callback_del(
      obj,
      "clicked",
      "left_controller",
      ConferenceUI::VConfManager::on_click_OK_CreateConf);
  edje_object_signal_callback_del(
      obj,
      "clicked",
      "right_controller",
      ConferenceUI::VConfManager::on_click_CANCEL_CreateConf);
  evas_object_del(obj);

  ConferenceUI::conference_info* info =
      reinterpret_cast<ConferenceUI::conference_info*>(data);
  delete info;
  elm_exit();
}

// ----------------------------------------------
static void _connect_win_del(
    void* data,
    Evas_Object* obj,
    void* /*event_info*/ __UNUSED__
    ) {
  printf("DELETE: Connect\n");

  edje_object_signal_callback_del(
      obj,
      "clicked",
      "left_controller",
      ConferenceUI::VConfManager::on_click_OK_Connect);
  edje_object_signal_callback_del(
      obj,
      "clicked",
      "right_controller",
      ConferenceUI::VConfManager::on_click_CANCEL_Connect);
  evas_object_del(obj);

  ConferenceUI::conference_info* info =
      reinterpret_cast<ConferenceUI::conference_info*>(data);
  delete info;
  elm_exit();
}


// ----------------------------------------------------------------------------
void process_dialog_window(
    const char* title,
    const char* gr_label,
    void* data,
    void handler_OK(void*, Evas_Object*, const char*, const char*),
    void handler_CANCEL(void*, Evas_Object*, const char*, const char*)
    ) {
  ConferenceUI::VConfGUI* gui =
      reinterpret_cast<ConferenceUI::VConfGUI*>(data);

  size_t window_index = gui->add_window(
      title,
      title,
      WIDTH_CREATECONF,
      HEIGHT_CREATECONF,
      EINA_TRUE,
      ConferenceUI::edj_filename_external,
      "group_create_connect_interface");
  printf("PROCESS DIALOG: (gui: %p, size: %d), (main: %p, evas: %p),"
      "(win: %p, evas: %p)\n",
         gui, gui->size(),
         &(gui->at(0)), gui->at(0).get_window(),
         &gui->at(window_index), gui->at(window_index).get_window());

  gui->at(window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      gr_label,
      "text_label_swallow");
  size_t entry_index = gui->at(window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_entry",
      "entry_swallow");
  size_t left_button_index = gui->at(window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_left_controller",
      "left_controller_swallow");
  size_t right_button_index = gui->at(window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_right_controller",
      "right_controller_swallow");
  printf("PROCESS DIALOG: lays %d\n", gui->at(window_index).size());

  /* Processing widgets */
  Evas_Object* entry_widget =
      gui->at(window_index).get_widget(entry_index, "entry");
  elm_entry_single_line_set(entry_widget, EINA_TRUE);
  elm_entry_scrollable_set(entry_widget, EINA_TRUE);

  gui->get_manager()->set_after(ConferenceUI::show_vconference);
  ConferenceUI::conference_info* conf =
      new ConferenceUI::conference_info(
          "",
          entry_widget,
          gui->at(window_index).get_window(),
          gui);

  /* Signals catch */
  gui->at(window_index).add_delete_cb(_createconf_win_del, conf);
  edje_object_signal_callback_add(
      gui->at(window_index).get_edje(left_button_index),
      "clicked",
      "left_controller",
      handler_OK,
      conf);
  edje_object_signal_callback_add(
      gui->at(window_index).get_edje(right_button_index),
      "clicked",
      "right_controller",
      handler_CANCEL,
      conf);

  evas_object_hide(gui->at(0).get_window());  // guess: main window has 0 index
  printf("PROCESS DIALOG: (hided: %p, evas %p)\n",
         &(gui->at(0)), gui->at(0).get_window());
}


// ----------------------------------------------------------------------------
static void create_function(
    void* data,
    Evas_Object* /*obj*/, __UNUSED__
    void* /*event_info*/ __UNUSED__
    ) {
  printf("CREATE\n");
  process_dialog_window(
      "Create new conference",
      "group_create_text_label",
      data,
      ConferenceUI::VConfManager::on_click_OK_CreateConf,
      ConferenceUI::VConfManager::on_click_CANCEL_CreateConf);
}

// ----------------------------------------------
static void connect_function(
    void* data,
    Evas_Object* /*obj*/, __UNUSED__
    void* /*event_info*/ __UNUSED__
    ) {
  printf("CONNECT\n");
  process_dialog_window(
      "Connect conference",
      "group_connect_text_label",
      data,
      ConferenceUI::VConfManager::on_click_OK_Connect,
      ConferenceUI::VConfManager::on_click_CANCEL_Connect);
}


// ----------------------------------------------------------------------------
static void on_click_CREATE(
    void* data,
    Evas_Object* obj,
    const char* /*emission*/, __UNUSED__
    const char* /*source*/ __UNUSED__
    ) {
  create_function(data, obj, NULL);
}

// ----------------------------------------------
static void on_click_CONNECT(
    void* data,
    Evas_Object* obj,
    const char* /*emission*/, __UNUSED__
    const char* /*source*/ __UNUSED__
    ) {
  connect_function(data, obj, NULL);
}

// ----------------------------------------------
static void on_click_CLOSE(
    void* /*data*/, __UNUSED__
    Evas_Object* /*obj*/, __UNUSED__
    const char* /*emission*/, __UNUSED__
    const char* /*source*/ __UNUSED__
    ) {
  printf("CLOSE\n");
  elm_exit();
}


/* MAIN PROGRAM */
//-----------------------------------------------------------------------------
/* name: main;
 *
 * type: PRIVATE;
 *
 * params: int argc - number of prompt arguments, argc >= 1,
 *         char argv[] - value of arguments, argv[0] = program name,
 *             These arguments currently are not used;
 *
 * return: int - system signal, 0 if correct;
 *
 * description: Initializes ecore, evas and edje. Adds new x11 window,
 *              canvas on it and edje (graph interface) on
 *              the canvas. Leverages the sizes on main window and edje.
 *              Gets several elm-widjet objects (type: Evas_Objects*) and
 *              establishes their functionality.
 *              Starts the ecore main loop to playback the GUI;
 *
 */
int main(int argc, char** argv) {
  // Conference::DeathHandler handler;
  printf("MAIN\n");
  elm_init(argc, argv);

  // GstElementEvasImageSink sink;
  /* Register external signals */
  /*UIExternalSignalHandlers::register_external_signal(
      Conference::kEventQueryVideoSink,
      UIExternalSignalHandlers::get_sink,
      "query_for_sink");
  UIExternalSignalHandlers::register_external_signal(
      Conference::kEventNewParticipant,
      UIExternalSignalHandlers::add_participant,
      "conn_participant");
  UIExternalSignalHandlers::register_external_signal(
      Conference::kEventParticipantLeft,
      UIExternalSignalHandlers::remove_participant,
      "dc_participant");
  UIExternalSignalHandlers::register_external_signal(
      Conference::kEventConnected,
      UIExternalSignalHandlers::handle_connected,
      "conn_me");
  UIExternalSignalHandlers::register_external_signal(
      Conference::kEventDisconnected,
      UIExternalSignalHandlers::handle_disconnected,
      "dc_me");*/
  printf("SIGNALS REGISTERED\n");

  ConferenceUI::VConfGUI gui;
  printf("GUI: %p\n", &gui);
  size_t main_window_index = gui.add_window(
      "VConf",
      "VConf",
      WIDTH,
      HEIGHT,
      EINA_TRUE,
      ConferenceUI::edj_filename_external,
      "group_main_interface");
  printf("WINDOW ADDED, %d\n", gui.size());
  gui.at(main_window_index).add_delete_cb(_win_del, NULL);
  printf("ADD_DELETE_CB\n");

  size_t top_controller_index = gui.at(main_window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_top_controller",
      "top_controller_swallow");
  edje_object_signal_callback_add(
      gui.at(main_window_index).get_edje(top_controller_index),
      "clicked",
      "top_controller",
      on_click_CREATE,
      &gui);

  size_t center_controller_index = gui.at(main_window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_center_controller",
      "center_controller_swallow");
  edje_object_signal_callback_add(
      gui.at(main_window_index).get_edje(center_controller_index),
      "clicked",
      "center_controller",
      on_click_CONNECT,
      &gui);

  size_t bottom_controller_index = gui.at(main_window_index).add_sublayout(
      ConferenceUI::edj_filename_external,
      "group_bottom_controller",
      "bottom_controller_swallow");
  edje_object_signal_callback_add(
      gui.at(main_window_index).get_edje(bottom_controller_index),
      "clicked",
      "bottom_controller",
      on_click_CLOSE,
      &gui);
  printf("SUBLAYOUTS ADDED, %d\n", gui.at(main_window_index).size());

  gst_init(&argc, &argv);
  printf("GSTREAMER INIT\n");

  elm_run();
  elm_shutdown();
  return 0;
}
