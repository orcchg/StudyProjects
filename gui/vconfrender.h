/*! @file vconfrender.h
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

#ifndef SRC_UI_VCONFRENDER_H_
#define SRC_UI_VCONFRENDER_H_

#include <string>
#include "vconf.h"

#define VCONF_WIDTH 1000
#define VCONF_HEIGHT 800

namespace ConferenceUI {

// ----------------------------------------------
void show_vconference(void* data);

}  // end namespace ConferenceUI

#endif  // SRC_UI_VCONFRENDER_H_
