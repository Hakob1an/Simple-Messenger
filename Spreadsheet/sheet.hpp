#ifndef SHEET_HPP
#define SHEET_HPP

#include "abstractCell.hpp"
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <iomanip>

class Spreadsheet
{
public:
   Spreadsheet();
   Spreadsheet(size_t width, size_t height);
   Spreadsheet(const Spreadsheet& src);
   Spreadsheet(Spreadsheet&& src) noexcept;
   ~Spreadsheet();

   Spreadsheet& operator=(Spreadsheet& rhs);
   std::vector<AbstractCell*>& operator[](size_t index);
   const std::string operator[](const AbstractCell& cell) const;
   friend std::ostream& operator<<(std::ostream&, const Spreadsheet&);
   
public:
   const AbstractCell* getCell(size_t row, size_t col) const;
   AbstractCell* getCell(size_t row, size_t col);
   void setCell(size_t x, size_t y, AbstractCell* cell);
   void setCell(size_t row, size_t col, const std::string& value);
   void addRow(size_t row);
   void addColumn(size_t col);
   void removeRow(size_t row);
   void removeColumn(size_t col);
   void print() const;
   void swap(Spreadsheet& sh) noexcept;

private:
   void moveFrom(Spreadsheet& src) noexcept;
   void cleanup() noexcept;
   void verifyCoord(size_t x, size_t y) const;

private:
   size_t m_row;
   size_t m_col;
   std::vector<std::vector<AbstractCell*>> m_cells;
};


#endif //SHEET_HPP
