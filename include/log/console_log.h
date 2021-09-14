#ifndef __SERIAL_TEST_LOG_CONSOLE_LOG_H__
#define __SERIAL_TEST_LOG_CONSOLE_LOG_H__

#include "log/log.h"

class ConsoleLog : public Log
{
public:
  virtual void debug(const char* value) const;
  virtual void info(const char* value) const;
  virtual void error(const char* value) const;
};

#endif
