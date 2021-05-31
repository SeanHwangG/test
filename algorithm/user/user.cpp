#pragma once
#include <memory>
#include <string>
using namespace std;

class User
{
public:
  ~User();
  User(string name);

  User(const User &other);
  User &operator=(User rhs);

  int getSalary();
  void setSalary(int);

private:
  class Impl;
  unique_ptr<Impl> pimpl;
};
