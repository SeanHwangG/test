#include "table.h"

using MyExcel::CSVTable;
using MyExcel::Table;
using MyExcel::TxtTable;
using std::max;
using std::to_string;

Table::Table(int max_row, int max_col) : max_row(max_row), max_col(max_col) {
  data_table = new Cell **[max_row];
  for (int i = 0; i < max_row; i++) {
    data_table[i] = new Cell *[max_col];
    for (int j = 0; j < max_col; j++) data_table[i][j] = NULL;
  }
}

Table::~Table() {
  for (int i = 0; i < max_row; i++)
    for (int j = 0; j < max_col; j++)
      if (data_table[i][j]) delete data_table[i][j];
  for (int i = 0; i < max_row; i++) delete[] data_table[i];

  delete[] data_table;
}

void Table::reg_cell(Cell *c, int row, int col) {
  if (!(row < max_row && col < max_col)) return;
  if (data_table[row][col]) delete data_table[row][col];
  data_table[row][col] = c;
}

int Table::to_numeric(const string &s) {
  int row = s[0] - 'A', col = atoi(s.c_str() + 1) - 1;
  if (row < max_row && col < max_col)
    if (data_table[row][col]) return data_table[row][col]->to_numeric();
  return 0;
}
string Table::stringify(const string &s) {
  int col = s[0] - 'A', row = atoi(s.c_str() + 1) - 1;

  if (row < max_row && col < max_col)
    if (data_table[row][col]) return data_table[row][col]->stringify();
  return 0;
}

std::ostream &operator<<(std::ostream &o, Table &table) {
  o << table.print_table();
  return o;
}

TxtTable::TxtTable(int row, int col) : Table(row, col) {}
string TxtTable::print_table() {
  string total_table;

  int *col_max_wide = new int[max_col];
  for (int i = 0; i < max_col; i++) {
    unsigned int max_wide = 2;
    for (int j = 0; j < max_row; j++)
      if (data_table[j][i] && data_table[j][i]->stringify().length() > max_wide)
        max_wide = data_table[j][i]->stringify().length();
    col_max_wide[i] = max_wide;
  }
  total_table += "    ";
  int total_wide = 4;
  for (int i = 0; i < max_col; i++)
    if (col_max_wide[i]) {
      int max_len = max(2, col_max_wide[i]);
      total_table += " | " + col_num_to_str(i);
      total_table += repeat_char(max_len - col_num_to_str(i).length(), ' ');
      total_wide += (max_len + 3);
    }

  total_table += "\n";
  for (int i = 0; i < max_row; i++) {
    total_table += repeat_char(total_wide, '-');
    total_table += "\n" + to_string(i + 1);
    total_table += repeat_char(4 - to_string(i + 1).length(), ' ');

    for (int j = 0; j < max_col; j++)
      if (col_max_wide[j]) {
        int max_len = max(2, col_max_wide[j]);

        string s = "";
        if (data_table[i][j]) s = data_table[i][j]->stringify();
        total_table += " | " + s;
        total_table += repeat_char(max_len - s.length(), ' ');
      }
    total_table += "\n";
  }

  return total_table;
}

string TxtTable::repeat_char(int n, char c) {
  string s = "";
  for (int i = 0; i < n; i++) s.push_back(c);

  return s;
}
string TxtTable::col_num_to_str(int n) {
  string s = "";
  if (n < 26)
    s.push_back('A' + n);
  else {
    s.push_back('A' + n / 26 - 1);
    s.push_back('A' + n % 26);
  }

  return s;
}

CSVTable::CSVTable(int row, int col) : Table(row, col) {}

string CSVTable::print_table() {
  string s = "";
  for (int i = 0; i < max_row; i++) {
    for (int j = 0; j < max_col; j++) {
      if (j >= 1) s += ",";
      string temp;
      if (data_table[i][j]) temp = data_table[i][j]->stringify();

      for (int k = 0; k < temp.length(); k++)
        if (temp[k] == '"') {
          temp.insert(k, 1, '"');
          k++;
        }
      temp = '"' + temp + '"';
      s += temp;
    }
    s += '\n';
  }
  return s;
}
