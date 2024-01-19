#ifndef STRINGCELL_HPP
#define STRINGCELL_HPP

#include "abstractCell.hpp"

class StringCell : public AbstractCell
{
public:
    StringCell() = default;
    std::string getString() const override;
    void setString(const std::string& str) override;
    double getDouble() const override;
    int getInt() const override;
    bool operator==(const AbstractCell& cell) const override;
private:
    std::string m_value;
};

#endif //STRINGCELL_HPP
