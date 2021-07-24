#include <cwchar>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int main() {
  wchar_t wcstr_v[2] = L"A";

  char array[3] = {'B', 'a', 'r'};
  string_view array_v(array, std::size(array));

  string cppstr = "Foo";
  string_view cppstr_v(&cppstr[0], cppstr.size());

  cout << cppstr_v << ' ' << array_v << ' ' << *wcstr_v;  // Foo Bar 65
}