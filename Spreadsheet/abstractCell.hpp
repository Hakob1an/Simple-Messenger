#ifndef ABSTRACTCELL_HPP
#define ABSTRACTCELL_HPP

#include <string>
#include <sstream>
#include <iostream>

class AbstractCell
{
public:
    virtual ~AbstractCell() = default;
    virtual std::string getString() const = 0;
    virtual double getDouble() const = 0;
    virtual int getInt() const = 0;
    virtual void setString(const std::string& str) = 0; 
    virtual bool operator==(const AbstractCell& other) const = 0;
};

#endif //ABSTRACTCELL_HPP
