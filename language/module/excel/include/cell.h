#pragma once
#include <string>

#include "utils.h"

namespace MyExcel {
class Table;
using MyExcel::Vector;
using std::string;

class Cell {
 protected:
  int x, y;
  Table *table;

  string data;

 public:
  virtual string stringify();
  virtual int to_numeric();

  Cell(int x, int y, Table *table);

  Cell(string data, int x, int y, Table *table);
};

class StringCell : public Cell {
  string data;

 public:
  string stringify();
  int to_numeric();

  StringCell(string data, int x, int y, Table *t);
};

class NumberCell : public Cell {
  int data;

 public:
  string stringify();
  int to_numeric();

  NumberCell(int data, int x, int y, Table *t);
};

class DateCell : public Cell {
  time_t data;

 public:
  string stringify();
  int to_numeric();

  DateCell(string s, int x, int y, Table *t);
};

class ExprCell : public Cell {
  string data;
  string *parsed_expr;

  Vector exp_vec;
  int precedence(char c);
  void parse_expression();

 public:
  ExprCell(string data, int x, int y, Table *t);

  string stringify();
  int to_numeric();
};
}  // namespace MyExcel