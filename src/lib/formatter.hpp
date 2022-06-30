#pragma once

#include <functional>
#include <iosfwd>
#include <optional>
#include <unordered_map>

namespace fmt {
class formatter {
public:
  formatter(std::istream &istream, std::ostream &ostream);
  void operator()();

private:

  using char_handler_t = std::function<void(formatter &)>;
  using handlers_map_t = std::unordered_map<char, char_handler_t>;

  static handlers_map_t create_handler_map();

  std::optional<char> peek();
  void copy_char();
  void new_line() const;
  void conditional_new_line();
  void handle_char();
  void handle_comma();
  void handle_open_bracket();
  void handle_close_bracket();
  void skip_ws_to_new_line();

  std::istream &istream_;
  std::ostream &ostream_;
  handlers_map_t handlers_;
  size_t indent_ = 0;
};
}
