/*! @file vconf.cc
 *  @brief API part of VConference GUI based on EFL (edje, elementary).
 *  @author Maxim Alov  <m.alov@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2012 Samsung Electronics
 *
 *  @section Description:
 *  Functions have 'type': CUSTOM - the function has default implementation, but it can be changed by user;
 *                         PRIVATE - the function's implementation should not be modified;
 *                         EDIT - the function must be implemented by user;
 */

#include "vconf.h"


/* VConfGUI methods' implementation */
// ----------------------------------------------------------------------------
ConferenceUI::VConfGUI::VConfGUI()
  : /*EinaLogger("VConfWindow", VCONFGUI_LOG_COLOR)
  ,*/ manager_(new VConfManager()) {
  printf("CONSTR-GUI\n");
  if (!manager_) {
    //CRT("Unable to create conference! Main GUI error.");
    throw VConfGUICommonException("Unable to create conference!");
  } else {
    //DBG("VConfGUI instance was created.");
  }
}

// ----------------------------------------------
ConferenceUI::VConfGUI::~VConfGUI() {
  //DBG("VConfGUI instance was deleted.");
  printf("DESTR-GUI, %p\n", this);
  delete manager_;
}

// ----------------------------------------------
size_t ConferenceUI::VConfGUI::add_window(
    const std::string& win_name,
    const std::string& win_title,
    int width,
    int height,
    Eina_Bool is_rotate,
    const std::string& edj_filename,
    const std::string& group_name
    ) {
  printf("ADD WINDOW: %d\n", parts_.capacity());
  size_t index = parts_.size();
  parts_.push_back(VConfWindow(
      win_name,
      win_title,
      width,
      height,
      is_rotate,
      edj_filename,
      group_name));
  //DBG("Added new window into GUI, at index %d.", index);
  printf("ADD WINDOW FINAL: %d, last: %p, evas: %p, cap: %d\n",
         parts_.size(), &parts_.back(),
         parts_.back().get_window(), parts_.capacity());
  return index;
}

// ----------------------------------------------
void ConferenceUI::VConfGUI::pop_window() {
  if (parts_.size() > 0) {
    //DBG("Pop top window from gui.");
    parts_.pop_back();
  } else {
    //DBG("Unable to pop top window from gui. Ignored.");
  }
}

// ----------------------------------------------
ConferenceUI::VConfManager* ConferenceUI::VConfGUI::get_manager() const {
  //DBG("Here get_manager invocation.");
  return manager_;
}

// ----------------------------------------------
ConferenceUI::VConfWindow& ConferenceUI::VConfGUI::at(size_t index) {
  if (index >= parts_.size()) {
    /*CRT("Index %d of parts is out of bounds [%d:%d].",
        index,
        0,
        parts_.size() - 1);*/
    throw VConfGUICommonException("Index of parts is out of bounds");
  } else {
    //DBG("Extracts [%d] parts", index);
  }
  return parts_[index];
}

// ----------------------------------------------
/*ConferenceUI::VConfWindow ConferenceUI::VConfGUI::at(size_t index) const {
  if (index >= parts_.size()) {
    CRT("Index %d of parts is out of bounds [%d:%d].",
        index,
        0,
        parts_.size() - 1);
    throw VConfGUICommonException("Index of parts is out of bounds");
  } else {
    DBG("Extracts [%d] parts", index);
  }
  return parts_[index];
}*/

// ----------------------------------------------
size_t ConferenceUI::VConfGUI::size() const {
  return parts_.size();
}


/* VConfWindow methods' implementation */
// ----------------------------------------------------------------------------
ConferenceUI::VConfWindow::VConfWindow(
    const std::string& win_name,
    const std::string& win_title,
    int width,
    int height,
    Eina_Bool is_rotate,
    const std::string& edj_filename,
    const std::string& group_name)
    : /*EinaLogger("VConfWindow", VCONFGUI_LOG_COLOR)
    ,*/ window_(NULL)
    , layout_(NULL) {
  printf("CONSTR-WIN\n");
  window_ = elm_win_add(NULL, win_name.c_str(), ELM_WIN_BASIC);

  if (!window_) {
    //CRT("Window could not be created!");
    throw VConfWindowCommonException("Window could not be created!");
  } else {
    //DBG("Window was created.");
  }

  elm_win_title_set(window_, win_title.c_str());

  /* Rotate the window: 90 degrees counter-clockwise */
  if (is_rotate) {
    //DBG("Rotation on 90 degree counter-clockwise.");
    elm_win_rotation_set(window_, 90);
  } else {
    //DBG("No rotation.");
  }

  /* The main layout containing other layouts. Provided for convenient way
   * of adaptive resizing of main window. The other layouts are represented
   * in terms of SWALLOW parts, which should be further swallowed by
   * real layouts with complete functionality. */
  layout_ = elm_layout_add(window_);

  if (!layout_) {
    //CRT("Layout could not be created on window!");
    throw VConfWindowCommonException("Layout could not be created on window!");
  } else {
    //DBG("Layout was added.");
  }

  if (!elm_layout_file_set(
      layout_,
      edj_filename.c_str(),
      group_name.c_str())
      ) {
    /*CRT("Could not set theme %s or group %s",
        edj_filename.c_str(),
        group_name.c_str());*/
    throw VConfWindowCommonException("EDJ theme file or group are unset!");
  } else {
    /*DBG("Theme file .EDJ %s and group %s were set.",
        edj_filename.c_str(),
        group_name.c_str());*/
  }

  evas_object_show(layout_);

  elm_win_resize_object_add(window_, layout_);
  evas_object_size_hint_weight_set(layout_, 1, 1);
  //DBG("Layout size is managed by window.");

  evas_object_resize(window_, width, height);
  evas_object_show(window_);
}

// ----------------------------------------------
ConferenceUI::VConfWindow::~VConfWindow() {
  //DBG("Here destructor ~VConfWindow invocation.");
  printf("DESTR-WIN: %p, evas: %p\n", this, this->get_window());
  /*for (std::vector<Evas_Object*>::iterator it = sublayouts_.begin();
      it != sublayouts_.end();
      ++it
      ) {
    evas_object_del(*it);
  }
  evas_object_del(layout_);
  evas_object_del(window_);*/
}

// ----------------------------------------------
Evas_Object* ConferenceUI::VConfWindow::get_window() const {
  //DBG("Here get_window invocation.");
  return window_;
}

// ----------------------------------------------
Evas_Object* ConferenceUI::VConfWindow::get_layout() const {
  //DBG("Here get_layout invocation.");
  return layout_;
}

// ----------------------------------------------
void ConferenceUI::VConfWindow::add_delete_cb(
    Evas_Smart_Cb del_cb,
    void* data) const {
  evas_object_smart_callback_add(
      window_,
      "delete,request",
      del_cb,
      data);
  //DBG("New delete,request callback was set for window %p", window_);
}

// ----------------------------------------------
void ConferenceUI::VConfWindow::add_win_props(
    Eina_Bool is_borderless,
    Eina_Bool is_shaped) const {
  elm_win_borderless_set(window_, is_borderless);
  elm_win_shaped_set(window_, is_shaped);
}

// ----------------------------------------------
size_t ConferenceUI::VConfWindow::add_sublayout(
    const std::string& edj_filename,
    const std::string& group_name,
    const std::string& swallow_partname
    ) {
  printf("ADD SUB\n");
  Evas_Object* sublayout = elm_layout_add(layout_);

  if (!sublayout) {
    //ERR("Sublayout hasn't been added.");
    return 0;
  } else {
    //DBG("Sublayout %p has been added.", sublayout);
  }

  if (!elm_layout_file_set(
      sublayout,
      edj_filename.c_str(),
      group_name.c_str())
      ) {
    /*ERR("Could not set theme %s or group %s",
        edj_filename.c_str(),
        group_name.c_str());*/
  } else {
    /*DBG("Theme file .EDJ %s and group %s were set.",
        edj_filename.c_str(),
        group_name.c_str());*/
  }

  elm_object_part_content_set(layout_, swallow_partname.c_str(), sublayout);
  /*DBG("Swallowed part %s with object %p.",
      swallow_partname.c_str(),
      sublayout);*/

  size_t index_of_layout = sublayouts_.size();
  sublayouts_.push_back(sublayout);
  //INF("New sublayout has been pushed back to VConfWindow::sublayouts_.");
  printf("ADD SUB FINAL: %d, last: %p\n",
         sublayouts_.size(), &sublayouts_.back());
  return index_of_layout;
}

// ----------------------------------------------
Evas_Object*& ConferenceUI::VConfWindow::operator[](size_t index) {
  if (index >= sublayouts_.size()) {
    /*CRT("Index %d of sublayout is out of bounds [%d:%d].",
        index,
        0,
        sublayouts_.size() - 1);*/
    throw VConfWindowCommonException("Index of sublayout is out of bounds");
  } else {
    //DBG("Extracts [%d] sublayout", index);
  }

  return sublayouts_[index];
}

// ----------------------------------------------
/*Evas_Object* ConferenceUI::VConfWindow::operator[](size_t index) const {
  if (index >= sublayouts_.size()) {
    CRT("Index %d of sublayout is out of bounds [%d:%d].",
        index,
        0,
        sublayouts_.size() - 1);
    throw VConfWindowCommonException("Index of sublayout is out of bounds");
  } else {
    DBG("Extracted [%d] sublayout.", index);
  }

  return sublayouts_[index];
}*/

// ----------------------------------------------
Evas_Object* ConferenceUI::VConfWindow::get_edje(size_t index) const {
  Evas_Object* edje = elm_layout_edje_get(sublayouts_[index]);
  if (!edje) {
    //ERR("Edje Object on index %d not found.", index);
    return NULL;
  } else {
    //DBG("Extracted [%d] edje object.", index);
  }

  return edje;
}

// ----------------------------------------------
Evas_Object* ConferenceUI::VConfWindow::get_widget(
    size_t index,
    const std::string& partname) const {
  Evas_Object* edje = elm_layout_edje_get(sublayouts_[index]);

  if (!edje) {
    //ERR("Edje Object on index %d not found.", index);
    return NULL;
  } else {
    //DBG("Extracted [%d] edje object.", index);
  }

  Evas_Object* widget =
      edje_object_part_external_object_get(edje, partname.c_str());

  if (!widget) {
    //ERR("Widget on index %d not found.", index);
    return NULL;
  } else {
    //DBG("Extracted [%d] widget.", index);
  }

  return widget;
}

// ----------------------------------------------
size_t ConferenceUI::VConfWindow::size() const {
  return sublayouts_.size();
}


/* VConfManager methods' implementation */
// ----------------------------------------------------------------------------
ConferenceUI::VConfManager::VConfManager()
  : /*EinaLogger("VConfManager", VCONFGUI_LOG_COLOR)
  , vconf_instance_(Conference::Create())
  ,*/ after_(NULL) {
  printf("CONSTR-MANAGER\n");
  /*if (!vconf_instance_) {
    //CRT("Unable to create conference!");
    throw VConfManagerException("Unable to create conference!");
  } else {
    //DBG("Conference was created.");
  }*/
}

// ----------------------------------------------
ConferenceUI::VConfManager::~VConfManager() {
  printf("DESTR-MANAGER\n");
  //delete vconf_instance_;
}

// ----------------------------------------------------------------------------
bool is_invalid(const char* name) {
  return strlen(name) <= 3;
}

// ----------------------------------------------------------------------------
void ConferenceUI::VConfManager::on_click_OK_Connect(
    void* data,
    Evas_Object* obj,
    const char* emission,
    const char* source
    ) {
  conference_info* info = reinterpret_cast<conference_info*>(data);
  info->name = elm_entry_entry_get(info->entry);

  /*Conference::JoinParameters params;
  snprintf(
      const_cast<char*>(params.conferenceName),
      sizeof(params.conferenceName),
      "%s",
      info->name);
  info->gui->get_manager()->vconf_instance_->Join(params);*/printf("Join()\n");

  if (is_invalid(info->name)) {
    Utility::invoke_popup(
        info->window,
        Utility::_popup_button_clicked,
        Utility::_popup_block_clicked,
        "Cannot connect to host.",
        "Skip");
  } else {
    edje_object_signal_callback_del(
        obj,
        emission,
        source,
        on_click_OK_Connect);
    info->gui->pop_window();
    evas_object_del(info->window);
    delete info;

    info->gui->get_manager()->after(info->gui);
  }
}

// ----------------------------------------------
void ConferenceUI::VConfManager::on_click_CANCEL_Connect(
    void* data,
    Evas_Object* obj,
    const char* emission,
    const char* source
    ) {
  printf("CANCEL Connect\n");
  handle_CANCEL(data, obj, emission, source, on_click_CANCEL_Connect);
}


// ----------------------------------------------------------------------------
void ConferenceUI::VConfManager::on_click_OK_CreateConf(
    void* data,
    Evas_Object* obj,
    const char* emission,
    const char* source
    ) {
  conference_info* info = reinterpret_cast<conference_info*>(data);
  info->name = elm_entry_entry_get(info->entry);

  /*Conference::OrganizeParameters params;
  snprintf(
      const_cast<char*>(params.conferenceName),
      sizeof(params.conferenceName),
      "%s",
      info->name);
  info->gui->get_manager()->vconf_instance_->Organize(params);*/printf("Organize()\n");

  if (is_invalid(info->name)) {
    Utility::invoke_popup(
        info->window,
        Utility::_popup_button_clicked,
        Utility::_popup_block_clicked,
        "Conference is already exist!",
        "Skip");
  } else {
    edje_object_signal_callback_del(
        obj,
        emission,
        source,
        on_click_OK_CreateConf);
    info->gui->pop_window();
    evas_object_del(info->window);
    delete info;

    info->gui->get_manager()->after(info->gui);
  }
}

// ----------------------------------------------
void ConferenceUI::VConfManager::on_click_CANCEL_CreateConf(
    void* data,
    Evas_Object* obj,
    const char* emission,
    const char* source
    ) {
  printf("CANCEL CreateConf\n");
  handle_CANCEL(data, obj, emission, source, on_click_CANCEL_CreateConf);
}

// ----------------------------------------------
void ConferenceUI::VConfManager::set_after(PTR_AFTER_FUNC handler) {
  after_ = handler;
}

// ----------------------------------------------
ConferenceUI::VConfManager::PTR_AFTER_FUNC
ConferenceUI::VConfManager::get_after() const {
  return after_;
}

// ----------------------------------------------
void ConferenceUI::VConfManager::after(void* data) const {
  after_(data);
}

// ----------------------------------------------
/*Conference::VConference*
ConferenceUI::VConfManager::get_instance() const {
  return vconf_instance_;
}*/

// ----------------------------------------------
void ConferenceUI::VConfManager::handle_CANCEL(
    void* data,
    Evas_Object* obj,
    const char* emission,
    const char* source,
    SIG_CB_FUNC handler
    ) {
  conference_info* info = reinterpret_cast<conference_info*>(data);

  edje_object_signal_callback_del(
      obj,
      emission,
      source,
      handler);

  evas_object_show(info->gui->at(0).get_window());
  printf("CANCEL: (main %p, evas: %p), subwin_evas: %p, size: %d\n",
         &(info->gui->at(0)), info->gui->at(0).get_window(),
         info->window, info->gui->size());
  info->gui->pop_window();
  printf("CANCEL: pop_size: %d, subwin_evas: %p\n",
         info->gui->size(), info->window);
  evas_object_del(info->window);

  delete info;
}
