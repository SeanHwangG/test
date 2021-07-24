#include "cell.h"

#include <string>

#include "utils.h"

using MyExcel::Cell;
using MyExcel::DateCell;
using MyExcel::ExprCell;
using MyExcel::NumberCell;
using MyExcel::Stack;
using MyExcel::StringCell;
using std::string;
using std::to_string;

Cell::Cell(int x, int y, Table *table) : x(x), y(y), table(table) {}
Cell::Cell(string data, int x, int y, Table *table) : data(data), x(x), y(y), table(table) {}

string Cell::stringify() { return data; }
int Cell::to_numeric() { return 0; }

NumberCell::NumberCell(int data, int x, int y, Table *t) : Cell(x, y, t), data(data) {}

string NumberCell::stringify() { return to_string(data); }
int NumberCell::to_numeric() { return data; }

void ExprCell::parse_expression() {
  Stack stack;

  data.insert(0, "(");
  data.push_back(')');

  for (int i = 0; i < data.length(); i++) {
    if (isalpha(data[i])) {
      exp_vec.push_back(data.substr(i, 2));
      i++;
    } else if (isdigit(data[i]))
      exp_vec.push_back(data.substr(i, 1));
    else if (data[i] == '(' || data[i] == '[' || data[i] == '{')
      stack.push(data.substr(i, 1));
    else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
      string t = stack.pop();
      while (t != "(" && t != "[" && t != "{") {
        exp_vec.push_back(t);
        t = stack.pop();
      }
    } else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
      while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i]))
        exp_vec.push_back(stack.pop());
      stack.push(data.substr(i, 1));
    }
  }
}