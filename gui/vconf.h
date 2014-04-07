/*! @file vconf.h
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

#ifndef SRC_UI_VCONF_H_
#define SRC_UI_VCONF_H_

#include <Elementary.h>
#include <string>
#include <vector>
/*#include "include/death_handler.h"
#include "include/eina_logger.h"*/
/*#include "include/vconference.h"  // user API*/
#include "vconfdeclare.h"  // declare common vars
#include "vconfpopup.h"  // GUI popups common methods

#define __UNUSED__

namespace ConferenceUI {

class VConfWindow;
class VConfManager;

typedef void SIG_CB_FUNC (void*, Evas_Object*, void*);

// ----------------------------------------------------------------------------
class VConfGUI/* : public EinaLogger*/ {
 public:
  VConfGUI();
  virtual ~VConfGUI();

  size_t add_window(
      const std::string& win_name,
      const std::string& win_title,
      int width,
      int height,
      Eina_Bool is_rotate,
      const std::string& edj_filename,
      const std::string& group_name);
  void pop_window();

  VConfManager* get_manager() const;

  VConfWindow& at(size_t index);
  // VConfWindow at(size_t index) const;

  size_t size() const;

  class VConfGUICommonException {
   public:
    explicit VConfGUICommonException(const std::string& msg) : info_(msg) {}
    inline void what() const throw() {
      printf("%s\n", info_.c_str());
    }
   private:
    std::string info_;
  };

 private:
  VConfManager* manager_;
  std::vector<VConfWindow> parts_;
};


// ----------------------------------------------------------------------------
class VConfWindow/* : public EinaLogger*/ {
 public:
  VConfWindow(
      const std::string& win_name,
      const std::string& win_title,
      int width,
      int height,
      Eina_Bool is_rotate,
      const std::string& edj_filename,
      const std::string& group_name);

  virtual ~VConfWindow();

  Evas_Object* get_window() const;
  Evas_Object* get_layout() const;

  void add_delete_cb(Evas_Smart_Cb del_cb, void* data) const;
  void add_win_props(Eina_Bool is_borderless, Eina_Bool is_shaped) const;

  size_t add_sublayout(
      const std::string& edj_filename,
      const std::string& group_name,
      const std::string& swallow_partname);

  Evas_Object*& operator[](size_t index);
  // Evas_Object* operator[](size_t index) const;

  Evas_Object* get_edje(size_t index) const;
  Evas_Object* get_widget(size_t index, const std::string& partname) const;

  size_t size() const;

  class VConfWindowCommonException {
   public:
    explicit VConfWindowCommonException(const std::string& msg) : info_(msg) {}
    inline void what() const throw() {
      printf("%s\n", info_.c_str());
    }
   private:
    std::string info_;
  };

 private:
  Evas_Object* window_;
  Evas_Object* layout_;
  std::vector<Evas_Object*> sublayouts_;
};


// ----------------------------------------------------------------------------
class VConfManager/* : public EinaLogger*/ {
 public:
  typedef void SIG_CB_FUNC (void*, Evas_Object*, const char*, const char*);
  typedef void (*PTR_AFTER_FUNC) (void* data);

  VConfManager();
  virtual ~VConfManager();
  static SIG_CB_FUNC on_click_OK_Connect;
  static SIG_CB_FUNC on_click_CANCEL_Connect;
  static SIG_CB_FUNC on_click_OK_CreateConf;
  static SIG_CB_FUNC on_click_CANCEL_CreateConf;

  void set_after(PTR_AFTER_FUNC handler);
  PTR_AFTER_FUNC get_after() const;
  void after(void* data) const;

  //Conference::VConference* get_instance() const;

  class VConfManagerException {
   public:
    explicit VConfManagerException(const std::string& msg) : info_(msg) {}
    inline void what() const throw() {
      printf("%s\n", info_.c_str());
    }
   private:
    std::string info_;
  };

 private:
  //Conference::VConference* vconf_instance_;
  PTR_AFTER_FUNC after_;

  static void handle_CANCEL(
      void* data,
      Evas_Object* obj,
      const char* emission,
      const char* source,
      SIG_CB_FUNC handler);
};


// ----------------------------------------------------------------------------
struct conference_info {
  const char* name;
  Evas_Object* entry;
  Evas_Object* window;
  VConfGUI* gui;

  conference_info(
      const char* n,
      Evas_Object* e,
      Evas_Object* w,
      VConfGUI* g)
    : name(n)
    , entry(e)
    , window(w)
    , gui(g)
  {}
};

}  // end namespace ConferenceUI

#endif  // SRC_UI_VCONF_H_
