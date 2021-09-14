#include "serial_port.h"
#include "log/console_log.h"
#include <boost/asio/io_service.hpp>
#include <boost/version.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
  boost::asio::io_service io;
  SerialPort serialPort(std::make_shared<ConsoleLog>(), io, 5000);
  serialPort.open("/dev/tty.usbserial-A50285BI", 115200);
  if (serialPort.isOpen())
    serialPort.asyncRead();
  io.run();

  std::cout << "Hello, Boost " << BOOST_VERSION << std::endl;
  return 0;
}
