#include "formatter.hpp"
#include <iostream>
#include <iterator>

namespace fmt {

namespace {
constexpr auto end = std::istream_iterator<char>();
}

formatter::formatter(std::istream &istream, std::ostream &ostream)
    : istream_(istream), ostream_(ostream), handlers_(create_handler_map()) {
}

void formatter::operator()() {
  istream_ >> std::noskipws;
  while (istream_) {
    handle_char();
  }
}

formatter::handlers_map_t formatter::create_handler_map() {
  return {
      {',', &formatter::handle_comma},
      {'{', &formatter::handle_open_bracket},
      {'}', &formatter::handle_close_bracket},
  };
}

std::optional<char> formatter::peek() {
  const int peeked = this->istream_.peek();
  if (peeked == EOF) {
    return std::nullopt;
  }
  return static_cast<char>(peeked);
}

void formatter::copy_char() {
  char c;
  istream_ >> c;
  ostream_ << c;
}

void formatter::new_line() const {
  ostream_ << '\n';
  if (indent_ > 0) {
    ostream_ << std::string(indent_ * 2, ' ');
  }
}

void formatter::conditional_new_line() {
  if (const auto &opt = peek(); opt) {
    const auto &c = opt.value();
    if (c != ',' && c != '{' && c != '}') {
      new_line();
    }
  }
}

void formatter::handle_char() {
  if (const auto opt = peek(); opt) {
    if (auto found = handlers_.find(opt.value()); found != handlers_.end()) {
      found->second(*this);
    } else {
      copy_char();
    }
  }
}

void formatter::handle_comma() {
  copy_char();
  skip_ws_to_new_line();
}

void formatter::handle_open_bracket() {
  new_line();
  copy_char();
  indent_++;
  skip_ws_to_new_line();
}

void formatter::handle_close_bracket() {
  if (indent_ > 0) {
    indent_--;
  }
  new_line();
  copy_char();
  skip_ws_to_new_line();
}

void formatter::skip_ws_to_new_line() {
  while (const auto opt = peek()) {
    const auto &c = opt.value();
    if (!std::isspace(c)) {
      break;
    }
    char _;
    istream_ >> _;
  }
  conditional_new_line();
}

}
