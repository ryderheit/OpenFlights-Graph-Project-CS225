#include "data.h"

auto CSV::readNextRow(std::istream& str) -> void {
  std::getline(str, m_line);

  m_data.clear();
  m_data.emplace_back(-1);
  std::string::size_type pos = 0;
  while((pos = m_line.find(',', pos)) != std::string::npos)
  {
    m_data.emplace_back(pos);
    ++pos;
  }
  pos   = m_line.size();
  m_data.emplace_back(pos);
}


auto CSV::size() -> std::size_t {
 return m_data.size() - 1;
}

std::istream& operator>>(std::istream& str, CSV& data) {
  data.readNextRow(str);
  return str;
}   
