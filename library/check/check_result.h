#pragma once

#include "severity.h"
#include "../util/location.h"

#include <string>
#include <vector>

namespace autotest {
namespace check {

struct check_result
{
  bool passed;
  std::string message;
  util::Location location;
  Severity severity;
};

using check_results = std::vector<check_result>;

} // namespace check
} // namespace autotest
