#include "serial_port.h"
#include "serial_helper.h"
#include "log/log.h"
#include <cassert>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

class SerialPortTimer
{
public:
  SerialPortTimer(io_service& io, SerialPort* serialPort, unsigned int timeout)
    : hasRead(false), timeout(timeout), timer(io), serialPort(serialPort)
  {
  }

  void asyncRead()
  {
    setTimer();
    doAsyncRead();
  }

private:
  void doAsyncRead()
  {
    static const std::string delim(2, 0x55);
    async_read_until(serialPort->impl, readContent, delim,
      boost::bind(&SerialPortTimer::callbackAsyncRead, this, placeholders::error, placeholders::bytes_transferred));
  }

  void callbackAsyncRead(const boost::system::error_code& ec, std::size_t readSize)
  {
    if (ec || readSize == 0)
    {
      serialPort->log->error(ArgusaiHelper::format("Read error: %s", ec.message().c_str()).c_str());
      return ;
    }

    boost::asio::streambuf::const_buffers_type content = readContent.data();
    std::vector<uint8_t> result(boost::asio::buffers_begin(content), boost::asio::buffers_begin(content) + readSize);
    serialPort->log->info(ArgusaiHelper::convertToHex(result).c_str());
    readContent.consume(readSize);

    hasRead = true;
    doAsyncRead();
  }

  void setTimer()
  {
    timer.expires_from_now(boost::posix_time::milliseconds(timeout));
    timer.async_wait(boost::bind(&SerialPortTimer::callbackTimeout, this, placeholders::error));
  }

  void callbackTimeout(const boost::system::error_code& ec)
  {
    if (ec)
    {
      serialPort->log->error(ArgusaiHelper::format("Timer error: %s", ec.message().c_str()).c_str());
      return ;
    }

    if (!hasRead)
    {
      serialPort->reOpen();
      if (serialPort->isOpen())
        doAsyncRead();
    }
    hasRead = false;
    setTimer();
  }
  bool hasRead;
  unsigned int timeout;
  deadline_timer timer;
  SerialPort* serialPort;
  streambuf readContent;
};

SerialPort::SerialPort(std::shared_ptr<Log> log, io_service& io, unsigned int timeout)
  : impl(io), port(std::string()), baudrate(0), log(log)
{
  timer = std::make_shared<SerialPortTimer>(io, this, timeout);
}

SerialPort::~SerialPort()
{
  if (isOpen())
    close();
}

bool SerialPort::isOpen() const
{
  return impl.is_open();
}

void SerialPort::open(const char* port, unsigned int baudrate)
{
  assert(!isOpen());

  boost::system::error_code ec;
  impl.open(port, ec);
  if (ec)
  {
    log->error(ArgusaiHelper::format("Open %s with %d error: %s", port, baudrate, ec.message().c_str()).c_str());
    return ;
  }

  setOption(baudrate, 8);
  this->port = port;
  log->info(ArgusaiHelper::format("Open %s with %d success", port, baudrate).c_str());
}

void SerialPort::setOption(unsigned int baudrate, unsigned int characterSize)
{
  impl.set_option(serial_port::baud_rate(baudrate));
  impl.set_option(serial_port::flow_control(serial_port::flow_control::none));
  impl.set_option(serial_port::parity(serial_port::parity::none));
  impl.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
  impl.set_option(serial_port::character_size(characterSize));
  this->baudrate = baudrate;
}

void SerialPort::close()
{
  assert(isOpen());
  impl.close();
  log->info(ArgusaiHelper::format("Close %s ", port.c_str()).c_str());
}

void SerialPort::asyncRead()
{
  assert(isOpen());
  timer->asyncRead();
}

void SerialPort::reOpen()
{
  if (isOpen())
    close();

  open(port.c_str(), baudrate);
}
