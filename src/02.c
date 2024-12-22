#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 65536

int
main_02(const int argc, char const* const* argv)
{

  char const* filename = "1.txt";
  if (argc > 1)
  {
    filename = argv[1];
  }

  return EXIT_SUCCESS;
}
