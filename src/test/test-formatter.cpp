#include <catch2/catch.hpp>
#include <formatter.hpp>
#include <sstream>

using namespace fmt;
using tested_t = formatter;

TEST_CASE("formatter", "[lib]") {

  SECTION("creation") {
    std::stringstream istream;
    std::stringstream ostream;
    tested_t tested(istream, ostream);
  }

  SECTION("streams") {

    SECTION("letters") {
      std::stringstream istream("abc");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "abc");
    }

    SECTION("commas") {
      std::stringstream istream("ab,c");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "ab,\nc");
    }

    SECTION("only brackets") {
      std::stringstream istream("{{}}");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "\n{\n  {\n  }\n}");
    }

    SECTION("balanced brackets") {
      std::stringstream istream("{{c}d}");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "\n{\n  {\n    c\n  }\n  d\n}");
    }

    SECTION("unbalanced brackets - more opened") {
      std::stringstream istream("{ab{c");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "\n{\n  ab\n  {\n    c");
    }

    SECTION("unbalanced brackets - more closed") {
      std::stringstream istream("c}d}");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "c\n}\nd\n}");
    }

    SECTION("brackets and commas") {
      std::stringstream istream("{a,b{c,d}e}");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "\n{\n  a,\n  b\n  {\n    c,\n    d\n  }\n  e\n}");
    }

    SECTION("brackets commas and spaces") {
      std::stringstream istream("{ a = 1, b = 2 { c = 3, d = 4 } e = 5 }");
      std::stringstream ostream;
      tested_t tested(istream, ostream);
      tested();
      REQUIRE(ostream.str() == "\n{\n  a = 1,\n  b = 2 \n  {\n    c = 3,\n    d = 4 \n  }\n  e = 5 \n}");
    }
  }
}
