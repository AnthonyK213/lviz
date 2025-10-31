#include "log_stream.h"

namespace lviz {
namespace appl {

LogStream::LogStream(std::ostream &stream, ui::Log *log_buf)
    : stream_(stream), log_buf_(log_buf), old_buf_(stream.rdbuf()) {
  stream.rdbuf(this);
}

LogStream::~LogStream() {
  if (!string_.empty())
    log_buf_->Print(string_);
  stream_.rdbuf(old_buf_);
}

std::streambuf::int_type LogStream::overflow(int_type v) {
  if (v == '\n') {
#ifndef NDEBUG
    std::printf("%s\n", string_.c_str());
    std::fflush(stdout);
#endif
    log_buf_->Print(string_);
    string_.erase(string_.begin(), string_.end());
  } else
    string_ += v;

  return v;
}

std::streamsize LogStream::xsputn(const char *p, std::streamsize n) {
  string_.append(p, p + n);

  size_t pos = 0;
  while (pos != std::string::npos) {
    pos = string_.find('\n');
    if (pos != std::string::npos) {
      std::string tmp(string_.begin(), string_.begin() + pos);
#ifndef NDEBUG
      std::printf("%s\n", tmp.c_str());
      std::fflush(stdout);
#endif
      log_buf_->Print(tmp);
      string_.erase(string_.begin(), string_.begin() + pos + 1);
    }
  }

  return n;
}

} // namespace appl
} // namespace lviz
