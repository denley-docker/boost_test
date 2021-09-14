#ifndef __SERIAL_TEST_LOG_LOG_H__
#define __SERIAL_TEST_LOG_LOG_H__

class Log
{
public:
  virtual void debug(const char* value) const = 0;
  virtual void info(const char* value) const = 0;
  virtual void error(const char* value) const = 0;
};

#endif
