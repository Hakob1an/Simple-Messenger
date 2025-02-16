#include "sheet.hpp"

Spreadsheet::Spreadsheet() 
    : m_row{0}
    , m_col{0}
{}
Spreadsheet::Spreadsheet(size_t width, size_t height) 
    : m_row{width}
    , m_col{height} 
{
    m_cells.resize(m_row, std::vector<AbstractCell*>(m_col, nullptr));
}
Spreadsheet::Spreadsheet(const Spreadsheet& src) 
    : Spreadsheet(src.m_row, src.m_col) 
{
    for (size_t i{0}; i < m_row; ++i) {
       for (size_t j{0}; j < m_col; ++j) {
          m_cells[i][j] = src.m_cells[i][j];
       }
    }
}
Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
{
    swap(src);
}
void Spreadsheet::cleanup() noexcept 
{
    m_cells.clear(); 
    m_row = 0;
    m_col = 0;
}
void Spreadsheet::moveFrom(Spreadsheet& src) noexcept 
{
    m_row = src.m_row;
    m_col = src.m_col;
    m_cells = std::move(src.m_cells);
   
    src.m_row = 0;
    src.m_col = 0;
}
void Spreadsheet::verifyCoord(size_t x, size_t y) const
{
    if (x >= m_row || y >= m_col) {
      throw std::out_of_range("Invalid index!");
    }
}
void Spreadsheet::setCell(size_t x, size_t y, AbstractCell* cell) 
{
    verifyCoord(x, y);
    m_cells[x][y] = cell;
}
void Spreadsheet::setCell(size_t x, size_t y, const std::string& value)
{
    verifyCoord(x, y);
    m_cells[x][y]->setString(value);
}
const AbstractCell* Spreadsheet::getCell(size_t x, size_t y) const 
{
    try {
        verifyCoord(x, y);
        return m_cells[x][y];
    } catch (const std::out_of_range& e) {
        return nullptr;  
    }
}
AbstractCell* Spreadsheet::getCell(size_t x, size_t y) {
    return const_cast<AbstractCell*>(std::as_const(*this).getCell(x, y));
}
void Spreadsheet::swap(Spreadsheet& rhs) noexcept 
{
    std::swap(m_row, rhs.m_row);
    std::swap(m_col, rhs.m_col);
    std::swap(m_cells, rhs.m_cells);
}
Spreadsheet& Spreadsheet::operator=(Spreadsheet& rhs)
{
    swap(rhs);

    return *this;
}
std::vector<AbstractCell*>& Spreadsheet::operator[](size_t index)
{
    return m_cells[index];
}
const std::string Spreadsheet::operator[](const AbstractCell& cell) const 
{
    for (size_t i{0}; i < m_row; ++i) {
        for (size_t j{0}; j < m_col; ++j) {
          if (*m_cells[i][j] == cell) {
             return cell.getString();
          }
       }
    }
    
    return "";
}
Spreadsheet::~Spreadsheet() 
{
    cleanup();
}
void Spreadsheet::addRow(size_t row) 
{
    if (row == 0) {
        return;
    }

    std::vector<AbstractCell*> newRow(m_col, nullptr);
    m_cells.push_back(newRow);
    ++m_row;
}
void Spreadsheet::addColumn(size_t col)
{
    if (col == 0) {
        return;
    }
    
    for (size_t i = 0; i < m_row; ++i) {
        m_cells[i].push_back(nullptr);
    }
    ++m_col;
}
void Spreadsheet::removeRow(size_t row) 
{
    if (m_row > 0) {
        for (size_t j = 0; j < m_col; ++j) {
            delete m_cells[m_row - 1][j];
        }
        m_cells.pop_back();
        --m_row;
    }
}
void Spreadsheet::removeColumn(size_t col) 
{
    if (m_col > 0) {
        for (size_t i = 0; i < m_row; ++i) {
            delete m_cells[i][m_col - 1];
            m_cells[i].pop_back();
        }
        --m_col;
    }
}
void Spreadsheet::print() const 
{
    for (const auto& row : m_cells) {
        for (const auto cell : row) {
            if (cell) {
                std::cout << cell->getString() << "\t";
            } else {
                std::cout << "-\t";
            }
        }
        std::cout << std::endl;
    }
}
