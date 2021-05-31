#include "glog/logging.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
#ifdef VAR // add_compile_definitions(VAR=value)
    cout << "F" << endl;
#endif
    std::cout << "Hello, world!\n";

    google::InitGoogleLogging("INFO");
    FLAGS_logtostderr = 1;
    int num_cookies = atoi(argv[1]);

    LOG(INFO) << "1. Conditional Logging" << num_cookies;
    for (int i = 0; i < num_cookies; i++)
    {
        LOG_IF(INFO, i > 5) << "Got lots of cookies";
    }

    return 0;
}
