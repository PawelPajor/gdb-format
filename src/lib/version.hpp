#pragma once

#include <iosfwd>
#include <ostream>

namespace fmt {
struct version  {
  int major;
  int minor;
  const char *datestamp;
  const char *timestamp;

  static version current();
  friend std::ostream &operator<<(std::ostream &os, const version &version);
};
}
