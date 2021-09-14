#include "log/console_log.h"
#include <iostream>

void ConsoleLog::debug(const char* value) const
{
  std::cout<<value<<std::endl;
}

void ConsoleLog::info(const char* value) const
{
  std::cout<<value<<std::endl;
}

void ConsoleLog::error(const char* value) const
{
  std::cerr<<value<<std::endl;
}
