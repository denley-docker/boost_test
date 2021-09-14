#ifndef __SERIAL_TEST_SERIAL_HELPER_H__
#define __SERIAL_TEST_SERIAL_HELPER_H__

#include <string>
#include <vector>
#include "serial_helper.h"

class ArgusaiHelper
{
public:
  static std::string format(const char* fmt, ...);
  static std::string convertToHex(const std::vector<uint8_t>& source);

private:
  static std::string formatEx(const char * fmt, va_list& args);
  static unsigned int getLength(const char * fmt, va_list& args);
};

#endif
