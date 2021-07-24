#include <fstream>
#include <iostream>

#include "table.h"

using namespace std;
using namespace MyExcel;

int main() {
  MyExcel::TxtTable table(5, 5);
  std::ofstream out("test.txt");

  table.reg_cell(new Cell("Hello~", 0, 0, &table), 0, 0);
  table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);

  table.reg_cell(new Cell("Programming", 1, 1, &table), 1, 1);
}