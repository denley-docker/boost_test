#ifndef __SERIAL_TEST_SERIAL_PORT_H__
#define __SERIAL_TEST_SERIAL_PORT_H__

#include <boost/asio/io_service.hpp>
#include <boost/asio/serial_port.hpp>

class Log;
class SerialPortTimer;
class SerialPort
{
public:
  friend class SerialPortTimer;
  SerialPort(std::shared_ptr<Log> log, boost::asio::io_service& io, unsigned int timeout);
  ~SerialPort();
  bool isOpen() const;
  void open(const char* port, unsigned int baudrate);
  void close();
  void asyncRead();

private:
  void setOption(unsigned int baudrate, unsigned int characterSize);
  void reOpen();

  std::string port;
  unsigned int baudrate;
  boost::asio::serial_port impl;
  std::shared_ptr<SerialPortTimer> timer;
  std::shared_ptr<Log> log;
};

#endif
