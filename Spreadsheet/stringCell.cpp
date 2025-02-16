#include "stringCell.hpp"


std::string StringCell::getString() const
{
    return m_value;
}
double StringCell::getDouble() const
{
    return std::stod(m_value);
}
int StringCell::getInt() const
{
    return std::stoi(m_value);
}
void StringCell::setString(const std::string& str)
{
    m_value = str;
}
bool StringCell::operator==(const AbstractCell& other) const 
{
    const StringCell* otherStringCell = dynamic_cast<const StringCell*>(&other);
    return (otherStringCell != nullptr) && (m_value == otherStringCell->m_value);
}
