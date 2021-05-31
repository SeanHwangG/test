#include <iostream>
#include "gflags/gflags.h"

using namespace std;
DEFINE_bool(debug, true, "Print debug option");

int main()
{
    if (FLAGS_debug)
    {
        cout << "Hello GFLAGS" << endl;
    }
    cout << "Hello World";
}