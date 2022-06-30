#include <catch2/catch.hpp>
#include <regex>
#include <sstream>
#include <version.hpp>

using namespace fmt;
using namespace std;

TEST_CASE("version", "[lib]") {
  stringstream stream;
  stream << version::current();
  const auto version = stream.str();
  REQUIRE(regex_match(
      version,
      regex(R"([0-9]+\.[0-9]+\.[0-9]{8}\.[0-9]{6})")));
}
