#include "serial_helper.h"
#include <cstdarg>
#include <vector>

std::string ArgusaiHelper::formatEx(const char * fmt, va_list& args)
{
  int length = getLength(fmt, args) + 1;
  std::vector<char> result(length);
  vsnprintf(result.data(), length, fmt, args);
  return result.data();
}

std::string ArgusaiHelper::format(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  std::string result = formatEx(fmt, args);
  va_end(args);
  return result;
}

unsigned int ArgusaiHelper::getLength(const char * fmt, va_list& args)
{
  va_list tempArgs;
  va_copy(tempArgs, args);
  unsigned int result = vsnprintf(nullptr, 0, fmt, tempArgs);
  va_end(tempArgs);
  return result;
}

std::string ArgusaiHelper::convertToHex(const std::vector<uint8_t>& source)
{
  char result[512] = {0x00};
  size_t size = source.size();
  for (size_t index = 0; index < size; ++index)
  {
    sprintf(&result[2*index], "%02X", source[index]);
  }
  return result;
}
