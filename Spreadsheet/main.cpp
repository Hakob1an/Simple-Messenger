#include "abstractCell.hpp"
#include "intCell.hpp"
#include "doubleCell.hpp"
#include "stringCell.hpp"
#include "sheet.hpp"

#include <iostream>

int main() 
{
   /*IntCell intCell;
   intCell.setString("42");

   DoubleCell doubleCell;
   doubleCell.setString("3.14");

   StringCell stringCell;
   stringCell.setString("Hello, World!");

   Spreadsheet spreadsheet(3, 3);
   spreadsheet.setCell(0, 0, &intCell);
   spreadsheet.setCell(1, 1, &doubleCell);
   spreadsheet.setCell(2, 2, &stringCell);
   spreadsheet.print();*/

   Spreadsheet spreadsheet(3, 3);
   spreadsheet.print();
   std::cout << std::endl;

   spreadsheet.addRow(2); 
   spreadsheet.addColumn(2); 

   IntCell intCell;
   intCell.setString("42");
   
   IntCell intCell2;
   intCell2.setString("4");

   /*DoubleCell doubleCell;
   doubleCell.setString("3.14");*/

   StringCell stringCell;
   stringCell.setString("Hi:)");

   spreadsheet.setCell(0, 0, &intCell);
   spreadsheet.setCell(1, 1, &intCell2);
   spreadsheet.setCell(2, 2, &stringCell);
   
   std::cout << spreadsheet[0][0]->getInt() << std::endl;
   
   spreadsheet.print();
   std::cout << std::endl;
    
   spreadsheet.removeRow(1); 
   spreadsheet.removeColumn(1); 
   
   spreadsheet.print();
   std::cout << std::endl;

   return 0;
}
