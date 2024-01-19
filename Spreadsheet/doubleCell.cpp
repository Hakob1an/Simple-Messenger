#include "doubleCell.hpp"


DoubleCell::DoubleCell() : m_value{0.0}
{}
std::string DoubleCell::getString() const
{
    return std::to_string(m_value);
}
double DoubleCell::getDouble() const
{
    return m_value;
}
int DoubleCell::getInt() const
{
    return static_cast<int>(m_value);
}
void DoubleCell::setString(const std::string& str)
{
    std::stringstream ss{str};
    double value;
    ss >> value;
    if (ss.fail()) {
        std::cout << "Conversion failed!" << std::endl;
    }
    m_value = value;
}
bool DoubleCell::operator==(const AbstractCell& other) const 
{
    const DoubleCell* otherDoubleCell = dynamic_cast<const DoubleCell*>(&other);
    return (otherDoubleCell != nullptr) && (m_value == otherDoubleCell->m_value);
}
