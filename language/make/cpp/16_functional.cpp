#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int some_func1(const string &a) {
  cout << "Func1 " << a;
  return 0;
}

struct S {
  void operator()(char c) { cout << "Func2 " << c; }
};

void functional_() {
  function<int(const string &)> f1 = some_func1;
  function<void(char)> f2 = S();
  function<void()> f3 = []() { cout << "Func3 "; };

  cout << f1("hello") << endl;
  f2('c');
  f3();
  cout << "\n\n";
}

class A {
  int c;

 public:
  A(int c) : c(c) {}
  int func() {
    cout << "Variable funct " << ++c << endl;
    return c;
  }

  int const_function() const {
    cout << "Constant funct " << c << endl;
    return c;
  }

  static void st() {}
};

void class_() {
  A a(5);
  function<int(A &)> f1 = &A::func;
  function<int(const A &)> f2 = &A::const_function;

  f1(a);
  f2(a);
}

void vector_() {
  vector<int> a(1);
  vector<int> b(2);
  vector<int> c(3);

  vector<vector<int>> container;
  container.push_back(a);
  container.push_back(b);
  container.push_back(c);

  function<size_t(const vector<int> &)> sz_func = &vector<int>::size;

  vector<int> size_vec(4);
  transform(container.begin(), container.end(), size_vec.begin(), sz_func);
  for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
    cout << "Size :: " << *itr << endl;
  }
}

int main() {
  functional_();
  class_();
  vector_();
}