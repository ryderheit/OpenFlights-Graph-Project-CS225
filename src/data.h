#pragma once

#include <iterator>
#include <sstream>
#include <fstream>
#include <iotream>
#include <string>
#include <vector>

class CSV {
public:
  auto size() const -> std::size_t;
  auto readNextRow(std::istream& str) -> void;

private:
  std::string         m_line;
  std::vector<int>    m_data;
};


std::istream& operator>>(std::istream& str, CSV& data);
