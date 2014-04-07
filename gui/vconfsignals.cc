/*! @file vconfsignals.cc
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

#include "src/ui/vconfsignals.h"


/* Register external signal issued in vconference.h */
// ----------------------------------------------------------------------------
void UIExternalSignalHandlers::register_external_signal(
    Conference::EventTypes event_type,
    void handler(const void* args),
    const void* data
    ) {
  auto ptr_vconf = Conference::Create();
  ptr_vconf->Events += {event_type, handler};

  delete ptr_vconf;
}

// ----------------------------------------------
void UIExternalSignalHandlers::unreg_external_signal(
    Conference::EventTypes event_type,
    void handler(const void* args),
    const void* data
    ) {
}


/* Implementation of handlers of external signals */
// ----------------------------------------------------------------------------
void UIExternalSignalHandlers::get_sink(const void* data) {
}

// ----------------------------------------------
void UIExternalSignalHandlers::add_participant(const void* data) {
}

// ----------------------------------------------
void UIExternalSignalHandlers::remove_participant(const void* data) {
}

// ----------------------------------------------
void UIExternalSignalHandlers::handle_connected(const void* data) {
}

// ----------------------------------------------
void UIExternalSignalHandlers::handle_disconnected(const void* data) {
}
