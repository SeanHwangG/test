#include "excel.h"

#include <iostream>

#include "utils.h"

using MyExcel::Excel;
using MyExcel::ExprCell;
using MyExcel::Stack;

void ExprCell::parse_expression() {
  Stack stack;

  data.insert(0, "(");
  data.push_back(')');

  for (int i = 0; i < data.length(); i++) {
    if (isalpha(data[i])) {
      exp_vec.push_back(data.substr(i, 2));
      i++;
    } else if (isdigit(data[i])) {
      exp_vec.push_back(data.substr(i, 1));
    } else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
      stack.push(data.substr(i, 1));
    } else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
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

Excel::Excel(int max_row, int max_col, int choice = 0) {
  switch (choice) {
    case 0:
      current_table = new TxtTable(max_row, max_col);
      break;
    case 1:
      current_table = new CSVTable(max_row, max_col);
      break;
    default:
      break;
  }
}