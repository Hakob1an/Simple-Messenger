#ifndef INTCELL_HPP
#define INTCELL_HPP

#include "abstractCell.hpp"

class IntCell : public AbstractCell
{
public:
    IntCell();
    std::string getString() const override;
    double getDouble() const override;
    int getInt() const override;
    void setString(const std::string& str) override;
    bool operator==(const AbstractCell& other) const override;

private:
    int m_value;
};

#endif //INTCELL_HPP
