#include <string>

#include "table.h"

using std::string;
// using MyExcel::Table;
namespace MyExcel {
class Excel {
  // Table *current_table;

 public:
  Excel(int max_row, int max_col, int choice);

  int parse_user_input(string s);
  void command_line();
};
}  // namespace MyExcel