#include "intCell.hpp"


IntCell::IntCell() : m_value(0) 
{}
std::string IntCell::getString() const
{
    return std::to_string(m_value);
}
double IntCell::getDouble() const
{
    return static_cast<double>(m_value);
}
int IntCell::getInt() const
{
    return m_value;
}
void IntCell::setString(const std::string& str)
{
    std::stringstream ss{str};
    int value;
    ss >> value;
    if (ss.fail()) {
        std::cout << "Conversion failed!" << std::endl;
    }
    m_value = value;
}
bool IntCell::operator==(const AbstractCell& other) const 
{
    const IntCell* otherIntCell = dynamic_cast<const IntCell*>(&other);
    return (otherIntCell != nullptr) && (m_value == otherIntCell->m_value);
}
