#include <unistd.h>

using namespace std;

int main(int argc, char *arg[])
{
  if (fork())
  {
    fork();
  }
  else
  {
    fork();
    char *argv[2] = {"/bin/ls", NULL};
    execv(argv[0], argv);
    fork();
  }
}