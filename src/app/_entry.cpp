#include <iostream>
#include <formatter.hpp>

int main() {
  fmt::formatter formatter(std::cin, std::cout);
  formatter();
  return 0;
}
