#ifndef DOUBLECELL_HPP
#define DOUBLECELL_HPP

#include "abstractCell.hpp"

class DoubleCell : public AbstractCell
{
public:
    DoubleCell();
    std::string getString() const override;
    void setString(const std::string& str) override;
    double getDouble() const override;
    int getInt() const override;
    bool operator==(const AbstractCell& other) const override;

private:
    double m_value;
};

#endif //DOUBLECELL_HPP
