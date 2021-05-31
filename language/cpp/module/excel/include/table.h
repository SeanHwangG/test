#pragma once
#include "cell.h"

using MyExcel::Cell;
namespace MyExcel {
class Table {
 protected:
  int max_row, max_col;
  Cell ***data_table;

 public:
  Table(int max_row_size, int max_col_size);
  ~Table();
  void reg_cell(Cell *c, int row, int col);
  int to_numeric(const string &s);
  int to_numeric(int row, int col);
  string stringify(const string &s);
  string stringify(int row, int col);
  virtual string print_table() = 0;
};
std::ostream &operator<<(std::ostream &out, Table &table);

class TxtTable : public Table {
  string repeat_char(int n, char c);
  string col_num_to_str(int n);

 public:
  TxtTable(int row, int col);
  string print_table();
};

class CSVTable : public Table {
 public:
  CSVTable(int row, int col);

  string print_table();
};
}  // namespace MyExcel