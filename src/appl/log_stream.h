#ifndef _LVIZ_APPL_LOG_STREAM_H
#define _LVIZ_APPL_LOG_STREAM_H

#include "../ui/log.h"

#include <iostream>
#include <streambuf>
#include <string>

namespace lviz {
namespace appl {

class LogStream : public std::basic_streambuf<char> {
public:
  LogStream(std::ostream &stream, ui::Log *log_buf);

  ~LogStream();

private:
  virtual int_type overflow(int_type v) override;

  virtual std::streamsize xsputn(const char *p, std::streamsize n) override;

private:
  std::string string_;
  std::ostream &stream_;
  std::streambuf *old_buf_;
  ui::Log *log_buf_;
};

} // namespace appl
} // namespace lviz

#endif
