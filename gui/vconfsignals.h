/*! @file vconfsignals.h
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

#ifndef SRC_UI_VCONFSIGNALS_H_
#define SRC_UI_VCONFSIGNALS_H_

#include "include/vconference.h"


namespace UIExternalSignalHandlers {

// ----------------------------------------------
void register_external_signal(
    Conference::EventTypes event_type,
    void handler(const void* args),
    const void* data);

// ----------------------------------------------
void unreg_external_signal(
    Conference::EventTypes event_type,
    void handler(const void* args),
    const void* data);

// ----------------------------------------------
enum SinkStatus {sFree, sBusy, sUnknown};

void get_sink(const void* data);
void add_participant(const void* data);
void remove_participant(const void* data);
void handle_connected(const void* data);
void handle_disconnected(const void* data);

}  // end namespace UIExternalSignalHandlers

#endif  // SRC_UI_VCONFSIGNALS_H_
